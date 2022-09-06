#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "GamePlayScene.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;
using namespace CocosDenshion;
using namespace experimental;
using namespace std;
USING_NS_CC;

const char* HIGH_SCORE = "key"; // highscore save in system



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

  
    SimpleAudioEngine::getInstance()->playBackgroundMusic(Music_Background_one, true);

    GamePlayScene::createPlayer(); // create sprite player
    GamePlayScene::createButtonBanDan(); // create button nhấn để bắn đạn
    GamePlayScene::createEnemyMan1(); // tạo quái
    GamePlayScene::addLabel(); // tạo các label

    /*auto def = UserDefault::sharedUserDefault();
    def->setIntegerForKey(HIGH_SCORE, 0);
    def->flush();*/
    lvDan = 1;
    mang = 3;

    backGround1 = Sprite::create(BackGround_full_one);
    backGround1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround1, -10);

    backGround2 = Sprite::create(BackGround_full_one);
    backGround2->setPosition(Vec2(visibleSize.width*1.5, visibleSize.height / 2));
    this->addChild(backGround2, -11);

    iBackGround1 = Sprite::create(BackGround_item_one);
    iBackGround1->setPosition(Vec2(visibleSize.width * 1.5, visibleSize.height / 2));
    this->addChild(iBackGround1, -1);

    iBackGround2 = Sprite::create(BackGround_item_two);
    iBackGround2->setPosition(Vec2(visibleSize.width * 1.2, visibleSize.height / 4));
    this->addChild(iBackGround2, -1);

    iBackGround3 = Sprite::create(BackGround_item_three);
    iBackGround3->setPosition(Vec2(visibleSize.width * 1.8, visibleSize.height *0.8));
    this->addChild(iBackGround3, -1);
    
    


    // sự kiện keyboard
    auto eventListener = EventListenerKeyboard::create();
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
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
    this->scheduleUpdate();
    return true;
}
// Kiểm tra keyboard được nhấn
bool GamePlayScene::isKeyPressed(EventKeyboard::KeyCode code) {
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


void GamePlayScene::createPlayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spriteShip = Ship::create();
    spriteShip->setPosition(Vec2(-visibleSize.width/2,visibleSize.height/2));
    this->addChild(spriteShip, 10);
}


void GamePlayScene::createDan()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    spriteShipLaser1 = ShipLaser::createShipLaser(lvDan);
    spriteShipLaser1->setPosition(Vec2(spriteShip->getPositionX() + spriteShip->shipWidth / 4,
                spriteShip->getPositionY() - spriteShip->shipHeight / 4));
    this->addChild(spriteShipLaser1, 8);

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

    
    buttonBanDan = cocos2d::ui::Button::create(GamePlayScene_ButtonBanDan);
    buttonBanDan->setOpacity(50);
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
                SimpleAudioEngine::getInstance()->playEffect(Music_Effect_BanDan,false);
                break;
            }
            default:
                break;
            }
        });
}

// add bonus
void GamePlayScene::addLvDan(int a, int b)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spriteLvDan1 = Sprite::create(GamePlayScene_BonusItem_Dame);
    spriteLvDan1->setPosition(Vec2( a + origin.x, origin.y + b));
    auto spriteLvDan1Body = PhysicsBody::createBox(spriteLvDan1->getContentSize());
    spriteLvDan1Body->setDynamic(false);
    spriteLvDan1Body->setCollisionBitmask(100);
    spriteLvDan1Body->setContactTestBitmask(true);
    spriteLvDan1->setPhysicsBody(spriteLvDan1Body);
    this->addChild(spriteLvDan1, 10);
    auto moveLvDan = MoveBy::create(6,Vec2(-visibleSize.width,0));
    auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(GamePlayScene::spriteMoveFinished, this));
    spriteLvDan1->runAction(Sequence::create(moveLvDan, actionMoveDone, NULL));
}


void GamePlayScene::createEnemyMan1() // tạo màn chơi 1
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int j = 1; j < 5; j++)
    {
        for (int i = 1; i < 11; i++)
        {
            auto enemyBig = EnemyBig::create();
            enemyBig->setPosition(Vec2(-(visibleSize.width + (visibleSize.width*(11*j+i)/22)),visibleSize.height*10/11));
            addChild(enemyBig, 10);
            auto moveBy1 = MoveBy::create(5+(10 + i + j*8)*0.1, Vec2((visibleSize.width + (visibleSize.width * (11 * j + i) / 22)) + visibleSize.width*(10-j)/10, 0));
            auto moveBydown1 = MoveBy::create(1.8-(i+j)*0.1, Vec2(0, -(visibleSize.width * (11 - i) / 22)));
            enemyBig->runAction(Sequence::create(moveBy1,moveBydown1,nullptr));
        }
    } 
}
// Add boss 
void GamePlayScene::createBoss1()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bossSprite1 = BossOne::create();
    bossSprite1->setPosition(Vec2(visibleSize.width *0.8, visibleSize.height * 2));
    addChild(bossSprite1, 10);
    auto moveToBoss = MoveTo::create(3,Vec2(visibleSize.width*0.8,visibleSize.height/2));
    bossSprite1->runAction(moveToBoss);
    this->schedule(schedule_selector(GamePlayScene::addDanBoss1),5);
}

void GamePlayScene::addDanBoss1(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    for (float i = -2; i < 3; i++)
    {
        bossBomS = BomS::create();
        bossBomS->setPosition(Vec2(bossSprite1->getPositionX(),bossSprite1->getPositionY()));
        addChild(bossBomS, 9);
        auto moveBomS = MoveTo::create(3,Vec2(-visibleSize.width*0.05,visibleSize.height/2 + visibleSize.height * i / 4));
        auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(GamePlayScene::spriteMoveFinished, this));
        bossBomS->runAction(Sequence::create(moveBomS, actionMoveDone, nullptr));
    }
}

void GamePlayScene::addLabel() // tạo các Label
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    String* teamscore = String::createWithFormat("%i", diem);
    labelDiem = Label::createWithTTF(teamscore->getCString(),Font_Arial,visibleSize.height*0.05);
    labelDiem->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height * 0.9));
    labelDiem->setColor(Color3B::WHITE);
    addChild(labelDiem,11);

    /*Best Score*/
    auto def = UserDefault::sharedUserDefault();
    iHighScore = def->getIntegerForKey(HIGH_SCORE);
    String* highScore = String::createWithFormat("%i", iHighScore);
    labelhighScore = Label::createWithTTF(highScore->getCString(), Font_Arial , visibleSize.height * 0.1, Size::ZERO, TextHAlignment::LEFT);
    labelhighScore->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
    labelhighScore->setColor(Color3B::RED);
    addChild(labelhighScore, 5);
}

// xét va chạm
bool GamePlayScene::onContactBegin1(PhysicsContact& contact)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();

    int k = random(1, 10); // random vật phẩm

    //xét đạn bắn chết quái
    if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 30)
    {
        auto shipLa = dynamic_cast<ShipLaser*>(a->getNode());
        shipLa->animateNo();

        auto enemyBig1 = dynamic_cast<EnemyBig*>(b->getNode());
        enemyBig1->setHealthEnemy(lvDan);

        if (enemyBig1->checkDieEnemy == true) // quái bị tiêu diệt
        {
            x1 = b->getNode()->getPosition().x; //  lấy tọa độ khi quái chết để tạo vật phẩm
            y1 = b->getNode()->getPosition().y;

            SimpleAudioEngine::getInstance()->playEffect(Music_Effect_QuaiBoss, false);
            checkMan++; // tiêu diệt được 1 quái
            diem += 5;
            String* teamscore = String::createWithFormat("%i", diem); // add điểm vào label
            labelDiem->setString(teamscore->getCString());

            auto def = UserDefault::sharedUserDefault(); // xét điểm cao nhất và add vào label
            iHighScore = def->getIntegerForKey(HIGH_SCORE);
            if (diem >= iHighScore)
            {
                def->setIntegerForKey(HIGH_SCORE, diem);
                def->flush();
                iHighScore = diem;
                String* highScore = String::createWithFormat("%i", iHighScore);
                labelhighScore->setString(highScore->getCString());
            }

            if (k == 1) // nếu random k = 1 thì add vật phẩm
            {
                check = true;
            }
            enemyBig1->spriteMove(); // xóa quái đã chết
        }
    }
    else if (a->getCollisionBitmask() == 30 && b->getCollisionBitmask() == 2)
    {
        auto shipLa = dynamic_cast<ShipLaser*>(b->getNode());
        shipLa->animateNo();

        auto enemyBig2 = dynamic_cast<EnemyBig*>(a->getNode());
        enemyBig2->setHealthEnemy(lvDan); // sét máu của quái


        if (enemyBig2->checkDieEnemy == true)
        {
            x1 = a->getPosition().x; // lấy tọa độ khi quái chết để tạo vật phẩm
            y1 = a->getPosition().y;

            SimpleAudioEngine::getInstance()->playEffect(Music_Effect_QuaiBoss, false);
            diem = diem + 5;
            checkMan++;
            String* teamscore = String::createWithFormat("%i", diem);
            labelDiem->setString(teamscore->getCString());
            auto def = UserDefault::sharedUserDefault();
            iHighScore = def->getIntegerForKey(HIGH_SCORE);

            if (diem >= iHighScore)
            {
                def->setIntegerForKey(HIGH_SCORE, diem);
                def->flush();
                iHighScore = diem;
                String* highScore = String::createWithFormat("%i", iHighScore);
                labelhighScore->setString(highScore->getCString());
            }
            if (k == 1) // nếu random k = 1 thì add vật phẩm
            {
                check = true;
            }
            enemyBig2->spriteMove();
        }

    }
    else if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 19)
    {
        auto shipLa = dynamic_cast<ShipLaser*>(a->getNode());
        shipLa->animateNo(); // xóa đạn

        auto enemyBoss1 = dynamic_cast<BossOne*>(b->getNode());
        enemyBoss1->setHealthEnemy(lvDan); // sét máu của quái
        SimpleAudioEngine::getInstance()->playEffect(Music_Effect_QuaiBoss, false);
        if (enemyBoss1->checkDieBoss == true)
        {
            x1 = b->getPosition().x; // lấy tọa độ khi Boss chết để tạo vật phẩm
            y1 = b->getPosition().y;

            SimpleAudioEngine::getInstance()->playEffect(Music_Effect_Die, false);
            diem = diem + 15;
            checkMan++;
            String* teamscore = String::createWithFormat("%i", diem);
            labelDiem->setString(teamscore->getCString());
            auto def = UserDefault::sharedUserDefault();
            iHighScore = def->getIntegerForKey(HIGH_SCORE);
            if (diem >= iHighScore)
            {
                def->setIntegerForKey(HIGH_SCORE, diem);
                def->flush();
                iHighScore = diem;
                String* highScore = String::createWithFormat("%i", iHighScore);
                labelhighScore->setString(highScore->getCString());
            }
            check = true;
            enemyBoss1->spriteMove();
        }
    }
    else if (a->getCollisionBitmask() == 19 && b->getCollisionBitmask() == 2)
    {
        auto shipLa = dynamic_cast<ShipLaser*>(b->getNode());
        shipLa->animateNo(); // xóa đạn

        auto enemyBoss1 = dynamic_cast<BossOne*>(a->getNode());
        enemyBoss1->setHealthEnemy(lvDan); // sét máu của quái
        if (enemyBoss1->checkDieBoss == true)
        {
            x1 = a->getPosition().x; // lấy tọa độ khi Boss chết để tạo vật phẩm
            y1 = a->getPosition().y;

            SimpleAudioEngine::getInstance()->playEffect(Music_Effect_QuaiBoss, false);
            diem = diem + 50;
            checkMan++;
            String* teamscore = String::createWithFormat("%i", diem);
            labelDiem->setString(teamscore->getCString());
            auto def = UserDefault::sharedUserDefault();
            iHighScore = def->getIntegerForKey(HIGH_SCORE);
            if (diem >= iHighScore)
            {
                def->setIntegerForKey(HIGH_SCORE, diem);
                def->flush();
                iHighScore = diem;
                String* highScore = String::createWithFormat("%i", iHighScore);
                labelhighScore->setString(highScore->getCString());
            }
            check = true;
            enemyBoss1->spriteMove();
        }
    }
    // xét plane va chạm với quái
    else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 30)
        || (a->getCollisionBitmask() == 30 && b->getCollisionBitmask() == 1)
        || (a->getCollisionBitmask() == 18 && b->getCollisionBitmask() == 1)
        || (a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 18)
        || (a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 19)
        || (a->getCollisionBitmask() == 19 && b->getCollisionBitmask() == 1))
    {
        SimpleAudioEngine::getInstance()->playEffect(Music_Effect_Die, false);
        mang--;
        if (lvDan > 1)
        {
            lvDan--;
        }
        if (a->getCollisionBitmask() == 18 )
        {
            this->removeChild(a->getNode(), true);
        }
        else if (b->getCollisionBitmask() == 18)
        {
            this->removeChild(b->getNode(), true);
        }
        if (mang >= 1 && a->getCollisionBitmask() == 1 )
        {
            
            keys.clear();
            a->getNode()->setPosition(Vec2(-visibleSize.width / 2, visibleSize.height / 2));
            a->getNode()->runAction(MoveTo::create(2, Vec2(visibleSize.width /8, visibleSize.height/2)));
        }
        else if (mang >= 1 && b->getCollisionBitmask() == 1)
        {
            keys.clear();
            b->getNode()->setPosition(Vec2(-visibleSize.width / 2, visibleSize.height / 2));
            b->getNode()->runAction(MoveTo::create(2, Vec2(visibleSize.width / 8, visibleSize.height / 2)));
        }
        else if (mang == 0)
        {
            // gameover
            keys.clear(); //Kết thúc tất cả các keyboard còn giữ khi kết thúc game
            auto moveGameOver = GameOver::createScene(diem, iHighScore);
            Director::getInstance()->replaceScene(moveGameOver);
        }
    }
    // xét plane ăn vật phẩm tăng dame
    else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 100)
        || (a->getCollisionBitmask() == 100 && b->getCollisionBitmask() == 1))
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


void GamePlayScene::update(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    iBackGround1->setPosition(Vec2(iBackGround1->getPositionX() - (0.001 * visibleSize.width), iBackGround1->getPositionY()));
    iBackGround2->setPosition(Vec2(iBackGround2->getPositionX() - (0.0015 * visibleSize.width), iBackGround2->getPositionY()));
    iBackGround3->setPosition(Vec2(iBackGround3->getPositionX() - (0.001 * visibleSize.width), iBackGround3->getPositionY()));

    backGround1->setPosition(Vec2(backGround1->getPositionX() - (0.001 * visibleSize.width), backGround1->getPositionY()));
    backGround2->setPosition(Vec2(backGround2->getPositionX() - (0.001 * visibleSize.width), backGround2->getPositionY()));


    if (backGround1->getPositionX() <= - visibleSize.width / 2)
    {
        backGround1->setPosition(Vec2(visibleSize.width * 1.5, visibleSize.height / 2));
    }
    if (backGround2->getPositionX() <= - visibleSize.width / 2)
    {
        backGround2->setPosition(Vec2(visibleSize.width * 1.5, visibleSize.height / 2));
    }
    if (iBackGround1->getPositionX() < - iBackGround1->getContentSize().width)
    {
        int ran = random(1, 7);
        iBackGround1->setPosition(Vec2(visibleSize.width * (1 + ran / 8), visibleSize.height * ran/8));
    }
    if (iBackGround2->getPositionX() < -iBackGround2->getContentSize().width)
    {
        int ran = random(1, 7);
        iBackGround2->setPosition(Vec2(visibleSize.width * ran / 8 + visibleSize.width, visibleSize.height * ran / 8));
    }
    if (iBackGround3->getPositionX() < -iBackGround3->getContentSize().width)
    {
        int ran = random(1, 7);
        iBackGround3->setPosition(Vec2(visibleSize.width + visibleSize.width * ran / 8, visibleSize.height * ran / 8));
    }
    if (check)
    {
        GamePlayScene::addLvDan(x1, y1);
        check = false;
    }
    if (checkMan == 40)
    {
        GamePlayScene::createBoss1();
        checkMan++;
    }
    else if (checkMan == 42)  // win va kết thúc
    {
        checkMan++;
        keys.clear(); //Kết thúc tất cả các keyboard còn giữ khi kết thúc game
        auto moveWin = GameOver::createScene(diem, iHighScore);
        Director::getInstance()->replaceScene(moveWin);
    }
}




