#include "GameLayer.h"
#include "Player.h"

using namespace cocos2d;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();

	//add physics box
	auto edge = PhysicsBody::createEdgeBox(visibleSize);
	edge->setContactTestBitmask(1);

	auto node = Node::create();
	node->setPosition(origion.x + visibleSize.width / 2, origion.y + visibleSize.height / 2);
	node->setPhysicsBody(edge);
	this->addChild(node);

	//add player
	auto player = Player::create("Game/playerDown0.png");
	player->setScale(5, 5);
	player->setPosition(10, 10);
	this->addChild(player);

	//add contact call back function
	auto plistener = EventListenerPhysicsContact::create();
	plistener->onContactBegin = [this](PhysicsContact& cont) -> bool {
		onContactBegin(cont.getShapeA()->getBody()->getNode(), cont.getShapeB()->getBody()->getNode());
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(plistener, this);

	//add keyboard call back function
	auto klistener = EventListenerKeyboard::create();
	klistener->onKeyPressed = [player](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			break;
		}
	};
	klistener->onKeyReleased = [player](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(klistener, this);

	return true;
}

void GameLayer::onContactBegin(cocos2d::Node* node1, cocos2d::Node* node2) {
	CCLOG("%s <-> %s\n", node1->getName(), node2->getName());
}