#include <string.h>
#include <vector>
#include "Player.h"
#include "PauseUILayer.h"
#include "Config.h"

using namespace cocos2d;

bool PauseUILayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//background
	auto backgound = Sprite::create("pause/back.png");
	backgound->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 2));
	this->addChild(backgound, 0);

	auto sprite1 = Sprite::create("pause/bullet.png");
	sprite1->setScale(2.5,2.5);
	sprite1->setPosition(origin.x + visibleSize.width*0.8f, origin.y + visibleSize.height*0.95f);
	this->addChild(sprite1);

	auto lableBullet = Label::createWithTTF("", "fonts/sans.ttf", 20);
	lableBullet->setPosition(origin.x + visibleSize.width *0.9f, origin.y + visibleSize.height*0.95f);
	this->addChild(lableBullet, 1, "bullet");

	auto sprite2 = Sprite::create("pause/Blood.png");
	sprite2->setScale(2.5, 2.5);
	sprite2->setPosition(origin.x + visibleSize.width*0.8f, origin.y + visibleSize.height*0.85f);
	this->addChild(sprite2);

	auto HP = Label::createWithTTF("", "fonts/sans.ttf", 20);
	HP->setPosition(origin.x + visibleSize.width *0.9f, origin.y + visibleSize.height*0.85f);
	this->addChild(HP, 1, "HP");
	
	auto klistener = EventListenerKeyboard::create();
	klistener->onKeyPressed = [](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE) {
			NotificationCenter::getInstance()->postNotification("resume", nullptr);
			Director::getInstance()->popScene();
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(klistener, this);
	
	return true;
}

void PauseUILayer::recievePlayerData(Player* player) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto bullet = dynamic_cast<Label*>(this->getChildByName("bullet"));
	auto HP = dynamic_cast<Label*>(this->getChildByName("HP"));

	bullet->setString(std::to_string(player->getBullet()));
	HP->setString(std::to_string(player->getHP()));

	auto collection = player->getAllCollection();
	float offset = 0.1f;

	for (auto a = collection.begin(); a != collection.end(); a++) {
		auto sprite = Sprite::create(Config::getInstance()->getObject(*a).image_path);
		sprite->setScale(3, 3);
		sprite->setPosition(origin.x + visibleSize.width * offset, origin.y + visibleSize.height * 0.5f);
		this->addChild(sprite);
		offset += 0.1f;
	}
}