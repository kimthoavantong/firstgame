
#include "Definitions.h"
#include "ClasDan.h"

USING_NS_CC;

DanSprite::DanSprite()
{
    spriteDan = Sprite::create(ClassDan_Sprite_Dan);
    auto edge2 = PhysicsBody::createBox(spriteDan->getContentSize());
    edge2->setDynamic(false);
    edge2->setCollisionBitmask(8);
    edge2->setContactTestBitmask(true);
    spriteDan->setTag(8);
    spriteDan->setPhysicsBody(edge2);
	this->addChild(spriteDan,10);
}
DanSprite::~DanSprite()
{

}
float DanSprite::getDanContentWidth()
{
    static float itemWidth = 0;
    if (0 == itemWidth) {
        Sprite* sprite = CCSprite::create(ClassDan_Sprite_Dan);
        itemWidth = sprite->getContentSize().width;
    }
    return itemWidth;
}
float DanSprite::getDanContentHeight()
{
    static float itemHeight = 0;
    if (0 == itemHeight) {
        Sprite* sprite = CCSprite::create(ClassDan_Sprite_Dan);
        itemHeight = sprite->getContentSize().height;
    }
    return itemHeight;
}



