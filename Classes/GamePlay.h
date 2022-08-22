

#ifndef __GamePlay_SCENE_H__
#define __GamePlay_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class PlayerSprite;
class ShipSprite;
class DanSprite;
class TargetSprite;
class GamePlay : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    cocos2d::ui::Button* buttonBanDan;

    PlayerSprite* playerGame;
    ShipSprite* shipSpriteGame;
    DanSprite* danSpriteGame;
    TargetSprite* targetSpriteGame;
    cocos2d::Sprite* sprite1;
    cocos2d::Sprite* sprite2;
    void keyBoard();
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    // implement the "static create()" method manually
    virtual void update(float delta) override;
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);

    bool onContactBegin1(cocos2d::PhysicsContact& contact);


    void createDan();
    void createPlayer();
    void createShip();
    void createButtonBanDan();
    void spriteMoveFinished(Node* sender);

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
