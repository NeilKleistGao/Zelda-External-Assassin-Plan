#include <algorithm>

#include "Enemy.h"

using namespace cocos2d;

void Enemy::setVertices(const Vec2& v1, const Vec2& v2) {
	vertex1 = v1;
	vertex2 = v2;

	origion = v1;
	this->setPosition(v1.x, v1.y);
	                         /*define direction login*/
	if (vertex1.x == vertex2.x) {
		direction = (vertex1.y > vertex2.y) ? Direction::Down : Direction::Up;
	}
	else {
		direction = (vertex1.x < vertex2.x) ? Direction::Right : Direction::Left;
	}

	this->move();//Unit::move()
	this->schedule(schedule_selector(Enemy::patrol));//60fps
}

 void Enemy::patrol(float dt) {
	auto current = this->getPosition();//get the current Position
	Vec2 target = (origion == vertex1) ? vertex2 : vertex1;//get the target position
	
	if (origion.x == target.x) {

		this->setPositionX(origion.x);

		if (direction == Direction::Up && current.y >= target.y) {
			this->stop();//stop
			std::swap(target, origion);//swap the position
			direction = Down;//chage direction
			
		}
		else if (direction == Direction::Down && current.y <= target.y) {
			this->stop();
			std::swap(target, origion);
			direction = Up;
		}
	}
	else {

		this->setPositionY(origion.y);

		if (direction == Direction::Right && current.x >= target.x) {
			this->stop();
			std::swap(target, origion);
			direction = Left;
		}
		else if (direction == Direction::Left && current.x <= target.x) {
			this->stop();
			std::swap(target, origion);
			direction = Right;
		}
	}

	this->move();
}

Enemy* Enemy::create() {
	auto enemy = new(std::nothrow)Enemy();//create Enmey object

	if (enemy && enemy->init()) {
		enemy->autorelease();
	}
	else {
		delete enemy;
		enemy = nullptr;
	}

	return enemy;
}
Enemy* Enemy::create(const std::string& filename) {
	auto enemy = new(std::nothrow)Enemy();

	if (enemy&&enemy->initWithFile(filename)) {
		enemy->autorelease();
	}
	else {
		delete enemy;
		enemy = nullptr;
	}

	return enemy;
}
bool Enemy::init() {
	return Unit::init();
}
bool Enemy::initWithFile(const std::string& filename) {
	if (!Unit::initWithFile(filename)) {
		return false;
	}

	std::string type = filename.substr(filename.find("/") + 1).substr(0, 6);

	frameCount[type + "Down"] = frameCount[type + "Up"] = frameCount[type + "Left"] = frameCount[type + "Right"] = 2;
	status = Status::Stand;
	return true;
}
