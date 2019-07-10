#include "Player.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace experimental;

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

	auto cache = SpriteFrameCache::getInstance();
	

	status = Status::Stand;

	this->schedule(schedule_selector(Player::blink), 0.5f);

	return true;
}

int Player::getDamage() {
	if (this->hasCollection("doubleDamage")) {
		return this->damage * 2;
	}
	
	return this->damage;
}

bool Player::hurt(int dmg) {
	if (isProtected) {
		return false;
	}

	if (dmg > 0) {
		AudioEngine::play2d("music/hurt.mp3", false, 0.5f);
	}
	
	return Unit::hurt(dmg);
}

void Player::blink(float) {
	if (!isProtected) {
		return;
	}

	if (this->getColor() == Color3B::RED) {
		this->setColor(Color3B::WHITE);
	}
	else {
		this->setColor(Color3B::RED);
	}
}