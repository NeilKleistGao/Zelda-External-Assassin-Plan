#include <iostream>
#include "GameUILayer.h"
#include "MessageBox.h"

using namespace cocos2d;

GameUILayer::~GameUILayer() {
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool GameUILayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto box = InteractionMessageBox::create();
	box->setPosition(Vec2::ZERO);
	box->setName("box");
	this->addChild(box);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameUILayer::recieveAndShow), "show", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameUILayer::recieveAndHide), "hide", nullptr);

	return true;
}

void GameUILayer::recieveAndShow(Ref* msg) {
	std::string str = dynamic_cast<String*>(msg)->getCString();
	auto box = dynamic_cast<InteractionMessageBox*>(this->getChildByName("box"));

	int space = str.find('*');
	std::string name = str.substr(0, space), pos = str.substr(space + 1);
	box->show(atof(pos.c_str()), name);
}

void GameUILayer::recieveAndHide(Ref*) {
	auto box = dynamic_cast<InteractionMessageBox*>(this->getChildByName("box"));
	box->hide();
}
