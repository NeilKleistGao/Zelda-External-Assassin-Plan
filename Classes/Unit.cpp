#include "Unit.h"

using namespace cocos2d;

void Unit::move(Status s) {
	frameName = this->getName();

	if (s != status) {
		animationIndex = 0;
		status = s;
	}

	if (s == Status::Jump) {
		frameName += "Jump";
		speed = 225.0f;
	}
	else if (s == Status::Swim) {
		frameName += "Swim";
	}

	auto body = this->getPhysicsBody();

	switch (direction)
	{
	case Up:
		frameName += "Up";
		body->setVelocity(Vec2(0, speed));
		break;
	case Down:
		frameName += "Down";
		body->setVelocity(Vec2(0, -speed));
		break;
	case Left:
		frameName += "Left";
		body->setVelocity(Vec2(-speed, 0));
		break;
	case Right:
		frameName += "Right";
		body->setVelocity(Vec2(speed, 0));
		break;
	}
	
	isMoving = true;
}

void Unit::stop() {
	std::string frameName = this->getName();

	if (status == Status::Swim) {
		frameName += "Swim";
	}

	switch (direction)
	{
	case Up:
		frameName += "Up";
		break;
	case Down:
		frameName += "Down";
		break;
	case Left:
		frameName += "Left";
		break;
	case Right:
		frameName += "Right";
		break;
	}

	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "0");
	this->setSpriteFrame(frame);

	auto body = this->getPhysicsBody();
	body->setVelocity(Vec2::ZERO);
	isMoving = false;
}

bool Unit::init() {
	return BoxSprite::init();
}

bool Unit::initWithFile(const std::string& filename) {
	if (!BoxSprite::initWithFile(filename)) {
		return false;
	}

	this->schedule(schedule_selector(Unit::update), 1.0f);
	return true;
}

void Unit::update(float dt) {
	if (!isMoving) {
		timer = 0.0f;
		return;
	}

	timer += dt;

	if (timer >= animationDelta) {
		std::string realName = frameName + (char)(animationIndex + '0');
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(realName);
		this->setSpriteFrame(frame);

		if (status == Status::Jump && animationIndex + 1 == frameCount[frameName]) {
			this->status = Status::Stand;
			this->stop();
			speed = 150.0f;
		}

		animationIndex = (animationIndex + 1) % frameCount[frameName];

		timer = 0;
	}
}

int Unit::getDamage() {
	return damage;
}

bool Unit::hurt(int dmg) {
	HP -= dmg;
	return (HP <= 0);
}