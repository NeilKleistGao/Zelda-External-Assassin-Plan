#include <cctype>
#include "MessageBox.h"
#include "Config.h"

using namespace cocos2d;

bool InteractionMessageBox::init() {
	if (!Node::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto messageBox = Sprite::create("Message/1.png");//create a message box
	this->addChild(messageBox, 1, "box");
	messageBox->setVisible(false);

	//create a lebal which show in message box.
	auto label = Label::createWithTTF("   ", "fonts/sans.ttf", 12);
	this->addChild(label, 1, "congratulations");
	label->setVisible(false);

	return true;
}


void InteractionMessageBox::show(float y,const std::string& name) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto box = Node::getChildByName("box");

	auto label = dynamic_cast<Label*>(this->getChildByName("congratulations"));
	std::string s = "";

	if (name.substr(0, 3) != "You") {
		s = Config::getInstance()->getObject(name).info_text;
	}
	else {
		s = name;
	}
	//Wrap the displayed information.
	for (int i = 0; i < s.length(); i++) {
		if (i % 42 == 0) {
			std::string temp = "\n";
			if (i > 0 && i < s.length() && std::isalpha(s[i - 1]) && std::isalpha(s[i])) {
				temp = "-\n";
			}
			s = s.insert(i, temp);
		}
	}

	label->setString(s);
	label->setAnchorPoint(Vec2::ZERO);

	//Set the corresponding location of the messagebox according to the location of the NPC
	if (y <= visibleSize.height / 2) {
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
	Node* messageBox = getChildByName("box");
	Node* label = getChildByName("congratulations");

	messageBox->setVisible(false);//hide the box
	label->setVisible(false);//hide the label
}