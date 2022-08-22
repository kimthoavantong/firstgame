

#ifndef __TargetSprite_SCENE_H__
#define __TargetSprite_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class TargetSprite : public cocos2d::Sprite
{
public:
	TargetSprite();
	~TargetSprite();
	cocos2d::Sprite* spriteDan;
	static float getDanContentWidth();
	static float getDanContentHeight();

private:
	cocos2d::PhysicsWorld* world;
	void setPhysicsWorld(cocos2d::PhysicsWorld* m_world)
	{
		world = m_world;
	}
};

#endif // __TargetSprite_SCENE_H__
