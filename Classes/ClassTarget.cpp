
#include "Definitions.h"
#include "ClassTarget.h"

USING_NS_CC;

TargetSprite::TargetSprite()
{
    spriteDan = Sprite::create(ClassShip_Sprite_Ship);
    auto edge2 = PhysicsBody::createBox(spriteDan->getContentSize());
    edge2->setDynamic(false);
    edge2->setCollisionBitmask(9);
    edge2->setContactTestBitmask(true);
    spriteDan->setTag(9);
    spriteDan->setPhysicsBody(edge2);
	this->addChild(spriteDan,10);
}
TargetSprite::~TargetSprite()
{

}
float TargetSprite::getDanContentWidth()
{
    static float itemWidth = 0;
    if (0 == itemWidth) {
        Sprite* sprite = CCSprite::create(ClassShip_Sprite_Ship);
        itemWidth = sprite->getContentSize().width;
    }
    return itemWidth;
}
float TargetSprite::getDanContentHeight()
{
    static float itemHeight = 0;
    if (0 == itemHeight) {
        Sprite* sprite = CCSprite::create(ClassShip_Sprite_Ship);
        itemHeight = sprite->getContentSize().height;
    }
    return itemHeight;
}



