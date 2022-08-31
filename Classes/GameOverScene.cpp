

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "GamePlayScene.h"
#include "GameOverScene.h"

using namespace cocos2d;
using namespace experimental;

USING_NS_CC;

int scoreOver;
int highScoreOver;
Scene* GameOver::createScene(int score,int highScore)
{
    highScoreOver = highScore;
    scoreOver = score;
    return GameOver::create();
}

bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("Diem %i", scoreOver);
    
    auto backGround = Sprite::create(GameOver_Sprite_BackGround);
    backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround,-1);

    GameOver::addButtonRestart();
    GameOver::addButtonResume();
    GameOver::addButtonSetting();
    GameOver::addButtonAbouts();
    GameOver::addButtonQuit();
    GameOver::addLabelScore();


    
    return true;
}
void GameOver::addButtonRestart()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonRestart = ui::Button::create(GameOver_Sprite_ButtonRestart);
    buttonRestart->setPosition(Vec2(visibleSize.width / 2 + origin.x , origin.y + visibleSize.height / 2));
    this->addChild(buttonRestart, 1);
    buttonRestart->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                auto moveSceneGamePlayScene = GamePlayScene::createPhysicsWorld();
                Director::getInstance()->replaceScene(moveSceneGamePlayScene);
                break;
            }
            default:
                break;
            }
        });
}

void GameOver::addButtonResume()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonResume = ui::Button::create(GameOver_Sprite_ButtonResume);
    buttonResume->setPosition(Vec2(visibleSize.width / 2 + origin.x,
        origin.y +  visibleSize.height / 2 - buttonResume->getContentSize().height - 20));
    this->addChild(buttonResume, 1);
    buttonResume->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                auto moveSceneHelloWorld = HelloWorld::createScene();
                Director::getInstance()->replaceScene(moveSceneHelloWorld);
                break;
            }
            default:
                break;
            }
        });
}

void GameOver::addButtonSetting()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonSetting = ui::Button::create(GameOver_Sprite_ButtonSetting);
    buttonSetting->setPosition(Vec2(visibleSize.width / 2 + origin.x - 20 - buttonSetting->getContentSize().width,
        origin.y + visibleSize.height / 2 - 40 - buttonSetting->getContentSize().height * 2));
    this->addChild(buttonSetting, 1);
}
void GameOver::addButtonAbouts()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonAbouts = ui::Button::create(GameOver_Sprite_ButtonAbout);
    buttonAbouts->setPosition(Vec2(visibleSize.width / 2 + origin.x,
        origin.y + visibleSize.height/2 - buttonAbouts->getContentSize().height*2 - 40));
    this->addChild(buttonAbouts, 1);
}
void GameOver::addButtonQuit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonQuit = ui::Button::create(GameOver_Sprite_ButtonQuit);
    buttonQuit->setPosition(Vec2(visibleSize.width / 2 + origin.x + 20 + buttonQuit->getContentSize().width,
        origin.y + visibleSize.height / 2 - 40 - buttonQuit->getContentSize().height * 2));
    buttonQuit->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                Director::getInstance()->end();
                break;
            }
            default:
                break;
            }
        });
    this->addChild(buttonQuit, 1);
}

void GameOver::addLabelScore()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    String* playScore = String::createWithFormat("Score %i",scoreOver);
    labelScore = Label::createWithTTF(playScore->getCString(), Font_Arial, visibleSize.height * 0.05);
    labelScore->setAnchorPoint(Vec2(0.5, 0.5));
    labelScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));
    labelScore->setColor(Color3B::BLACK);
    this->addChild(labelScore);

    String* playHighScore = String::createWithFormat("%i", highScoreOver);
    labelScore = Label::createWithTTF(playHighScore->getCString(), Font_Arial, visibleSize.height * 0.1);
    labelScore->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 3 / 4));
    labelScore->setColor(Color3B::RED);
    this->addChild(labelScore);
}







