

#ifndef __DanSprite_SCENE_H__
#define __DanSprite_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class DanSprite : public cocos2d::Sprite
{
public:
	DanSprite();
	~DanSprite();
	cocos2d::Sprite* spriteDan;
	static float getDanContentWidth();
	static float getDanContentHeight();

	int mau;
private:
	cocos2d::PhysicsWorld* world;
	void setPhysicsWorld(cocos2d::PhysicsWorld* m_world)
	{
		world = m_world;
	}
};

#endif // __DanSprite_SCENE_H__
