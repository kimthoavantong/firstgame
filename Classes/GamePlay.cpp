#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GamePlay.h"
#include "ClassPlayer.h"
#include "ClasDan.h"
#include "ClassShip.h"
#include "GameOverScene.h"
#include "ClassTarget.h"
#include "Definitions.h"
USING_NS_CC;

Scene* GamePlay::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GamePlay::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // set physics size = scene
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, false);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
    addChild(edgeNode);

    
    GamePlay::createButtonBanDan(); // create button nhấn để bắn đạn
    GamePlay::createPlayer(); // create spriteplayer từ classplayer
    GamePlay::createShip(); // create Spriteship(quái) từ classShip
    

    // sự kiện keyboard
    auto eventListener = EventListenerKeyboard::create();
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if (keys.find(keyCode) == keys.end()) {
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    

    // nhận sự kiện va chạm
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlay::onContactBegin1, this);
    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    
    this->scheduleUpdate(); // Nhận update 60/1s
    
    return true;
}
// Kiểm tra keyboard được nhấn
bool GamePlay::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if (keys.find(code) != keys.end())
        return true;
    return false;
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
    std::chrono::high_resolution_clock::time_point> GamePlay::keys;

///////// xét sự kiện keyBoard 

void GamePlay::keyBoard()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int a = 5;

    if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) && playerGame->getPositionX() < (visibleSize.width - PlayerSprite::getContentWidth() / 2))
    {
        playerGame->setPosition(Vec2(playerGame->getPositionX() + a + origin.x, playerGame->getPositionY()));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) && playerGame->getPositionX() > PlayerSprite::getContentWidth() / 2)
    {
        playerGame->setPosition(Vec2(playerGame->getPositionX() - a + origin.x, playerGame->getPositionY()));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_W) && playerGame->getPositionY() < (visibleSize.height - PlayerSprite::getContentHeight() / 2))
    {
        playerGame->setPosition(Vec2(playerGame->getPositionX() + origin.x, playerGame->getPositionY() + a));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_S) && playerGame->getPositionY() > PlayerSprite::getContentHeight()/2)
    {
        playerGame->setPosition(Vec2(playerGame->getPositionX() + origin.x, playerGame->getPositionY() - a));
    }

}
void GamePlay::update(float delta) 
{
    GamePlay::keyBoard();
}

// xét va chạm


void GamePlay::createPlayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    playerGame = new PlayerSprite();
    playerGame->setPosition(Vec2(visibleSize.width / 2, PlayerSprite::getContentHeight()));
    playerGame->mau = 100;
    this->addChild(playerGame, 10);
}
void GamePlay::createShip()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    int k = 20;
    int d = (visibleSize.width - 14 * k - 15 * TargetSprite::getDanContentWidth())/2;
    for (int i = 0; i < 15; i++)
    {
        // Sprite
        sprite2 = Sprite::create(ClassShip_Sprite_Ship);
        sprite2->setPosition(Vec2(d + sprite2->getContentSize().width/2 + (k + sprite2->getContentSize().width)*i, visibleSize.height * 9 / 10));
        auto edge3 = PhysicsBody::createBox(sprite2->getContentSize());
        edge3->setDynamic(false);
        edge3->setCollisionBitmask(9);
        edge3->setContactTestBitmask(true);
        sprite2->setPhysicsBody(edge3);
        this->addChild(sprite2, 10);
        auto moveby1 = MoveBy::create(1, Vec2(40, 0));
        auto moveby2 = MoveBy::create(2, Vec2(-80, 0));
        auto seq = Sequence::create(moveby1, moveby2, moveby1, nullptr);
        sprite2->runAction(RepeatForever::create(seq));
        

        //// sprite quái từ classShip

        /*targetSpriteGame = new TargetSprite();
        targetSpriteGame->setPosition(Vec2(d + TargetSprite::getDanContentWidth()/2 + (k + TargetSprite::getDanContentWidth())*i, visibleSize.height * 9 / 10));
        auto edge3 = PhysicsBody::createBox(targetSpriteGame->getContentSize());
        edge3->setDynamic(false);
        edge3->setCollisionBitmask(9);
        edge3->setContactTestBitmask(true);
        targetSpriteGame->setTag(9);
        targetSpriteGame->setPhysicsBody(edge3);
        this->addChild(targetSpriteGame, 10);
        auto moveby1 = MoveBy::create(1, Vec2(40, 0));
        auto moveby2 = MoveBy::create(2, Vec2(-80, 0));
        auto seq = Sequence::create(moveby1, moveby2, moveby1, nullptr);
        targetSpriteGame->runAction(RepeatForever::create(seq));*/
    }   
}
void GamePlay::createDan()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    danSpriteGame = new DanSprite();
    danSpriteGame->setPosition(Vec2(playerGame->getPositionX(), playerGame->getPositionY()));
    auto edge2 = PhysicsBody::createBox(danSpriteGame->getContentSize());
    edge2->setDynamic(false);
    edge2->setCollisionBitmask(8);
    edge2->setContactTestBitmask(true);
    danSpriteGame->setTag(8);
    danSpriteGame->setPhysicsBody(edge2);
    this->addChild(danSpriteGame, 10);
    auto movedan = MoveBy::create(6, Vec2(0, playerGame->getPositionY() + visibleSize.height * 2));
    auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(GamePlay::spriteMoveFinished, this));
    danSpriteGame->runAction(Sequence::create(movedan, actionMoveDone, NULL));
}

// Remove đạn
void GamePlay::spriteMoveFinished(Node* sender)
{
    // Hàm này có mỗi công việc là loại bỏ Target ( đang là Sprite) ra khỏi layer của game
    // Ép kiểu Contrỏ Sprite của 1 Node*
    auto sprite = (Sprite*)sender;
    this->removeChild(sprite, true);
}
// create button click bắn đạn
void GamePlay::createButtonBanDan()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    buttonBanDan = ui::Button::create("HelloWorld.png");
    buttonBanDan->setPosition(Vec2(visibleSize.width - buttonBanDan->getContentSize().width/2, buttonBanDan->getContentSize().height/2));
    this->addChild(buttonBanDan, 1);
    buttonBanDan->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                GamePlay::createDan();
                break;
            }
            default:
                break;
            }
        });

}
// xét va chạm
bool GamePlay::onContactBegin1(PhysicsContact& contact)
{
    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();

    if (a->getCollisionBitmask() == 8 && b->getCollisionBitmask() == 9)
    {
        CCLOG("1");
        this->removeChild(b->getNode(), true);
        this->removeChild(a->getNode(), true);
        
        
    }
    else if (a->getCollisionBitmask() == 9 && b->getCollisionBitmask() == 8)
    {
        CCLOG("2");
        this->removeChild(b->getNode(), true);
        this->removeChild(a->getNode(), true);
        
    }
    else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 9) || (a->getCollisionBitmask() == 9 && b->getCollisionBitmask() == 1))
    {
        // gameover
        auto moveGameOver = GameOver::createScene();
        Director::getInstance()->replaceScene(moveGameOver);
    }
    return true;
}


