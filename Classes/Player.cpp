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
	status = Status::Stand;

	return true;
}
