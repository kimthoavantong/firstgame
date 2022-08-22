

#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    cocos2d::ui::Button* buttonPlay;

    void addSpriteGameOver();
    void addButtonPlay();

    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
};

#endif // __HELLOWORLD_SCENE_H__
