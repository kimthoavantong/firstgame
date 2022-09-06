

#ifndef __ENEMY_SMALL_H__
#define __ENEMY_SMALL_H__

#include "cocos2d.h"
#include "Enemy.h"
using namespace cocos2d;
USING_NS_CC;

class EnemySmall : public Enemy
{
public:
    static EnemySmall* createEnemySmall();
    virtual bool init();
    Sprite* spriteEnemySmall;

    int getHealthEnemy();
    void setHealthEnemy(int);

    PhysicsBody* physicsSmall;
    void spriteMoveFinished(Node* sender);
    CREATE_FUNC(EnemySmall);
private:
    
    int healthEnemy;
};

#endif // __ENEMY_SMALL_H__

#ifndef __ENEMYO_BIG_H__
#define __ENEMYO_BIG_H__

#include "cocos2d.h"
#include "Enemy.h"
using namespace cocos2d;
USING_NS_CC;

class EnemyBig : public Enemy
{
public:
    static EnemyBig* createEnemyBig();
    virtual bool init();
    cocos2d::Sprite* spriteEnemyBig;
    cocos2d::Sprite* spriteBom;
    int getHealthEnemy();
    void setHealthEnemy(int );
    void spriteMove();
    void addBom(float dt);
   
    PhysicsBody* physicsBig;
    void spriteMoveFinished(Node* sender);
    int width;
    int height;
    bool checkDieEnemy = false;
    CREATE_FUNC(EnemyBig);
private:
    int healthEnemy;
};

#endif // __ENEMY_BIG_H__
