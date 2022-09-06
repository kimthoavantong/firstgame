

#ifndef __SHIPLASER_H__
#define __SHIPLASER_H__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class ShipLaser : public cocos2d::Node
{
public:
    static ShipLaser* createShipLaser();
    virtual bool init();

    Sprite* spriteShipLaser;
    Animation* createAnimation(std::string tenFrame, int soFrame, float delay);
<<<<<<< HEAD
    
=======

    bool checkNo = false;
>>>>>>> 00bb282b9d9d6f84f30ac9681b727cd84330efbf

    PhysicsBody* physicsLaser;
    void spriteMoveFinished(Node* sender);
    void animateNo();
<<<<<<< HEAD
<<<<<<< HEAD
=======
    
>>>>>>> 00bb282b9d9d6f84f30ac9681b727cd84330efbf
=======
    int dameDan;
>>>>>>> parent of 5cd683b (commit1-06-09)
    CREATE_FUNC(ShipLaser);
    int getDameDan(int a);

};

#endif // __ShipLaser_H__
