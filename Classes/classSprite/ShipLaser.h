

#ifndef __SHIPLASER_H__
#define __SHIPLASER_H__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class ShipLaser : public cocos2d::Node
{
public:
    static ShipLaser* createShipLaser(int a);
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
=======
    
>>>>>>> 00bb282b9d9d6f84f30ac9681b727cd84330efbf
    CREATE_FUNC(ShipLaser);

};

#endif // __ShipLaser_H__
