

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "GamePlayScene.h"
#include "GameOverScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    auto backGround = Sprite::create(GameOver_Sprite_BackGround);
    backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround,-1);

    GameOver::addButtonRestart();
    GameOver::addButtonResume();
    GameOver::addButtonSetting();
    GameOver::addButtonAbouts();
    GameOver::addButtonQuit();


    
    return true;
}
void GameOver::addButtonRestart()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonRestart = ui::Button::create(GameOver_Sprite_ButtonRestart);
    buttonRestart->setPosition(Vec2(visibleSize.width / 2 + origin.x , origin.y + 40 + buttonRestart->getContentSize().height*2 + visibleSize.height / 2));
    this->addChild(buttonRestart, 1);
    buttonRestart->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                auto moveSceneGamePlayScene = GamePlayScene::createScene();
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
    buttonResume->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 20 +  visibleSize.height / 2 + buttonResume->getContentSize().height));
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
    buttonSetting->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height / 2 ));
    this->addChild(buttonSetting, 1);
}
void GameOver::addButtonAbouts()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonAbouts = ui::Button::create(GameOver_Sprite_ButtonAbout);
    buttonAbouts->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height / 2 - 20 - buttonAbouts->getContentSize().height));
    this->addChild(buttonAbouts, 1);
}
void GameOver::addButtonQuit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonQuit = ui::Button::create(GameOver_Sprite_ButtonQuit);
    buttonQuit->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height / 2 - 40 - buttonQuit->getContentSize().height * 2));
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







