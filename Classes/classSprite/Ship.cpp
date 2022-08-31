
#include "Ship.h"
#include "Definitions.h"

USING_NS_CC;


Ship* Ship::createShip()
{
    return Ship::create();
}

bool Ship::init()
{
    if ( !Node::init() )
    {
        return false;
    }

    checkBanDan = false;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spriteplane/plane.plist","spriteplane/plane.png");
    spriteShip = Sprite::createWithSpriteFrameName("Fly1.png");
    //this->schedule(schedule_selector(Ship::animatePlaneFly), 0.1);
    shipWidth = spriteShip->getContentSize().width;
    shipHeight = spriteShip->getContentSize().height;
    this->addChild(spriteShip);
    Ship::animatePlaneFly(0.1);

    
    

    physicsShip = PhysicsBody::createBox(spriteShip->getContentSize());
    physicsShip->setDynamic(false);
    physicsShip->setCollisionBitmask(1);
    physicsShip->setContactTestBitmask(true);
    this->addComponent(physicsShip);
   
    this->schedule(schedule_selector(Ship::animateBanDan), 0.1);
    

    return true;
}
int Ship::getHealth()
{
    return healthShip;
}
void Ship::setHealth(int x)
{
        healthShip -= x;
}
void Ship::animateBanDan(float)
{
    
    if (checkBanDan == true)
    {
        Vector <SpriteFrame*> aniFrame;
        aniFrame.reserve(5);
        aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Shoot1.png"));
        aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Shoot2.png"));
        aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Shoot3.png"));
        aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Shoot4.png"));
        aniFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Shoot5.png"));

        Animation* animationBanDan = Animation::createWithSpriteFrames(aniFrame, 0.05);
        Animate* animateBanDan = Animate::create(animationBanDan);
        spriteShip->runAction(Repeat::create(animateBanDan,1));
        checkBanDan = false;
    }
}

void Ship::animatePlaneFly(float dt)
{
    Vector <SpriteFrame*> aniFrameShip;
    aniFrameShip.reserve(2);
    aniFrameShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Fly1.png"));
    aniFrameShip.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Fly2.png"));
    Animation* animationShip = Animation::createWithSpriteFrames(aniFrameShip, 0.1);
    auto animateShip = Animate::create(animationShip);
    spriteShip->runAction(RepeatForever::create(animateShip));
}


