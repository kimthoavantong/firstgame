
#include "ShipLaser.h"

USING_NS_CC;


ShipLaser* ShipLaser::createShipLaser()
{
    return ShipLaser::create();
}

bool ShipLaser::init()
{
    if ( !Node::init() )
    {
        return false;
    }

    /*SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shiplaser/shiplaser.plist","shiplaser/shiplaser.png");
    spriteShipLaser = Sprite::createWithSpriteFrameName("Bullet1.png");
    this->addChild(spriteShipLaser);*/

    spriteShipLaser = Sprite::create("shiplaser/Bullet1.png");
    this->addChild(spriteShipLaser);



    physicsLaser = PhysicsBody::createBox(spriteShipLaser->getContentSize());
    physicsLaser->setDynamic(false);
    physicsLaser->setContactTestBitmask(true);
    physicsLaser->setCollisionBitmask(2);
    this->addComponent(physicsLaser);

    /*Vector<SpriteFrame*> aniFrame;
    aniFrame.reserve(5);
    aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bullet1.png"));
    aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bullet2.png"));
    aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bullet3.png"));
    aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bullet4.png"));
    aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bullet5.png"));
   
    
    Animation* animationLaser = Animation::createWithSpriteFrames(aniFrame,0.02f);
    Animate* animateLaser = Animate::create(animationLaser);
    spriteShipLaser->runAction(RepeatForever::create(animateLaser));*/


    auto moveUp = MoveBy::create(2, Vec2(2000,0));
    auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(ShipLaser::spriteMoveFinished, this));
    this->runAction(Sequence::create(moveUp, actionMoveDone, NULL));
   
    
    return true;
}

void ShipLaser::spriteMoveFinished(Node* sender)
{
    this->removeFromParentAndCleanup(true);
}




