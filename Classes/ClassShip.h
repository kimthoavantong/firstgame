

#ifndef __ShipSprite_SCENE_H__
#define __ShipSprite_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ShipSprite : public cocos2d::Sprite
{
public:
	ShipSprite();
	~ShipSprite();
	cocos2d::Sprite* spriteShip;
	static float getShipContentWidth();
	static float getShipContentHeight();

	int mau;
private:
	cocos2d::PhysicsWorld* world;
	void setPhysicsWorld(cocos2d::PhysicsWorld* m_world)
	{
		world = m_world;
	}
};

#endif // __ShipSprite_SCENE_H__
