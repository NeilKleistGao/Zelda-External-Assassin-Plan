#include "HelloWorldUILayer.h"

using namespace cocos2d;

bool HelloWorldUILayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//background image
	auto backgound = Sprite::create("HelloWorld/background.png");
	backgound->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(backgound, 0);

	//blink infomation
	auto label = Label::createWithTTF("Press Any Key To Continue...", "fonts/sans.ttf", 24);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.2f);
	this->addChild(label, 1, "info");

	//add keyboard event
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		//TODO:
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//add schedule
	this->schedule(schedule_selector(HelloWorldUILayer::update), 0.6f);

	return true;
}

void HelloWorldUILayer::update(float dt) {
	auto label = this->getChildByName("info");
	label->setVisible(!label->isVisible());
}