#include"SelectUILayer.h"
using namespace cocos2d;

bool SelectUILayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//background image

	//blink infomation
	

	//add keyboard event

	//add schedule

	return true;
}

void SelectUILayer::update(float dt) {
	//TODO;
}