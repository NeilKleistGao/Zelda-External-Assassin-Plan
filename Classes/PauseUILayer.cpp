#include "PauseUILayer.h"
#include<string.h>
#include<vector>
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

    auto label = Label::createWithTTF("PAUSE", "fonts/sans.ttf", 40);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.9f);
	this->addChild(label, 1, "pause");

	auto sprite1 = Sprite::create("pause/bullet.png");
	sprite1->setScale(0.2, 0.2);
	sprite1->setPosition(origin.x + visibleSize.width*0.8f, origin.y + visibleSize.height*0.95f);
	this->addChild(sprite1);

	auto sprite2 = Sprite::create("pause/Blood.png");
	sprite2->setScale(2.5, 2.5);
	sprite2->setPosition(origin.x + visibleSize.width*0.8f, origin.y + visibleSize.height*0.85f);
	this->addChild(sprite2);

	std::vector<std::string> v1{ "Game/key1.png","Game/key2.png" };
	float offset = 0.1f;
	for (auto a = v1.begin(); a != v1.end(); a++) {
		auto sprite_ = Sprite::create(*a);
		sprite_->setPosition(origin.x + visibleSize.width*offset, origin.y + visibleSize.height*0.5f);
		this->addChild(sprite_);
		offset += 0.1f;
	}	
	auto klistener_ = EventListenerKeyboard::create();
	klistener_->onKeyPressed = [](cocos2d::EventKeyboard::KeyCode code_, cocos2d::Event* event) {
		if (code_ == EventKeyboard::KeyCode::KEY_ESCAPE) {
			Director::sharedDirector()->popScene();
		}
	};
	klistener_->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode code_, cocos2d::Event* event) {
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(klistener_, this);
	
	return true;
}

