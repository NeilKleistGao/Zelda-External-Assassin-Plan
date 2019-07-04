#include <algorithm>

#include "GameLayer.h"
#include "Player.h"
#include "MapManager.h"
#include "PauseScene.h"
#include "Config.h"

using namespace cocos2d;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	this->isInteractable = false;
	this->isMovable = true;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();

	//add map
	auto map = MapManager::create(1);
	map->setPosition(Vec2::ZERO);
	map->setName("map");
	this->addChild(map, 0);

	//add physics box
	auto edge = PhysicsBody::createEdgeBox(
		Size(visibleSize.width - map->getTileSize() * 2, visibleSize.height - map->getTileSize() * 2));
	edge->setContactTestBitmask(1);
	edge->setDynamic(false);

	auto node = Node::create();
	node->setPosition(origion.x + visibleSize.width / 2, origion.y + visibleSize.height / 2);
	node->setPhysicsBody(edge);
	node->setName("edge");
	this->addChild(node);

	//add player
	auto player = Player::create("Game/playerDown0.png");
	player->setName("player");
	player->setScale(4, 4);
	player->setPosition(map->getPlayerPosition());
	this->addChild(player, 1);

	//add contact call back function
	auto plistener = EventListenerPhysicsContact::create();
	plistener->onContactBegin = [this](PhysicsContact& cont) -> bool {
		cont.getShapeA()->getBody()->resetForces();
		cont.getShapeB()->getBody()->resetForces();
		this->onContactBegin(cont.getShapeA()->getBody()->getNode(), cont.getShapeB()->getBody()->getNode());
		return true;
	};

	plistener->onContactSeparate = [this](PhysicsContact& cont) {
		cont.getShapeA()->getBody()->resetForces();
		cont.getShapeB()->getBody()->resetForces();
		this->onContactEnd(cont.getShapeA()->getBody()->getNode(), cont.getShapeB()->getBody()->getNode());
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(plistener, this);

	//add keyboard call back function
	auto klistener = EventListenerKeyboard::create();
	klistener->onKeyPressed = [player,this](EventKeyboard::KeyCode code, Event* event) noexcept {
		if (this->isMovable) {
			switch (code)
			{
			case EventKeyboard::KeyCode::KEY_A:
				player->setDirection(Unit::Direction::Left);
				player->move(Unit::Status::Stand);
				break;
			case EventKeyboard::KeyCode::KEY_D:
				player->setDirection(Unit::Direction::Right);
				player->move(Unit::Status::Stand);
				break;
			case EventKeyboard::KeyCode::KEY_S:
				player->setDirection(Unit::Direction::Down);
				player->move(Unit::Status::Stand);
				break;
			case EventKeyboard::KeyCode::KEY_W:
				player->setDirection(Unit::Direction::Up);
				player->move(Unit::Status::Stand);
				break;
			}
		}

		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_J:
			//interact
			this->interact();
			break;
		case EventKeyboard::KeyCode::KEY_K:
			//jump
			break;
		case EventKeyboard::KeyCode::KEY_L:
			this->push();
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			RenderTexture *renderTexture = RenderTexture::create(1024, 768);
			renderTexture->begin();
			this->getParent()->visit();
			renderTexture->end();
			//pause game
			Director::getInstance()->pushScene((Scene*)renderTexture);
			Scene *scene = PauseScene::createScene();
			Director::getInstance()->replaceScene(scene); 
			break;
		}
	};

	klistener->onKeyReleased = [player](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) noexcept {
		if (code == EventKeyboard::KeyCode::KEY_A || code == EventKeyboard::KeyCode::KEY_D
			|| code == EventKeyboard::KeyCode::KEY_S || code == EventKeyboard::KeyCode::KEY_W) {
			player->stop();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(klistener, this);

	return true;
}


void GameLayer::onContactBegin(cocos2d::Node* node1, cocos2d::Node* node2) {
	CCLOG("%s <-> %s\n", node1->getName().c_str(), node2->getName().c_str());

	if (node2->getName() == "player") {
		std::swap(node1, node2);
	}

	if (node1->getName() == "player" && node2->getName() == "box") {
		node2->setTag(this->interactingFlag);
		this->isInteractable = true;
	}
	else if (node1->getName() == "player" && node2->getName() == "mov") {
		auto player = dynamic_cast<Player*>(this->getChildByName("player"));
		if (player->hasCollection("strengthGloove")) {
			this->isMovable = false;
		}
	}
	else if (node1->getName() == "player" && node2->getName() == "enemy") {
		//TODO:
	}
}

void GameLayer::onContactEnd(cocos2d::Node* node1, cocos2d::Node* node2){
	if (node2->getName() == "player") {
		std::swap(node1, node2);
	}

	if (node1->getName() == "player" && node2->getName() == "box") {
		node2->setTag(0);
		this->isInteractable = false;
	}
	else if (node1->getName() == "player" && node2->getName() == "mov") {
		this->isMovable = false;
	}
	else if (node1->getName() == "player" && node2->getName() == "enemy") {
		//TODO:
	}
}

void GameLayer::interact() {
	if (!this->isInteractable) {
		return;
	}
	
	auto map = this->getChildByName("map");
	auto box = dynamic_cast<Sprite*>(map->getChildByTag(this->interactingFlag));
	box->setSpriteFrame(SpriteFrame::create("Game/boxOpen.png", Rect(0, 0, 64, 64)));

	std::string content = *static_cast<std::string*>(box->getUserData());

	if (content != "") {
		this->isMovable = false;

		auto data = Config::getInstance()->getObject(content);
		auto pic = Sprite::create(data.image_path);
		pic->setScale(3, 3);
		pic->setPosition(box->getPositionX(), box->getPositionY() + pic->getBoundingBox().size.height / 2);
		pic->setName("temp");
		this->addChild(pic, 1);

		auto player = dynamic_cast<Player*>(this->getChildByName("player"));
		player->addCollection(content);

		content = "";
		box->setUserData(new std::string(content));
	}
	else {
		auto pic = this->getChildByName("temp");
		if (pic) {
			this->removeChild(pic, true);
			this->isMovable = true;
		}
	}
}

void GameLayer::push() {

}