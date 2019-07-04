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




void InteractionMessageBox::show(int y,const std::string& name) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	if (y < origin.y+visibleSize.height/2) {
		Node* box = Node::getChildByName("box");
		box->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.875f);
		box->setVisible(true);

		auto label = dynamic_cast<Label*>(this->getChildByName("congratulations"));
		std::string s = Config::getInstance()->getObject(name).info_text;
		for (int i = 0; i < sizeof(s);i++) {
			if (i == 16) {
				s = s.insert(i, "\n");
			}
        }
		label->setString(s);
		label->setPosition(origin.x + visibleSize.width*0.41f, origin.y + visibleSize.height*0.97f);
		label->setVisible(true);

	}
	else if (y > origin.y + visibleSize.height / 2) {
		Node* box_ = Node::getChildByName("box");
		box_->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.125f);
		box_->setVisible(true);
		
		auto label_ = dynamic_cast<Label*>(this->getChildByName("congratulations"));
		std::string s_ = Config::getInstance()->getObject(name).info_text;
		for (int i = 0; i < sizeof(s_); i++) {
			if (i == 16) {
				s_ = s_.insert(i, "\n");
			}
		}
		label_->setString(s_);
		label_->setPosition(origin.x + visibleSize.width*0.41f, origin.y + visibleSize.height*0.225f);
		label_->setVisible(true);
	}
}

void InteractionMessageBox::hide() {
	Node* messageBox = Node::getChildByName("box");
	Node* label = Node::getChildByName("congratulations");

	messageBox->setVisible(false);
	label->setVisible(false);
}