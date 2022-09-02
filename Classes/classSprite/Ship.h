

#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class Ship : public cocos2d::Node
{
public:
    static Ship* createShip();
    virtual bool init();

    Sprite* spriteShip;
    int shipWidth;
    int shipHeight;

    Sprite* spriteBar;
    int getHealth();
    void setHealth(int);
    void animateBanDan(float);
    void animatePlaneFly(float);

    bool checkBanDan = false;

    PhysicsBody* physicsShip;
    CREATE_FUNC(Ship);
    int healthShip = 5;
    void moveToto();
private:
    
    
};

#endif // __Ship_H__
