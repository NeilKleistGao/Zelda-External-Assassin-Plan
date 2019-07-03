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
	player->setName("player");
	player->setScale(2.5, 2.5);
	player->setPosition(100, 100);
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
	klistener->onKeyPressed = [player](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) noexcept {
		CCLOG("wryyyy");
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			player->setDirection(Unit::Direction::Left);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			player->setDirection(Unit::Direction::Right);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			player->setDirection(Unit::Direction::Down);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			player->setDirection(Unit::Direction::Up);
			break;
		}

		player->move(Unit::Status::Stand);
	};

	klistener->onKeyReleased = [player](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) noexcept {
		player->stop();
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(klistener, this);

	return true;
}

void GameLayer::onContactBegin(cocos2d::Node* node1, cocos2d::Node* node2) {
	CCLOG("%s <-> %s\n", node1->getName(), node2->getName());
}