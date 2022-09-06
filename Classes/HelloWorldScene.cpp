

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "GamePlayScene.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backGround = Sprite::create(HelloWorld_Sprite_BackGround);
    backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround,-1);

    SimpleAudioEngine::getInstance()->preloadEffect(Music_Effect_Click);

    HelloWorld::addButtonPlay();
    HelloWorld::addButtonShop();
    HelloWorld::addButtonAbout();
    HelloWorld::addButtonSetting();
    HelloWorld::addButtonQuick();

    
    return true;
}

void HelloWorld::addButtonPlay()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    buttonPlay = cocos2d::ui::Button::create(HelloWorld_Sprite_ButtonPlay);
    buttonPlay->setScale(1);
    buttonPlay->setPosition(Vec2(visibleSize.width / 2 + origin.x,origin.y + visibleSize.height * 3 / 4));
    buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
            
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
            {
                SimpleAudioEngine::getInstance()->playEffect(Music_Effect_Click, false);
                break;
            }
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
    this->addChild(buttonPlay, 1);
}
void HelloWorld::addButtonShop()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    buttonShop = cocos2d::ui::Button::create(HelloWorld_Sprite_ButtonShop);
    buttonShop->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height / 2));
    this->addChild(buttonShop, 1);
    buttonShop->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
            {
                SimpleAudioEngine::getInstance()->playEffect(Music_Effect_Click, false);
            }
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                break;
            }
            default:
                break;
            }
        });
    
}
void HelloWorld::addButtonAbout()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonAbout = cocos2d::ui::Button::create(HelloWorld_Sprite_ButtonAbout);
    buttonAbout->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height / 4));
    this->addChild(buttonAbout, 1);

}
void HelloWorld::addButtonSetting()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonSetting = cocos2d::ui::Button::create(HelloWorld_Sprite_ButtonSetting);
    buttonSetting->setPosition(Vec2(visibleSize.width / 2 - buttonAbout->getContentSize().width * 1.2 + origin.x, origin.y + visibleSize.height / 4));
    this->addChild(buttonSetting, 1);
}

void HelloWorld::addButtonQuick()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    buttonQuick = cocos2d::ui::Button::create(HelloWorld_Sprite_ButtonQuick);
    buttonQuick->setPosition(Vec2(visibleSize.width / 2 + buttonAbout->getContentSize().width * 1.2 + origin.x, origin.y + visibleSize.height / 4));
    this->addChild(buttonQuick, 1);
    buttonQuick->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
            {
                SimpleAudioEngine::getInstance()->playEffect(Music_Effect_Click, false);
                break;
            }
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                Director::getInstance()->end();
                break;
            }
            default:
                break;
            }
        });
}




