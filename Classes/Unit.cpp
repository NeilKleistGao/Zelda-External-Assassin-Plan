#include "Unit.h"

using namespace cocos2d;
using namespace extension;

void Unit::move(const Direction& dir) {
	switch (dir)
	{
	case Up:
		this->setPositionY(this->getPositionY() + this->speed);
		break;
	case Down:
		this->setPositionY(this->getPositionY() - this->speed);
		break;
	case Left:
		this->setPositionX(this->getPositionX() - this->speed);
		break;
	case Right:
		this->setPositionX(this->getPositionX() + this->speed);
		break;
	}
}

bool Unit::init() {
	return PhysicsSprite::init();
}

bool Unit::initWithFile(const std::string& filename) {
	return PhysicsSprite::initWithFile(filename);
}

void Unit::play(std::string name, int count) {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name + ".plist");
	Vector<AnimationFrame*> frames;

	char temp[64];
	for (int i = 0; i < count; i++) {
		sprintf(temp, (name + "%d.png").c_str(), i);
		frames.pushBack(AnimationFrame::create(SpriteFrameCache::getInstance()->getSpriteFrameByName(temp), 1, ValueMap()));
	}

	auto anim = Animate::create(Animation::create(frames, 0.1f, 1));
	this->runAction(RepeatForever::create(anim));
}