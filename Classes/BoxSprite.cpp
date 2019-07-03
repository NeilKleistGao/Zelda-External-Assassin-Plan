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
	body->setRotationEnable(false);
	body->getShape(0)->setRestitution(0);
	body->getShape(0)->setDensity(1);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setMass(1);
	body->getShape(0)->setContactTestBitmask(1);
	this->setPhysicsBody(body);

	return true;
}