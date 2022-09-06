
#include "ShipLaser.h"

USING_NS_CC;
int dameDanOne;
ShipLaser* ShipLaser::createShipLaser(int a)
{
    dameDanOne = a;
    return ShipLaser::create();
}

bool ShipLaser::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    if (dameDanOne == 1)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dan1.plist", "dan1.png");
        spriteShipLaser = Sprite::createWithSpriteFrameName("dan11.png");
        this->addChild(spriteShipLaser);

        physicsLaser = PhysicsBody::createBox(spriteShipLaser->getContentSize());
        physicsLaser->setDynamic(false);
        physicsLaser->setContactTestBitmask(true);
        physicsLaser->setCollisionBitmask(2);
        this->addComponent(physicsLaser);

        auto moveUp = MoveBy::create(2, Vec2(2000, 0));
        auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(ShipLaser::spriteMoveFinished, this));
        this->runAction(Sequence::create(moveUp, actionMoveDone, NULL));
    }
    else if (dameDanOne >= 2)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Missile.plist", "Missile.png");
        spriteShipLaser = Sprite::createWithSpriteFrameName("Missile3_Fly1.png");
        this->addChild(spriteShipLaser);

        Animate* animatePlay = Animate::create(ShipLaser::createAnimation("Missile3_Fly", 10, 0.1));
        spriteShipLaser->runAction(RepeatForever::create(animatePlay));

        physicsLaser = PhysicsBody::createBox(spriteShipLaser->getContentSize());
        physicsLaser->setDynamic(false);
        physicsLaser->setContactTestBitmask(true);
        physicsLaser->setCollisionBitmask(2);
        this->addComponent(physicsLaser);

        auto moveUp = MoveBy::create(2, Vec2(2000, 0));
        auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(ShipLaser::spriteMoveFinished, this));
        this->runAction(Sequence::create(moveUp, actionMoveDone, NULL));
    }
    
   
    return true;
}

void ShipLaser::spriteMoveFinished(Node* sender)
{
    this->removeFromParentAndCleanup(true);
}

Animation* ShipLaser::createAnimation(std::string tenFrame, int soFrame, float delay)
{
    Vector <SpriteFrame*> frameAni;
    for (int i = 1; i <= soFrame; i++)
    {
        char buff[20] = { 0 };
        sprintf(buff, "%d.png", i);
        std::string str = tenFrame + buff;
        auto addframe = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        frameAni.pushBack(addframe);
    }
    Animation* animationPlay = Animation::createWithSpriteFrames(frameAni, delay);
    return animationPlay;
}
void ShipLaser::animateNo()
{
    if (dameDanOne == 1)
    {
        this->stopAllActions();
        spriteShipLaser->stopAllActions();
        Animate* animatePlay = Animate::create(ShipLaser::createAnimation("dan1", 8, 0.01));
        auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(ShipLaser::spriteMoveFinished, this));
        spriteShipLaser->runAction(Sequence::create(animatePlay, actionMoveDone, nullptr));
    }  
    else if (dameDanOne >= 2)
    {
        this->stopAllActions();
        spriteShipLaser->stopAllActions();
        Animate* animatePlay = Animate::create(ShipLaser::createAnimation("Missile3_No", 9, 0.01));
        auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(ShipLaser::spriteMoveFinished, this));
        spriteShipLaser->runAction(Sequence::create(animatePlay, actionMoveDone, nullptr));
    }
}







