
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

	healthEnemy = 1;

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

/////////

BossOne* BossOne::createEnemyBig()
{
	return BossOne::create();
}
bool BossOne::init()
{
	if (!Node::init())
	{
		return false;
	}

	healthEnemy = 30;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BossOne.plist", "BossOne.png");
	spriteBoss = Sprite::createWithSpriteFrameName("BossOne1.png");
	this->addChild(spriteBoss);


	Vector<SpriteFrame*> aniBoss;
	aniBoss.reserve(4);
	aniBoss.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BossOne1.png"));
	aniBoss.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BossOne2.png"));
	aniBoss.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BossOne3.png"));
	aniBoss.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BossOne4.png"));

	Animation* animationBoss = Animation::createWithSpriteFrames(aniBoss, 0.02);
	Animate* animateBoss = Animate::create(animationBoss);
	spriteBoss->runAction(RepeatForever::create(animateBoss));

	physicsBoss = PhysicsBody::createBox(spriteBoss->getContentSize());
	physicsBoss->setDynamic(false);
	physicsBoss->setCollisionBitmask(19);
	physicsBoss->setContactTestBitmask(true);
	this->addComponent(physicsBoss);

	return true;
}

int BossOne::getHealthEnemy()
{
	return this->healthEnemy;
}
void BossOne::setHealthEnemy(int a)
{
	healthEnemy = healthEnemy - a;
	if (healthEnemy <= 0)
	{
		checkDieBoss = true;
	}
}
void BossOne::spriteMove()
{
	this->removeFromParentAndCleanup(true);
}
void BossOne::spriteMoveFinished(Node* sender)
{
	this->removeFromParentAndCleanup(true);
}


/////////

BomS* BomS::createBomS()
{
	return BomS::create();
}
bool BomS::init()
{
	if (!Node::init())
	{
		return false;
	}

	healthEnemy = 1;

	bomSSprite = Sprite::create("Bomb3Idle1.png");
	this->addChild(bomSSprite);

	physicsBomS = PhysicsBody::createBox(bomSSprite->getContentSize());
	physicsBomS->setDynamic(false);
	physicsBomS->setCollisionBitmask(18);
	physicsBomS->setContactTestBitmask(true);
	this->addComponent(physicsBomS);

	return true;
}

int BomS::getHealthEnemy()
{
	return this->healthEnemy;
}
void BomS::setHealthEnemy(int a)
{
	healthEnemy = healthEnemy - a;
}
void BomS::spriteMove()
{
	this->removeFromParentAndCleanup(true);
}
void BomS::spriteMoveFinished(Node* sender)
{
	this->removeFromParentAndCleanup(true);
}





