#include "Player.h"

Player* Player::create() {
	auto player = new(std::nothrow)Player();

	if (player && player->init()) {
		player->autorelease();
	}
	else {
		delete player;
		player = nullptr;
	}

	return player;
}

Player* Player::create(const std::string& filename) {
	auto player = new(std::nothrow)Player();

	if (player && player->initWithFile(filename)) {
		player->autorelease();
	}
	else {
		delete player;
		player = nullptr;
	}

	return player;
}

bool Player::init() {
	return Unit::init();
}

bool Player::initWithFile(const std::string& filename) {
	if (!Unit::initWithFile(filename)) {
		return false;
	}

	frameCount["playerDown"] = frameCount["playerUp"] = frameCount["playerLeft"] = frameCount["playerRight"] = 2;
	frameCount["playerSwimDown"] = frameCount["playerSwimUp"] = frameCount["playerSwimLeft"] = frameCount["playerSwimRight"] = 2;
	frameCount["playerJumpDown"] = frameCount["playerJumpUp"] = frameCount["playerJumpLeft"] = frameCount["playerJumpRight"] = 3;
	status = Status::Stand;

	return true;
}

int Player::getDamage() {
	if (this->hasCollection("doubleDamage")) {
		return this->damage * 2;
	}
	
	return this->damage;
}

void Player::cancelProtection(float dt) {
	this->isProtected = false;
}

bool Player::hurt(int dmg) {
	if (isProtected) {
		return false;
	}

	return Unit::hurt(dmg);
}