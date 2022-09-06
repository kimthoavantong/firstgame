
#include "EnemyObject.h"

USING_NS_CC;

EnemySmall* EnemySmall::createEnemySmall()
{
	return EnemySmall::create();
}
bool EnemySmall::init()
{
	if (!Node::init())
	{
		return false;
	}

	healthEnemy = 4;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemysmall.plist", "enemysmall.png");
	spriteEnemySmall = Sprite::createWithSpriteFrameName("enemysmall1.png");
	this->addChild(spriteEnemySmall);
	

	Vector<SpriteFrame*> aniFrameSmall;
	aniFrameSmall.reserve(2);
	aniFrameSmall.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemysmall1.png"));
	aniFrameSmall.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemysmall2.png"));

	Animation* animationSmall = Animation::createWithSpriteFrames(aniFrameSmall, 0.02f);
	Animate* animateSmall = Animate::create(animationSmall);
	spriteEnemySmall->runAction(RepeatForever::create(animateSmall));


	physicsSmall = PhysicsBody::createBox(spriteEnemySmall->getContentSize());
	physicsSmall->setDynamic(false);
	physicsSmall->setCollisionBitmask(20);
	physicsSmall->setContactTestBitmask(true);
	this->addComponent(physicsSmall);


	auto moveSmall = MoveBy::create(6, Vec2(-2000, 0));
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(EnemySmall::spriteMoveFinished, this));
	/*this->runAction(Sequence::create(moveSmall, actionMoveDone, NULL));*/
	

	return true;
}
int EnemySmall::getHealthEnemy()
{
	return this->healthEnemy;
}
void EnemySmall::setHealthEnemy(int)
{
	if (healthEnemy <=0 )
	{
		this->removeFromParentAndCleanup(true);
	}
	else
	{
		healthEnemy = healthEnemy - 2;
	}
}
void EnemySmall::spriteMoveFinished(Node* sender)
{
	this->removeFromParentAndCleanup(true);
}






/////////

EnemyBig* EnemyBig::createEnemyBig()
{
	return EnemyBig::create();
}
bool EnemyBig::init()
{
	if (!Node::init())
	{
		return false;
	}

	healthEnemy = 3;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemybig.plist", "enemybig.png");
	spriteEnemyBig = Sprite::createWithSpriteFrameName("enemybig1.png");
	this->addChild(spriteEnemyBig);

	width = spriteEnemyBig->getContentSize().width;
	height = spriteEnemyBig->getContentSize().height;

	Vector<SpriteFrame*> aniFrameBig;
	aniFrameBig.reserve(2);
	aniFrameBig.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemybig1.png"));
	aniFrameBig.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemybig2.png"));

	Animation* animationBig = Animation::createWithSpriteFrames(aniFrameBig, 0.02f);
	Animate* animateBig = Animate::create(animationBig);
	spriteEnemyBig->runAction(RepeatForever::create(animateBig));

	physicsBig = PhysicsBody::createBox(spriteEnemyBig->getContentSize());
	physicsBig->setDynamic(false);
	physicsBig->setCollisionBitmask(30);
	physicsBig->setContactTestBitmask(true);
	this->addComponent(physicsBig);

	auto moveBig = MoveBy::create(6, Vec2(-2000, 0));
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(EnemyBig::spriteMoveFinished, this));
	auto moveBy1 = MoveBy::create(1, Vec2(0, 20));
	auto moveBy2 = MoveBy::create(2, Vec2(0, -40));
	auto moveBy3 = MoveBy::create(1, Vec2(0, 20));
	this->runAction(RepeatForever::create(Sequence::create(moveBy1,moveBy2,moveBy3,nullptr)));


	return true;
}

int EnemyBig::getHealthEnemy()
{
	return this->healthEnemy;
}
void EnemyBig::setHealthEnemy(int a)
{
	healthEnemy = healthEnemy - a;
	if (healthEnemy <= 0)
	{
		checkDieEnemy = true;
	}	
}
void EnemyBig::spriteMove()
{
	this->removeFromParentAndCleanup(true);
}
void EnemyBig::spriteMoveFinished(Node* sender)
{
	this->removeFromParentAndCleanup(true);
}
void EnemyBig::addBom(float dt)
{
	int random1 = random(1, 2);
	if (spriteEnemyBig != nullptr)
	{
		if (random1 == 1)
		{
			spriteBom = Sprite::create("enemy1.png");
			this->addChild(spriteBom);
		}
	}
}



