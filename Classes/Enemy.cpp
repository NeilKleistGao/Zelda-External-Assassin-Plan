#include "Enemy.h"

using namespace cocos2d;

void Enemy::setVertices(const Vec2& v1, const Vec2& v2) {
	vertex1 = v1;
	vertex2 = v2;

	origion = v1;
	this->setPosition(v1.x, v1.y);

	if (vertex1.x == vertex2.x) {
		direction = (vertex1.y > vertex2.y) ? Direction::Down : Direction::Up;
	}
	else {
		direction = (vertex1.x > vertex2.x) ? Direction::Right : Direction::Left;
	}

	this->move();
	this->schedule(schedule_selector(Enemy::patrol));
}

 void Enemy::patrol(float dt) {
	auto current = this->getPosition();
	Vec2 target = (origion == vertex1) ? vertex2 : vertex1;
	
	if (origion.x == target.x) {
		if (direction == Direction::Up && current.y >= target.y) {
			direction = Down;
		}
		else if (direction == Direction::Down && current.y <= target.y) {
			direction = Up;
		}
	}
	else {
		if (direction == Direction::Right && current.x >= target.x) {
			direction = Left;
		}
		else if (direction == Direction::Left && current.x <= target.x) {
			direction = Right;
		}
		
	}
}

Enemy* Enemy::create() {
	auto enemy = new(std::nothrow)Enemy();

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
	frameCount["EnemyDown"] = frameCount["EnemyUp"] = frameCount["EnmeyLeft"] = frameCount["EnmeyRight"] = 2;
	status = Status::Stand;
	return true;
}
