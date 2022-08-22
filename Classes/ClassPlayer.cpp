#include "ClassPlayer.h"
#include "Definitions.h"

USING_NS_CC;


PlayerSprite::PlayerSprite()
{
	spritePlayer = Sprite::create(ClassPlayer_Sprite_spritePlayer);
    auto edge2 = PhysicsBody::createBox(spritePlayer->getContentSize());
    edge2->setDynamic(false);
    edge2->setCollisionBitmask(1);
    edge2->setContactTestBitmask(true);
    spritePlayer->setPhysicsBody(edge2);
    spritePlayer->setTag(1);
	this->addChild(spritePlayer,10);
}
PlayerSprite::~PlayerSprite()
{

}
float PlayerSprite::getContentWidth()
{
    static float itemWidth = 0;
    if (0 == itemWidth) {
        Sprite* sprite = CCSprite::create(ClassPlayer_Sprite_spritePlayer);
        itemWidth = sprite->getContentSize().width;
    }
    return itemWidth;
}
float PlayerSprite::getContentHeight()
{
    static float itemHeight = 0;
    if (0 == itemHeight) {
        Sprite* sprite = CCSprite::create(ClassPlayer_Sprite_spritePlayer);
        itemHeight = sprite->getContentSize().height;
    }
    return itemHeight;
}



