#include "MessageBox.h"
#include"Config.h"
using namespace cocos2d;

bool InteractionMessageBox::init() {
	if (!Node::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto messageBox = Sprite::create("Message/1.png");
	this->addChild(messageBox, 1, "box");
	messageBox->setVisible(false);

	
	auto label = Label::createWithTTF("   ", "fonts/sans.ttf", 15);
	this->addChild(label, 1, "congratulations");
	label->setVisible(false);

	return true;
}


void InteractionMessageBox::show(bool isLow,const std::string& name) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto box = Node::getChildByName("box");

	auto label = dynamic_cast<Label*>(this->getChildByName("congratulations"));
	std::string s = Config::getInstance()->getObject(name).info_text;
	for (int i = 0; i < sizeof(s); i++) {
		if (i == 16) {
			s = s.insert(i, "\n");
		}
	}

	label->setString(s);
	label->setAnchorPoint(Vec2::ZERO);

	if (isLow) {
		box->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.875f);
		label->setPosition(origin.x + visibleSize.width*0.305f, origin.y + visibleSize.height*0.95f);
	}
	else {
		box->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.125f);
		label->setPosition(origin.x + visibleSize.width*0.305f, origin.y + visibleSize.height*0.195f);
		
	}

	box->setVisible(true);
	label->setVisible(true);
}

void InteractionMessageBox::hide() {
	Node* messageBox = Node::getChildByName("box");
	Node* label = Node::getChildByName("congratulations");

	messageBox->setVisible(false);
	label->setVisible(false);
}