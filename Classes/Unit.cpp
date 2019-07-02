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