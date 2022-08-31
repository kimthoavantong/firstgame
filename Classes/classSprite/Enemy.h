

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

class Enemy : public cocos2d::Node
{
public:
    
    virtual int getHealthEnemy() = 0;
    virtual void setHealthEnemy(int) = 0;

private:
    
    int healthEnemy;
};

#endif // __Ship_H__
