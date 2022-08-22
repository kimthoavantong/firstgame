

#ifndef __PlayerSprite_SCENE_H__
#define __PlayerSprite_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class PlayerSprite : public cocos2d::Sprite
{
public:
	PlayerSprite();
	~PlayerSprite();
	cocos2d::Sprite* spritePlayer;
	static float getContentWidth();
	static float getContentHeight();

	int mau;
private:
	cocos2d::PhysicsWorld* world;
	void setPhysicsWorld(cocos2d::PhysicsWorld* m_world)
	{
		world = m_world;
	}
};

#endif // __HELLOWORLD_SCENE_H__
