#include <algorithm>
#include <cmath>

#include "GameLayer.h"
#include "Player.h"
#include "MapManager.h"
#include "PauseScene.h"
#include "Config.h"
#include "Enemy.h"
#include "SelectScene.h"
#include "Bullet.h"
#include "GameVictoryScene.h"
#include "GameProcess.h"
#include "PauseUILayer.h"
#include "audio/include/AudioEngine.h"
#include "Debuger.h"

using namespace cocos2d;
using namespace experimental;

GameLayer::~GameLayer() {
	NotificationCenter::getInstance()->removeAllObservers(this);
}

GameLayer* GameLayer::create(int level) {
	auto layer = new(std::nothrow) GameLayer();
	if (layer && layer->init(level)) {
		layer->autorelease();
	}
	else if (layer) {
		delete layer;
		layer = nullptr;
	}

	return layer;
}

bool GameLayer::init(int level) {
	if (!Layer::init()) {
		return false;
	}

	currentLevel = level;

	this->isInteractable = false;
	this->isMovable = true;
	this->isTransition = false;
	this->damageTaken = 0;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();

	AudioEngine::stopAll();
	bgmID = AudioEngine::play2d("music/" + std::to_string(level) + ".mp3", true, 0.5f);

	//add map
	auto map = MapManager::create(level);
	map->setPosition(Vec2::ZERO);
	map->setName("map");
	this->addChild(map, 0);

	//add player
	auto player = Player::create("Game/playerDown0.png");
	player->setName("player");
	player->setScale(3.2, 3.2);
	player->setPosition(map->getPlayerPosition());
	player->setOrigion(player->getPosition());
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
	klistener->onKeyPressed = [player,this](EventKeyboard::KeyCode code, Event* event){
		if (this->isMovable && player->getStatus() != Unit::Status::Jump) {
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

		if (!player->getIsMoving()) {
			switch (code)
			{
			case EventKeyboard::KeyCode::KEY_J:
				//interact
				if (!this->interact()) {
					this->close();
				}
				break;
			case EventKeyboard::KeyCode::KEY_L:
				//fire
				if (player->checkBulletReady()) {
					player->fire();
					this->fire();
				}
				break;
			case EventKeyboard::KeyCode::KEY_K:
				//jump
				if (player->getStatus() != Unit::Status::Jump && player->hasCollection("plumage")) {
					player->stop();
					player->move(Unit::Status::Jump);
				}
				break;
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				//pause game
				if (!isTransition) {
					auto scene = PauseScene::createScene();
					auto layer = dynamic_cast<PauseUILayer*>(scene->getChildByName("layer"));
					layer->recievePlayerData(player);
					Director::getInstance()->pushScene(dynamic_cast<Scene*>(this->getParent()));
					Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
				}
				break;
			}
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
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::resume), "resume", nullptr);
	
	return true;
}

void GameLayer::resume(Ref*) {
	auto player = this->getChildByName("player");
	player->unscheduleAllSelectors();
	player->schedule(schedule_selector(Player::update));

	auto map = this->getChildByName("map");
	auto list = map->getChildren();

	this->unscheduleAllSelectors();
	this->schedule(schedule_selector(GameLayer::check));
	
	for (auto node : list) {
		if (node->getName().substr(0, 5) == "enemy") {
			node->unscheduleAllSelectors();
			node->schedule(schedule_selector(Enemy::update));
			node->schedule(schedule_selector(Enemy::patrol));
		}
	}
}

void GameLayer::onContactBegin(cocos2d::Node* node1, cocos2d::Node* node2) {
	if (node1 == nullptr || node2 == nullptr) {
		return;
	}

	if (node2->getName() == "player" || node2->getName() == "bullet") {
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
	else if (node1->getName() == "player" && node2->getName().substr(0, 5) == "enemy") {
		auto enemy = dynamic_cast<Enemy*>(node2);
		damageTaken += enemy->getDamage();
	}
	else if (node1->getName() == "player" && node2->getName() == "trans") {
		auto pos = static_cast<std::pair<Vec2, Vec2>*>(node2->getUserData());
		auto player = dynamic_cast<Player*>(node1);
		player->setUserData(pos);

		this->isTransition = true;
		this->schedule(schedule_selector(GameLayer::turnOff));
	}
	else if (node1->getName() == "player" && node2->getName() == "door") {
		auto player = dynamic_cast<Player*>(node1);
		auto require = *static_cast<std::string*>(node2->getUserData());
		if (player->hasCollection(require)) {
			auto map = dynamic_cast<MapManager*>(this->getChildByName("map"));
			map->openDoor(node2->getPosition());
			node2->setPosition(this->unavailablePos);
			AudioEngine::pause(bgmID);
			AudioEngine::play2d("music/open.mp3");
			AudioEngine::resumeAll();
		}
		else{
			require = "You need:" + require + "*" + std::to_string(player->getPositionY());
			auto msg = String::createWithData((const unsigned char*)(require.c_str()), require.length());
			msg->retain();
			NotificationCenter::getInstance()->postNotification("show", msg);
			this->isMovable = false;
		}
	}
	else if (node1->getName() == "player" && node2->getName() == "boss") {
		if (currentLevel - 1 == Process::getInstance()->FileGet()) {
			Process::getInstance()->FileModify();
		}
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameVictoryScene::createScene()));
	}
	else if (node1->getName() == "bullet" && node2->getName() != "player") {

		if (node2->getName().substr(0, 5) == "enemy") {
			auto player = dynamic_cast<Player*>(this->getChildByName("player"));
			auto enemy = dynamic_cast<Enemy*>(node2);

			if (enemy->hurt(player->getDamage())) {
				auto map = this->getChildByName("map");
				map->removeChild(node2);
			}
		}

		this->removeChild(node1);
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
		player->setOrigion(pos->second);

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
		this->isTransition = false;
	}
}

void GameLayer::onContactEnd(cocos2d::Node* node1, cocos2d::Node* node2){
	if (node1 == nullptr || node2 == nullptr) {
		return;
	}

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
	else if (node1->getName() == "player" && node2->getName() == "door") {
		if (node2->getPosition() == this->unavailablePos) {
			this->removeChild(node2);
		}
	}
	else if (node1->getName() == "player" && node2->getName().substr(0, 5) == "enemy") {
		auto enemy = dynamic_cast<Enemy*>(node2);
		damageTaken -= enemy->getDamage();
	}
}

bool GameLayer::interact() {
	if (!this->isInteractable) {
		return false;
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

		AudioEngine::pause(bgmID);
		interactionID = AudioEngine::play2d("music/get.mp3", false);

		std::string temp = content;
		temp += "*";
		temp += std::to_string(player->getPositionY());

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

		return true;
	}
	
	return false;
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
		mov->setName("");
		mov->setTag(0);
	}
}

void GameLayer::check(float dt) {
	auto map = dynamic_cast<MapManager*>(this->getChildByName("map"));
	auto player = dynamic_cast<Player*>(this->getChildByName("player"));
	auto realPos = player->getPosition() - map->getOffset();

	bool hasHurted = false;
	if (map->isHole(realPos)) {
		if (player->getStatus() != Unit::Status::Jump) {
			hasHurted = true;
		}
	}
	
	if (map->isWater(realPos)) {
		if (player->hasCollection("fipperWebFoot")) {
			if (player->getIsMoving()) {
				player->stop();
				player->move(Unit::Status::Swim);
			}
			else {
				player->move(Unit::Status::Swim);
				player->stop();
			}
		}
		else {
			hasHurted = true;
		}
	}
	else if (player->getStatus() == Unit::Status::Swim) {
		player->stop();
		player->move(Unit::Status::Stand);
	}

	if (hasHurted) {
		this->isMovable = false;
		player->move();
		player->stop();
		player->hurt(1);
		player->resetPosition();
		this->isMovable = true;
	}

	if (player->hurt(damageTaken)) {
		this->isMovable = false;
		Director::getInstance()->replaceScene(SelectScene::createScene());
	}
	else if (damageTimer > 0) {
		damageTimer -= dt;
	}
	else if (damageTaken > 0) {
		if (damageTimer <= 0.0f) {
			player->setProtection(true);
			damageTimer = 1.0f;
		}
	}

	if (damageTimer <= 0.0f) {
		player->setProtection(false);
	}
}

void GameLayer::fire() {
	auto player = dynamic_cast<Player*>(this->getChildByName("player"));
	Unit::Direction dir = player->getDirection();

	auto bullet = Bullet::create();
	bullet->setName("bullet");
	auto size = player->getBoundingBox().size;

	switch (dir)
	{
	case Unit::Up:
		bullet->setVelocity(Vec2(0, 1));
		bullet->setPosition(Vec2(player->getPositionX(), player->getPositionY() + size.height / 2));
		break;
	case Unit::Down:
		bullet->setVelocity(Vec2(0, -1));
		bullet->setPosition(Vec2(player->getPositionX(), player->getPositionY() - size.height / 2));
		break;
	case Unit::Left:
		bullet->setVelocity(Vec2(-1, 0));
		bullet->setPosition(Vec2(player->getPositionX() - size.width / 2, player->getPositionY()));
		break;
	case Unit::Right:
		bullet->setVelocity(Vec2(1, 0));
		bullet->setPosition(Vec2(player->getPositionX() + size.width / 2, player->getPositionY()));
		break;
	}

	this->addChild(bullet, 2);

	AudioEngine::pause(bgmID);
	AudioEngine::play2d("music/fire.mp3");
	AudioEngine::resumeAll();
}

void GameLayer::close() {
	auto pic = this->getChildByName("temp");

	this->isMovable = true;
	NotificationCenter::getInstance()->postNotification("hide");

	if (pic) {
		this->removeChild(pic, true);

		AudioEngine::stop(interactionID);
		AudioEngine::resumeAll();
	}
}