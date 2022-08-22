

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "GamePlay.h"


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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    HelloWorld::addButtonPlay();
    
    


    
    return true;
}

void HelloWorld::addButtonPlay()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    buttonPlay = ui::Button::create(HelloWorld_Sprite_ButtonPlay);
    buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(buttonPlay, 1);
    buttonPlay->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                auto moveSceneGamePlay = GamePlay::createScene();
                Director::getInstance()->replaceScene(moveSceneGamePlay);
                break;
            }
            default:
                break;
            }
        });
}



