#include "PauseUILayer.h"
using namespace cocos2d;
bool PauseUILayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//background
	auto backgound = Sprite::create("pause/back.png");
	//backgound->setScale(2,2);
	backgound->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2));
	this->addChild(backgound, 0);

	// objects
	float offset = 0.1f;
	for (int i = 1; i <= 6; i++) {
		std::string filename = "Game/key";
		filename += (char)(i + '0'); filename += ".png";
		auto sprite = Sprite::create(filename);
		sprite->setPosition(origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height*offset);
		this->addChild(sprite);
		offset += 0.13f;
	}

	float offset_ = 0.1f;
	for (int i = 1; i <= 6; i++) {
		std::string filename_ = "Game/P";
		filename_ += (char)(i + '0'); filename_ += ".png";
		auto sprite_ = Sprite::create(filename_);
		sprite_->setPosition(origin.x + visibleSize.width * 0.6f, origin.y + visibleSize.height*offset_);
		this->addChild(sprite_);
		offset_+= 0.13f;
	}

	auto label = Label::createWithTTF("PAUSE", "fonts/sans.ttf", 40);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.9f);
	this->addChild(label, 1, "pause");

	return true;
}

