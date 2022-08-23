

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    cocos2d::ui::Button* buttonPlay;
    cocos2d::ui::Button* buttonShop;
    cocos2d::ui::Button* buttonSetting;
    cocos2d::ui::Button* buttonAbout;
    cocos2d::ui::Button* buttonQuick;


    void addButtonPlay();
    void addButtonShop();
    void addButtonSetting();
    void addButtonAbout();
    void addButtonQuick();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
