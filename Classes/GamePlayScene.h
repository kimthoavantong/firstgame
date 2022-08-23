

#ifndef __GamePlayScene_SCENE_H__
#define __GamePlayScene_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class PlayerSprite;
class ShipSprite;
class DanSprite;
class TargetSprite;
class GamePlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    cocos2d::ui::Button* buttonBanDan;

    
    cocos2d::Sprite* spritePlayer;
    cocos2d::Sprite* spriteDan;
    cocos2d::Sprite* spriteTarget;


    /*void keyBoard();*/
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    // implement the "static create()" method manually
   /* virtual void update(float delta);*/
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScene);
    void keyboard(float delta);
    bool onContactBegin1(cocos2d::PhysicsContact& contact);

    void createDan();
    void createPlayer();
    void createTarget();
    void createButtonBanDan();
    void spriteMoveFinished(Node* sender);
    int diem = 0;
    int manchoi = 0;
    int dameDan = 1;
    void tick(float dt);


private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::PhysicsWorld* world;
    void setPhysicsWorld(cocos2d::PhysicsWorld* m_world)
    {
        world = m_world;
    }
};

#endif // __HELLOWORLD_SCENE_H__
