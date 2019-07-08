#include <algorithm>

#include "SelectUILayer.h"
#include "GameProcess.h"
#include "GameScene.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace experimental;

bool SelectUILayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	AudioEngine::stopAll();
	AudioEngine::play2d("music/select.mp3", true);//backgroud music

	// title words
	auto label = Label::createWithTTF("Please choose one checkpoint", "fonts/sans.ttf", 30);
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.8f);
	this->addChild(label, 1,"word");

	//Get current game progress
	Process *p = Process::getInstance();
	int a = p->FileGet();

	//Display a color map of all clearance levels
    float offset = 0.1f;
	for (int i = 1; i <= std::min(a + 1, 5); i++) {
		std::string filename = "Select/";
		filename += (char)(i + '0'); filename += ".png";
		auto sprite = Sprite::create(filename);
		sprite->setPosition(origin.x+visibleSize.width * offset,origin.y+visibleSize.height*0.6f);
		this->addChild(sprite);
		offset += 0.2f;
	}

	//Display a grey map of all  unclearance levels
	for (int i = a + 2; i <= 5; i++) {
		std::string filename_ = "Select/";
		filename_ += (char)(i + '0'); filename_ += "u.png";
		auto sprite_ = Sprite::create(filename_);
		sprite_->setPosition(origin.x + visibleSize.width * offset, origin.y + visibleSize.height*0.6f);
		this->addChild(sprite_);
		offset += 0.2f;
	}
	
    //Press the corresponding button on the keyboard to enter the corresponding level
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		Process *q = Process::getInstance();
		int rec = q->FileGet();
		int sel = static_cast<int>(code) - static_cast<int>(EventKeyboard::KeyCode::KEY_1);

		if (sel <= rec && sel >= 0) {
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene(sel + 1)));
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
