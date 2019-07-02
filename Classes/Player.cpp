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
	return Unit::initWithFile(filename);
}