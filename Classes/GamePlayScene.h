

#ifndef __GamePlayScene_SCENE_H__
#define __GamePlayScene_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "classSprite/ShipLaser.h"
#include "classSprite/Ship.h"
#include "classSprite/EnemyObject.h"

USING_NS_CC;

class GamePlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createPhysicsWorld();

    virtual bool init();
    
    cocos2d::ui::Button* buttonBanDan;


    Ship* spriteShip;
    ShipLaser* spriteShipLaser;
    void updateEnemy(float);


    cocos2d::Sprite* spriteLvDan10;
    cocos2d::Sprite* spriteTarget;

    void addLvDan(int a, int b);
    /*void keyBoard();*/
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);

    virtual void update(float delta);

    CREATE_FUNC(GamePlayScene);
    void keyboard(float delta);
    bool onContactBegin1(cocos2d::PhysicsContact& contact);

    void createDan();
    void createPlayer();
    void createTarget();
    void createButtonBanDan();
    void addLabelDiem();
    void spriteMoveFinished(Node* sender);
    
    int checkMan = 0 ;
    void createEnemyMan1();
    void createEnemyMan2();
    void updateMan(float);

    int x1; int y1; // tọa độ add phần quà khi quái chết
    bool check = false; // check để add qua
    int lvDan = 1; // lv cua dan
    

    /*void tick(float dt);*/

private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;
    

    cocos2d::Label* labelDiem;
    int diem;

    
    PhysicsWorld* world;

    void setPhysicsWorld(PhysicsWorld* m_world)
    {
        world = m_world;
    }
};

#endif // __HELLOWORLD_SCENE_H__
