

#ifndef __BOM_H__
#define __BOM_H__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class Bom1 : public cocos2d::Node
{
public:
    static Bom1* createBom();
    virtual bool init();

    Sprite* spriteBom;
    Animation* createAnimation(std::string tenFrame, int soFrame, float delay);


    PhysicsBody* physicsBom;
    void spriteMoveFinished(Node* sender);

    
    CREATE_FUNC(Bom1);

};

#endif // __ShipLaser_H__
