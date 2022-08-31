#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "GamePlayScene.h"


using namespace cocos2d;
using namespace CocosDenshion;
using namespace experimental;
using namespace std;
USING_NS_CC;

Scene* GamePlayScene::createPhysicsWorld()
{
    auto scene = GamePlayScene::create();
    return scene;
}

bool GamePlayScene::init()
{

    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

  
    SimpleAudioEngine::getInstance()->playBackgroundMusic("musicBackground.wav", true);

    GamePlayScene::createPlayer(); // create sprite player
    GamePlayScene::createButtonBanDan(); // create button nhấn để bắn đạn
    GamePlayScene::createEnemyMan1();
    GamePlayScene::addLabelDiem();



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

    

    this->schedule(schedule_selector(GamePlayScene::keyboard),0.01);
     /*this->schedule(schedule_selector(GamePlayScene::tick), 0.01);*/
    this->schedule(schedule_selector(GamePlayScene::updateMan), 0.02);
    this->scheduleUpdate();
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
    

    if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) && spriteShip->getPositionX() < (visibleSize.width - spriteShip->shipWidth / 2))
    {
        spriteShip->setPosition(Vec2(spriteShip->getPositionX() + a + origin.x, spriteShip->getPositionY()));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) && spriteShip->getPositionX() > spriteShip->shipWidth / 2)
    {
        spriteShip->setPosition(Vec2(spriteShip->getPositionX() - a + origin.x, spriteShip->getPositionY()));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_W) && spriteShip->getPositionY() < (visibleSize.height - spriteShip->shipHeight / 2))
    {
        spriteShip->setPosition(Vec2(spriteShip->getPositionX() + origin.x, spriteShip->getPositionY() + a));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_S) && spriteShip->getPositionY() > spriteShip->shipHeight / 2)
    {
        spriteShip->setPosition(Vec2(spriteShip->getPositionX() + origin.x, spriteShip->getPositionY() - a));
    }
}


void GamePlayScene::update(float dt)
{
    if (check)
    {
    GamePlayScene::addLvDan(x1, y1);
    check = false;
    }
}


void GamePlayScene::createPlayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spriteShip = Ship::create();
    spriteShip->setPosition(Vec2(visibleSize.width/8,visibleSize.height/2));
    this->addChild(spriteShip, 10);
}


void GamePlayScene::createDan()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spriteShipLaser = ShipLaser::create();
    spriteShipLaser->setPosition(Vec2(spriteShip->getPositionX() + spriteShip->shipWidth/4,
        spriteShip->getPositionY() - spriteShip->shipHeight/4));
    this->addChild(spriteShipLaser, 10);
    
}

// Remove sprite
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
                spriteShip->checkBanDan = true;
                GamePlayScene::createDan();
                SimpleAudioEngine::getInstance()->playEffect("musicBanDan.wav",false);
                break;
            }
            default:
                break;
            }
        });

}

// xét va chạm
bool GamePlayScene::onContactBegin1(PhysicsContact& contact)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();
    
    int k = random(1, 10);
    if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 30)
    {
        x1 = b->getNode()->getPosition().x;
        y1 = b->getNode()->getPosition().y;
        

        auto enemyBig1 = dynamic_cast<EnemyBig*>(b->getNode());
        enemyBig1->setHealthEnemy(lvDan);
        if (enemyBig1->checkDieEnemy == true)
        {
            checkMan++;
            diem+=5;
            String* teamscore = String::createWithFormat("%i", diem);
            labelDiem->setString(teamscore->getCString());
            if (k == 1)
            {
                check = true;
            }
            enemyBig1->spriteMove();
        }
        
        this->removeChild(a->getNode(), true);
        CCLOG("%d", checkMan);
        CCLOG("%d", diem);

    }
    else if (a->getCollisionBitmask() == 30 && b->getCollisionBitmask() == 2)
    {
        x1 = a->getPosition().x;
        y1 = a->getPosition().y;
        auto enemyBig2 = dynamic_cast<EnemyBig*>(a->getNode());
        enemyBig2->setHealthEnemy(lvDan);
        if (enemyBig2->checkDieEnemy == true)
        {
            diem+=5;
            checkMan++;

            String* teamscore = String::createWithFormat("%i", diem);
            labelDiem->setString(teamscore->getCString());

            if (k == 1)
            {
                check = true;
            }
            enemyBig2->spriteMove();
        }
        this->removeChild(b->getNode(), true);
        CCLOG("%d", checkMan);
        CCLOG("%d", diem);
    }
    else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 20)  
    {
        checkMan++;
        x1 = a->getPosition().x;
        y1 = a->getPosition().y;
        diem++;
        if (k == 1)
        {
            check = true;
        }
        this->removeChild(b->getNode(), true);
        this->removeChild(a->getNode(), true);
        CCLOG("%d", checkMan);
    }
    else if (a->getCollisionBitmask() == 20 && b->getCollisionBitmask() == 2)
    {
        checkMan++;
        x1 = a->getPosition().x;
        y1 = a->getPosition().y;
        diem++;
        
        if (k == 1)
        {
            check = true;
        }
        this->removeChild(b->getNode(), true);
        this->removeChild(a->getNode(), true);
        CCLOG("%d", checkMan);
    }
    else if((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 30) 
            || (a->getCollisionBitmask() == 30 && b->getCollisionBitmask() == 1)
            || (a->getCollisionBitmask() == 20 && b->getCollisionBitmask() == 1) 
            || (a->getCollisionBitmask() == 20 && b->getCollisionBitmask() == 1))
    {
        // gameover
        keys.clear();
        auto moveGameOver = GameOver::createScene(diem);
        Director::getInstance()->replaceScene(moveGameOver);
    }
    else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 100) || (a->getCollisionBitmask() == 100 && b->getCollisionBitmask() == 1))
    {
        lvDan++;
        if (a->getCollisionBitmask() == 100)
        {
            this->removeChild(a->getNode(), true);
        }
        else if (b->getCollisionBitmask() == 100)
        {
            this->removeChild(b->getNode(), true);
        }
    }

    return true;
}

void GamePlayScene::addLvDan(int a, int b)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spriteLvDan10 = Sprite::create("HP_Bonus.png");
    spriteLvDan10->setPosition(Vec2( a + origin.x, origin.y + b));
    auto spriteLvDan10Body = PhysicsBody::createBox(spriteLvDan10->getContentSize());
    spriteLvDan10Body->setDynamic(false);
    spriteLvDan10Body->setCollisionBitmask(100);
    spriteLvDan10Body->setContactTestBitmask(true);
    spriteLvDan10->setPhysicsBody(spriteLvDan10Body);
    this->addChild(spriteLvDan10, 10);
    auto moveLvDan = MoveBy::create(6,Vec2(-visibleSize.width,0));
    auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(GamePlayScene::spriteMoveFinished, this));
    spriteLvDan10->runAction(Sequence::create(moveLvDan, actionMoveDone, NULL));
}

void GamePlayScene::updateMan(float) // kiểm tra quái còn không
{
    if (checkMan == 40)
    {
        GamePlayScene::createEnemyMan1();
        checkMan++;
    }
    else if (checkMan == 81)
    {
        keys.clear();
        auto moveWin = GameOver::createScene(diem);
        Director::getInstance()->replaceScene(moveWin);
    }
}

void GamePlayScene::createEnemyMan1()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int j = 1; j < 5; j++)
    {
        for (int i = 1; i < 11; i++)
        {
            auto enemyBig = EnemyBig::create();
            enemyBig->setPosition(Vec2(-(visibleSize.width + (visibleSize.width*(11*j-i)/22)),visibleSize.height*10/11));
            /*enemyBig->setPosition(Vec2(visibleSize.width * (10-j) / 10, visibleSize.height * i / 11));*/
            addChild(enemyBig, 10);
            auto moveBy1 = MoveBy::create(15+(10-i)*2/10, Vec2((visibleSize.width + (visibleSize.width * (11 * j - i) / 22)) + visibleSize.width*(10-j)/10, 0));
            auto moveBydown1 = MoveBy::create(2, Vec2(0, - (visibleSize.width * (11 - i) / 22) ));
            enemyBig->runAction(Sequence::create(moveBy1,moveBydown1,nullptr));
        }
    }  
}
void GamePlayScene::addLabelDiem()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    String* teamscore = String::createWithFormat("%i", diem);
    labelDiem = Label::createWithTTF(teamscore->getCString(),"fonts/arial.ttf",visibleSize.height*0.1);
 /*   labelDiem->setAnchorPoint(Vec2(0.5 , 0.5));*/
    labelDiem->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 9 / 10));
    labelDiem->setColor(Color3B::WHITE);
    addChild(labelDiem,11);
}




//void GamePlayScene::tick(float dt)
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    bool isWin = true;
//
//    // Vector bodies lấy tất cả các bodies của world ( ball, edge, paddle body)
//    //Vector<PhysicsWorld*> bodies = world->getAllBodies();
//
//    //for (auto body : bodies) 
//    //{
//    //    if (body->getCollisionBitmask() == 20 || body->getCollisionBitmask() == 30)
//    //    {
//    //        isWin = false; // Chưa Win
//    //    }
//    //}
//    //// Duyệt hết mà  isWin vẫn ko đổi thì xử lý Win game
//    //if (isWin == true)
//    //{ 
//    //        /*auto moveGameOver = GameOver::createScene();
//    //        Director::getInstance()->replaceScene(moveGameOver);*/
//    //}
//}


