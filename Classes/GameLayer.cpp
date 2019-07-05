#include <algorithm>
#include <cmath>

#include "GameLayer.h"
#include "Player.h"
#include "MapManager.h"
#include "PauseScene.h"
#include "Config.h"
#include "Enemy.h"

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

	//add player
	auto player = Player::create("Game/playerDown0.png");
	player->setName("player");
	player->setScale(3.5, 3.5);
	player->setPosition(map->getPlayerPosition());
	this->addChild(player, 1);

	auto shadow = Sprite::create("Game/shadow.png");
	shadow->setPosition(Vec2(origion.x + visibleSize.width / 2, origion.y + visibleSize.height / 2));
	shadow->setName("shadow");
	shadow->setOpacity(0);
	this->addChild(shadow, 20);

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

	klistener->onKeyReleased = [player](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event) {
		if (code == EventKeyboard::KeyCode::KEY_A || code == EventKeyboard::KeyCode::KEY_D
			|| code == EventKeyboard::KeyCode::KEY_S || code == EventKeyboard::KeyCode::KEY_W) {
			player->stop();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(klistener, this);

	this->schedule(schedule_selector(GameLayer::check));

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
		auto player = dynamic_cast<Player*>(node1);
		if (player->hasCollection("strengthGloove")) {
			node2->setTag(this->movableFlag);
			this->push();
		}
	}
	else if (node1->getName() == "player" && node2->getName() == "enemy") {
		//TODO:
	}
	else if (node1->getName() == "player" && node2->getName() == "trans") {
		auto pos = static_cast<std::pair<Vec2, Vec2>*>(node2->getUserData());
		auto player = dynamic_cast<Player*>(this->getChildByName("player"));
		player->setUserData(pos);

		this->schedule(schedule_selector(GameLayer::turnOff));
	}
}

void GameLayer::turnOff(float) {
	auto shadow = dynamic_cast<Sprite*>(this->getChildByName("shadow"));
	shadow->setOpacity(shadow->getOpacity() + 5);

	if (shadow->getOpacity() == 255) {
		auto player = dynamic_cast<Player*>(this->getChildByName("player"));
		auto pos = static_cast<std::pair<Vec2, Vec2>*>(player->getUserData());
		auto map = dynamic_cast<MapManager*>(this->getChildByName("map"));
		

		map->setPosition(map->getPositionX() + pos->first.x, map->getPositionY() + pos->first.y);
		map->setOffset(pos->first);
		player->setPosition(pos->second);

		this->schedule(schedule_selector(GameLayer::turnOff));

		this->unschedule(schedule_selector(GameLayer::turnOff));
		this->schedule(schedule_selector(GameLayer::turnOn));
	}
}

void GameLayer::turnOn(float) {
	auto shadow = dynamic_cast<Sprite*>(this->getChildByName("shadow"));
	shadow->setOpacity(shadow->getOpacity() - 5);

	if (shadow->getOpacity() == 0) {
		this->unschedule(schedule_selector(GameLayer::turnOn));
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
		node2->setTag(0);
	}
	else if (node1->getName() == "player" && node2->getName() == "enemy") {
		//TODO:
	}
}

void GameLayer::interact() {
	if (!this->isInteractable) {
		return;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto map = dynamic_cast<MapManager*>(this->getChildByName("map"));
	auto box = dynamic_cast<Sprite*>(map->getChildByTag(this->interactingFlag));
	auto player = dynamic_cast<Player*>(this->getChildByName("player"));

	box->setSpriteFrame(SpriteFrame::create("Game/boxOpen.png", Rect(0, 0, 64, 64)));

	std::string content = *static_cast<std::string*>(box->getUserData());
	auto offset = map->getOffset();

	if (content != "") {
		this->isMovable = false;

		std::string temp = content;
		temp += (player->getPositionY() >= visibleSize.height / 2) ? " 1024" : " 0";

		auto msg = String::createWithData((const unsigned char*)(temp.c_str()), temp.length());
		msg->retain();
		NotificationCenter::getInstance()->postNotification("show", msg);

		auto data = Config::getInstance()->getObject(content);
		auto pic = Sprite::create(data.image_path);
		pic->setScale(3, 3);
		pic->setPosition(box->getPositionX() + offset.x, box->getPositionY() + offset.y + pic->getBoundingBox().size.height / 2);
		pic->setName("temp");
		this->addChild(pic, 1);
		
		player->addCollection(content);

		content = "";
		box->setUserData(new std::string(content));
	}
	else {
		auto pic = this->getChildByName("temp");
		if (pic) {
			this->removeChild(pic, true);
			this->isMovable = true;
			NotificationCenter::getInstance()->postNotification("hide");
		}
	}
}

void GameLayer::push() {
	auto map = dynamic_cast<MapManager*>(this->getChildByName("map"));
	auto player = dynamic_cast<Player*>(this->getChildByName("player"));
	auto mov = map->getChildByTag(movableFlag);
	
	bool flag = false;
	Vec2 next = mov->getPosition(), offset = map->getOffset();
	switch(player->getDirection()) {
	case Unit::Direction::Up:
		flag = (player->getPositionY() - offset.y < mov->getPositionY() && abs(player->getPositionX() - offset.x - mov->getPositionX()) <= map->getTileSize() / 2);
		next.y += map->getTileSize();
		break;
	case Unit::Direction::Down:
		flag = (player->getPositionY() - offset.y > mov->getPositionY() && abs(player->getPositionX() - offset.x - mov->getPositionX()) <= map->getTileSize() / 2);
		next.y -= map->getTileSize();
		break;
	case Unit::Direction::Left:
		flag = (player->getPositionX() - offset.x > mov->getPositionX() && abs(player->getPositionY() - offset.y - mov->getPositionY()) <= map->getTileSize() / 2);
		next.x -= map->getTileSize();
		break;
	case Unit::Direction::Right:
		flag = (player->getPositionX() - offset.x < mov->getPositionX() && abs(player->getPositionY() - offset.y - mov->getPositionY()) <= map->getTileSize() / 2);
		next.x += map->getTileSize();
		break;
	}

	if (flag && map->isNull(next)) {
		map->resetMovableObject(mov->getPosition(), next);
		mov->setPosition(next);
		//mov->setTag(0);
	}
}

void GameLayer::check(float dt) {
	//TODO:
}