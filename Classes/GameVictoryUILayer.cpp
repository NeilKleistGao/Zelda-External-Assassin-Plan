#include "GameVictoryUILayer.h"
#include"SelectScene.h"
#include"GameProcess.h"
using namespace cocos2d;

bool GameVictoryUILayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("Game/Victory.png");
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background, 0);

	auto label = Label::createWithTTF("Press Any Key To Continue...", "fonts/sans.ttf", 24);
	label->setColor(cocos2d::Color3B(47 ,79, 79));
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.2f);
	this->addChild(label, 1,"Victory" );


	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SelectScene::createScene()));
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//add schedule
	this->schedule(schedule_selector(GameVictoryUILayer::Refresh, 1f));
	return true;
}

void GameVictoryUILayer::Refresh(float dt) {
	auto label = this->getChildByName("Victory");
	label->setVisible(!label->isVisible());
}
void GameVictoryUILayer::DataRetore(){
	Process::getInstance()->FileModify();

}