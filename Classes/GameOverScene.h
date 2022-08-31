

#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int score,int highScore);

    virtual bool init();
    
    cocos2d::ui::Button* buttonResume;
    cocos2d::ui::Button* buttonRestart;
    cocos2d::ui::Button* buttonSetting;
    cocos2d::ui::Button* buttonAbouts;
    cocos2d::ui::Button* buttonQuit;
    cocos2d::Label* labelScore;
    


    void addLabelScore();
    void addButtonResume();
    void addButtonRestart();
    void addButtonAbouts();
    void addButtonSetting();
    void addButtonQuit();


    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
};

#endif // __HELLOWORLD_SCENE_H__
