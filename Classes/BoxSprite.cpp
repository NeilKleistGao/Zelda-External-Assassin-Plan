#include "BoxSprite.h"

using namespace cocos2d;

BoxSprite* BoxSprite::create(const std::string& filename) {
	auto sprite = new(std::nothrow)BoxSprite();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->autorelease();
	}
	else {
		delete sprite;
		sprite = nullptr;
	}

	return sprite;
}

bool BoxSprite::initWithFile(const std::string& filename) {
	if (!Sprite::initWithFile(filename)) {
		return false;
	}

	auto body = PhysicsBody::createBox(Size(this->getBoundingBox().size));
	this->setPhysicsBody(body);

	return true;
}