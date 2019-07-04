#include <algorithm>

#include"SelectUILayer.h"
#include"GameProcess.h"
using namespace cocos2d;

bool SelectUILayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Please choose one checkpoint", "fonts/sans.ttf", 30);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.8f);
	this->addChild(label, 1,"word");

	Process *p= Process::getInstance();
	int a = p->FileGet();

    float offset = 0.1f;
	for (int i = 1; i <= std::min(a + 1, 5); i++) {
		std::string filename = "Select/";
		filename += (char)(i + '0'); filename += ".png";
		auto sprite = Sprite::create(filename);
		sprite->setPosition(origin.x+visibleSize.width * offset,origin.y+visibleSize.height*0.6f);
		this->addChild(sprite);
		offset += 0.2f;
	}

	for (int i = a + 2; i <= 5; i++) {
		std::string filename_ = "Select/";
		filename_ += (char)(i + '0'); filename_ += "u.png";
		auto sprite_ = Sprite::create(filename_);
		sprite_->setPosition(origin.x + visibleSize.width * offset, origin.y + visibleSize.height*0.6f);
		this->addChild(sprite_);
		offset += 0.2f;
	}

	auto label_ = Label::createWithTTF("press 1 to the first checkpoint,2 to the second checkpoint and so on", "fonts/sans.ttf", 15);
	label_->setPosition(origin.x + visibleSize.width*0.7f, origin.y + visibleSize.height*0.1f);
	this->addChild(label_, 1, "tips");
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		auto keycode1 = EventKeyboard::KeyCode::KEY_1;
		auto keycode2 = EventKeyboard::KeyCode::KEY_2;
		auto keycode3 = EventKeyboard::KeyCode::KEY_3;
		auto keycode4 = EventKeyboard::KeyCode::KEY_4;
		auto keycode5 = EventKeyboard::KeyCode::KEY_5;

		Process *q = Process::getInstance();
		int a = q->FileGet();
		int b=static_cast<int>(code)-static_cast<int>(EventKeyboard::KeyCode::KEY_1);
		if (b > a) {
			
		}
		else if(code == keycode1) {
			//TODO
		}
		else if (code == keycode2) {
			//TODO
		}
		else if (code == keycode3) {
			//TODO
		}
		else if (code == keycode4) {
			//TODO
		}
		else if (code == keycode5) {
			//TODO
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
