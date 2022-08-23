#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "GamePlayScene.h"

USING_NS_CC;

Scene* GamePlayScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GamePlayScene::create();
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
bool GamePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->unschedule(schedule_selector(GamePlayScene::keyboard));

    // set physics size = scene
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, false);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
    addChild(edgeNode);

    

    GamePlayScene::createPlayer(); // create sprite player
    GamePlayScene::createButtonBanDan(); // create button nhấn để bắn đạn
    GamePlayScene::createTarget(); // create Sprite target (quái)
    

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
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin1, this);
    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    
    /*this->scheduleUpdate();*/ // Nhận update 60/1s
    this->schedule(schedule_selector(GamePlayScene::keyboard),0.01);
    this->schedule(schedule_selector(GamePlayScene::tick), 0.01);
    
    return true;
}
// Kiểm tra keyboard được nhấn
bool GamePlayScene::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?

    if (keys.find(code) != keys.end())
        return true;
    return false;
    
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
    std::chrono::high_resolution_clock::time_point> GamePlayScene::keys;

///////// xét sự kiện keyBoard 


void GamePlayScene::keyboard(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int a = 5;

    if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) && spritePlayer->getPositionX() < (visibleSize.width - spritePlayer->getContentSize().width / 2))
    {
        spritePlayer->setPosition(Vec2(spritePlayer->getPositionX() + a + origin.x, spritePlayer->getPositionY()));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) && spritePlayer->getPositionX() > spritePlayer->getContentSize().width / 2)
    {
        spritePlayer->setPosition(Vec2(spritePlayer->getPositionX() - a + origin.x, spritePlayer->getPositionY()));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_W) && spritePlayer->getPositionY() < (visibleSize.height - spritePlayer->getContentSize().height / 2))
    {
        spritePlayer->setPosition(Vec2(spritePlayer->getPositionX() + origin.x, spritePlayer->getPositionY() + a));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_S) && spritePlayer->getPositionY() > spritePlayer->getContentSize().height / 2)
    {
        spritePlayer->setPosition(Vec2(spritePlayer->getPositionX() + origin.x, spritePlayer->getPositionY() - a));
    }
}
//void GamePlayScene::update(float delta) 
//{
//    GamePlayScene::keyBoard();
//}


void GamePlayScene::createPlayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spritePlayer = Sprite::create(ClassPlayer_Sprite_spritePlayer);
    spritePlayer->setPosition(Vec2(visibleSize.width/2,spritePlayer->getContentSize().height));
    auto spritePlayerBody = PhysicsBody::createBox(spritePlayer->getContentSize());
    spritePlayerBody->setDynamic(false);
    spritePlayerBody->setCollisionBitmask(1);
    spritePlayerBody->setContactTestBitmask(true);
    spritePlayer->setPhysicsBody(spritePlayerBody);
    this->addChild(spritePlayer, 10);
}


void GamePlayScene::createDan()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spriteDan = Sprite::create(ClassDan_Sprite_Dan);
    spriteDan->setPosition(spritePlayer->getPosition());
    auto spriteDanBody = PhysicsBody::createBox(spriteDan->getContentSize());
    spriteDanBody->setDynamic(false);
    spriteDanBody->setCollisionBitmask(2);
    spriteDanBody->setContactTestBitmask(true);
    spriteDan->setPhysicsBody(spriteDanBody);
    this->addChild(spriteDan, 10);
    auto movedan = MoveBy::create(2, Vec2(0,  visibleSize.height * 2));
    auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(GamePlayScene::spriteMoveFinished, this));
    spriteDan->runAction(Sequence::create(movedan, actionMoveDone, NULL));
}

// Remove đạn
void GamePlayScene::spriteMoveFinished(Node* sender)
{
    // Hàm này có mỗi công việc là loại bỏ dan ( đang là Sprite) ra khỏi layer của game
    // Ép kiểu Contrỏ Sprite của 1 Node*
    auto sprite = (Sprite*)sender;
    this->removeChild(sprite, true);
}
// create button click bắn đạn
void GamePlayScene::createButtonBanDan()
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
                GamePlayScene::createDan();
                break;
            }
            default:
                break;
            }
        });

}
void GamePlayScene::createTarget()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    spriteTarget = Sprite::create(ClassShip_Sprite_Ship);
    int kc = spriteTarget->getContentSize().width / 2;
    int viTriDau = (visibleSize.width - 10 * spriteTarget->getContentSize().width - 9 * kc) / 2 + spriteTarget->getContentSize().width / 2;
    for (int i = 0; i < 10; i++)
    {
        spriteTarget = Sprite::create(ClassShip_Sprite_Ship);
        spriteTarget->setPosition(Vec2(viTriDau + (kc + spriteTarget->getContentSize().width)*i,visibleSize.height - spriteTarget->getContentSize().height*2));
        auto spriteTargetBody = PhysicsBody::createBox(spriteTarget->getContentSize());
        spriteTargetBody->setDynamic(false);
        spriteTargetBody->setCollisionBitmask(3);
        spriteTargetBody->setContactTestBitmask(true);
        spriteTarget->setTag(3);
        spriteTarget->setPhysicsBody(spriteTargetBody);
        this->addChild(spriteTarget, 10);
    }
}

// xét va chạm
bool GamePlayScene::onContactBegin1(PhysicsContact& contact)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();
    
    if ((a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 3))
    {
        
        diem++;
        CCLOG("%d", diem);
        this->removeChild(b->getNode(), true);
        this->removeChild(a->getNode(), true);
    }
    else if ((a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 2))
    {
        diem++;
        CCLOG("%d", diem);
        this->removeChild(b->getNode(), true);
        this->removeChild(a->getNode(), true);
    }
    else if((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 3) || (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 1))
    {
        // gameover

        this->unschedule(schedule_selector(GamePlayScene::keyboard));
        auto moveGameOver = GameOver::createScene();
        Director::getInstance()->replaceScene(moveGameOver);
    }
    else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 100) || (a->getCollisionBitmask() == 100 && b->getCollisionBitmask() == 1))
    {
        // gameover
        dameDan++;
        if (a->getCollisionBitmask() == 100)
        {
            this->removeChild(a->getNode(), true);
        }
        else if (b->getCollisionBitmask() == 100)
        {
            this->removeChild(b->getNode(), true);
        }
       
    }
    else
    {
        for (int i = 4; i < 10; i++)
        {

             if ((a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == i) || (a->getCollisionBitmask() == i && b->getCollisionBitmask() == 2))
             {
                diem++;
                CCLOG("%d", diem);
                 if (a->getCollisionBitmask() == i)
                 {
                        a->setCollisionBitmask(a->getCollisionBitmask() - dameDan);
                        if (a->getCollisionBitmask() < 3)
                        {
                            a->setCollisionBitmask(3);
                        }
                        this->removeChild(b->getNode(), true);
                 }
                 else if (b->getCollisionBitmask() == i)
                 {
                        b->setCollisionBitmask(b->getCollisionBitmask() - dameDan);
                        if (b->getCollisionBitmask() < 3)
                        {
                            b->setCollisionBitmask(3);
                        }
                        this->removeChild(a->getNode(), true);
                 }
             }
        }
    }
      
    return true;
}
void GamePlayScene::tick(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // 1 biến bool xác nhận Win game ban đầu gán = true;
    bool isWin = true;

    // Vector bodies lấy tất cả các bodies của world ( ball, edge, paddle body), về vector bạn nghiên cứu thêm C++ nâng cao nhé, cũng gần giống mảng, và cũng khá giống Stack. Khai báo vector thì như này Vector<Kiểu biến> tên_biến
    Vector<PhysicsBody*> bodies = world->getAllBodies();

    // Duyệt từng phần tử của vector trên, kiếm tra loại đối tượng = Tag, Bạn nên tìm hiểu lại lệnh for nhé, nó có nhiều biến thể cho từng loại lớp đặc biệt, đọc phần C++ nâng cao phần list, vector, queue,v..
   // Đừng dập khuôn for chỉ có dạng for( int i=0; i<N; i++) nhé

    for (auto body : bodies) 
    {
        for (int i = 3; i < 7; i++)
        {
            if (body->getCollisionBitmask() == i)
            {
                isWin = false; // Chưa Win
            }
        }
    }
    // Duyệt hết mà  isWin vẫn ko đổi thì xử lý Win game
    if (isWin == true)
    { 
        manchoi++;
        if (manchoi == 1)
        {
            spriteTarget = Sprite::create(GamePlayScene_Sprite_QuaiShip2);
            int kc = spriteTarget->getContentSize().width / 2;
            int viTriDau = (visibleSize.width - 10 * spriteTarget->getContentSize().width - 9 * kc) / 2 + spriteTarget->getContentSize().width / 2;
            for (int i = 0; i < 10; i++)
            {
                spriteTarget = Sprite::create(GamePlayScene_Sprite_QuaiShip2);
                spriteTarget->setPosition(Vec2(viTriDau + (kc + spriteTarget->getContentSize().width) * i, visibleSize.height - spriteTarget->getContentSize().height * 2));
                auto spriteTargetBody = PhysicsBody::createBox(spriteTarget->getContentSize());
                spriteTargetBody->setDynamic(false);
                spriteTargetBody->setCollisionBitmask(4);
                spriteTargetBody->setContactTestBitmask(true);
                spriteTarget->setPhysicsBody(spriteTargetBody);
                this->addChild(spriteTarget, 10);
            }
        }
        else if (manchoi == 2)
        {
            spriteTarget = Sprite::create(ClassShip_Sprite_Ship);
            int kc = spriteTarget->getContentSize().width / 2;
            int viTriDau = (visibleSize.width - 10 * spriteTarget->getContentSize().width - 9 * kc) / 2 + spriteTarget->getContentSize().width / 2;
            for (int i = 0; i < 10; i++)
            {
                spriteTarget = Sprite::create(ClassShip_Sprite_Ship);
                spriteTarget->setPosition(Vec2(viTriDau + (kc + spriteTarget->getContentSize().width) * i, visibleSize.height - spriteTarget->getContentSize().height * 2));
                auto spriteTargetBody = PhysicsBody::createBox(spriteTarget->getContentSize());
                spriteTargetBody->setDynamic(false);
                spriteTargetBody->setCollisionBitmask(5);
                spriteTargetBody->setContactTestBitmask(true);
                spriteTarget->setPhysicsBody(spriteTargetBody);
                this->addChild(spriteTarget, 10);
            }
        }
        else if (manchoi == 3)
        {
            spriteTarget = Sprite::create(ClassShip_Sprite_Ship);
            int kc = spriteTarget->getContentSize().width / 2;
            int viTriDau = (visibleSize.width - 10 * spriteTarget->getContentSize().width - 9 * kc) / 2 + spriteTarget->getContentSize().width / 2;
            for (int i = 0; i < 10; i++)
            {
                spriteTarget = Sprite::create(ClassShip_Sprite_Ship);
                spriteTarget->setPosition(Vec2(viTriDau + (kc + spriteTarget->getContentSize().width) * i, visibleSize.height - spriteTarget->getContentSize().height * 2));
                auto spriteTargetBody = PhysicsBody::createBox(spriteTarget->getContentSize());
                spriteTargetBody->setDynamic(false);
                spriteTargetBody->setCollisionBitmask(6);
                spriteTargetBody->setContactTestBitmask(true);
                spriteTarget->setPhysicsBody(spriteTargetBody);
                this->addChild(spriteTarget, 10);
            }
        }
        else
        {
            auto moveGameOver = GameOver::createScene();
            Director::getInstance()->replaceScene(moveGameOver);
        }
    }
}



