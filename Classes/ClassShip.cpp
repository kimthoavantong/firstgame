
#include "Definitions.h"
#include "ClassShip.h"

USING_NS_CC;

ShipSprite::ShipSprite()
{
	spriteShip = Sprite::create(ClassShip_Sprite_Ship);
    auto edge2 = PhysicsBody::createBox(spriteShip->getContentSize());
    edge2->setDynamic(false);
    edge2->setCollisionBitmask(7);
    edge2->setContactTestBitmask(true);
    spriteShip->setTag(7);
    spriteShip->setPhysicsBody(edge2);
	this->addChild(spriteShip,10);
}
ShipSprite::~ShipSprite()
{

}
float ShipSprite::getShipContentWidth()
{
    static float itemWidth = 0;
    if (0 == itemWidth) {
        Sprite* sprite = CCSprite::create(ClassShip_Sprite_Ship);
        itemWidth = sprite->getContentSize().width;
    }
    return itemWidth;
}
float ShipSprite::getShipContentHeight()
{
    static float itemHeight = 0;
    if (0 == itemHeight) {
        Sprite* sprite = CCSprite::create(ClassShip_Sprite_Ship);
        itemHeight = sprite->getContentSize().height;
    }
    return itemHeight;
}



