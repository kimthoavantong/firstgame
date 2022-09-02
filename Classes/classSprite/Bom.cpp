
#include "Bom.h"

USING_NS_CC;


Bom1* Bom1::createBom()
{
    return Bom1::create();
}

bool Bom1::init()
{
    if ( !Node::init() )
    {
        return false;
    }

    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Missile3.plist","Missile3.png");
    //spriteShipLaser = Sprite::createWithSpriteFrameName("Missile3_Fly1.png");
    //this->addChild(spriteShipLaser);

    spriteBom = Sprite::create("Bomb3Idle1.png");
    this->addChild(spriteBom);

    physicsBom = PhysicsBody::createBox(spriteBom->getContentSize());
    physicsBom->setDynamic(false);
    physicsBom->setContactTestBitmask(true);
    physicsBom->setCollisionBitmask(4);
    this->addComponent(physicsBom);

    /*Animate* animatePlay = Animate::create(Bom1::createAnimation("Missile3_Fly", 10, 0.1));
    spriteShipLaser->runAction(RepeatForever::create(animatePlay));*/

    auto moveUp = MoveBy::create(2, Vec2(-2000,0));
    auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(Bom1::spriteMoveFinished, this));
    this->runAction(Sequence::create(moveUp, actionMoveDone, NULL));
    
    return true;
}

void Bom1::spriteMoveFinished(Node* sender)
{
    this->removeFromParentAndCleanup(true);
}

Animation* Bom1::createAnimation(std::string tenFrame, int soFrame, float delay)
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






