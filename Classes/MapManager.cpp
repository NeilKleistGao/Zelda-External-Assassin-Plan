#include "MapManager.h"

using namespace cocos2d;

MapManager* MapManager::create(const int& index) {
	auto manager = new(std::nothrow)MapManager();
	if (manager && manager->init(index)) {
		manager->autorelease();
	}
	else if (manager) {
		delete manager;
		manager = nullptr;
	}

	return manager;
}

bool MapManager::init(const int& index) {
	if (!Node::init()) {
		return false;
	}

	std::string filename = "Game/";
	filename += (char)(index + '0');
	filename += ".tmx";
	auto map = TMXTiledMap::create(filename);
	map->setPosition(Vec2::ZERO);
	map->setName("map");
	this->addChild(map);

	this->setPhysicsBoxes();

	return true;
}

size_t MapManager::getTileSize() {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	return map->getTileSize().width;
}

void MapManager::setPhysicsBoxes() {
	this->addNodeByType("obs");
	this->addNodeByType("mov");
	this->addNodeByType("door");
	this->addSpriteByType("box", "Game/boxClose.png");
}

cocos2d::Vec2 MapManager::getObjectPosition(const std::string& objName) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto posObject = map->getObjectGroup(objName)->getObjects().at(0).asValueMap();
	return Vec2(posObject.at("x").asFloat(), posObject.at("y").asFloat());
}

void MapManager::addNodeByType(const std::string& type) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto typeLayer = map->getObjectGroup(type);
	auto typeObjects = typeLayer->getObjects();

	int size = typeObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = typeObjects.at(i).asValueMap();
		float x = obj.at("x").asFloat(), y = obj.at("y").asFloat(),
			width = obj.at("width").asFloat(), height = obj.at("height").asFloat();

		auto node = Node::create();
		auto body = PhysicsBody::createBox(Size(width, height));
		body->getShape(0)->setContactTestBitmask(1);
		body->setDynamic(false);
		node->setPosition(x + width / 2, y + height / 2);
		node->setPhysicsBody(body);
		node->setName(type);

		this->addChild(node);
	}
}

void MapManager::addSpriteByType(const std::string& type, const std::string& filename) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto typeLayer = map->getObjectGroup(type);
	auto typeObjects = typeLayer->getObjects();

	int size = typeObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = typeObjects.at(i).asValueMap();
		float x = obj.at("x").asFloat(), y = obj.at("y").asFloat(),
			width = obj.at("width").asFloat(), height = obj.at("height").asFloat();

		std::string content = obj.at("content").asString();

		auto node = Sprite::create(filename);
		auto body = PhysicsBody::createBox(Size(width, height));
		body->getShape(0)->setContactTestBitmask(1);
		body->setDynamic(false);
		node->setPosition(x + width / 2, y + height / 2);
		node->setPhysicsBody(body);
		node->setName(type);
		node->setUserData(new std::string(content));

		this->addChild(node);
	}
}

std::vector<VecPair> MapManager::getEnemyPosition() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origion = Director::getInstance()->getVisibleOrigin();
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto enmLayer = map->getObjectGroup("enm");
	auto enmObjects = enmLayer->getObjects();

	int size = enmObjects.size();
	std::vector<VecPair> res;
	res.reserve(size / 2);

	for (int i = 0; i < size / 2; i++) {
		res[i].first = res[i].second = Vec2::ZERO;
	}

	for (int i = 0; i < size; i++) {
		auto obj = enmObjects.at(i).asValueMap();
		float x = obj.at("x").asFloat(), y = obj.at("y").asFloat();
		int index = obj.at("index").asInt();

		if (res[index].first == Vec2::ZERO) {
			res[index].first = Vec2(x, y);
		}
		else {
			res[index].second = Vec2(x, y);
		}
	}

	return res;
}

bool MapManager::isWater(const cocos2d::Vec2&) {
	//TODO:
	return false;
}

bool MapManager::isHole(const cocos2d::Vec2&) {
	//TODO:
	return false;
}

void MapManager::change() {
	//TODO:
}