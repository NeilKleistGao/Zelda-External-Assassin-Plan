#include <iostream>
#include <fstream>
#include "MapManager.h"
#include "Enemy.h"
#include "BoxSprite.h"
#include "Config.h"

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

	/*
	set all static boxes
	*/
	this->setPhysicsBoxes();
	this->createEnemy();

	auto boss = BoxSprite::create("Game/boss" + std::to_string(index) + ".png");
	boss->setPosition(this->getBossPosition());
	boss->setName("boss");
	boss->setDynamic(false);
	this->addChild(boss, 1);

	return true;
}

size_t MapManager::getTileSize() {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	return map->getTileSize().width;
}

void MapManager::setPhysicsBoxes() {
	this->addNodeByType("obs");
	this->addNodeByType("mov");
	this->addDoors();
	this->addSpriteByType("box", "Game/boxClose.png");
	this->addPositionNode("trans");
}

cocos2d::Vec2 MapManager::getObjectPosition(const std::string& objName) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto posObject = map->getObjectGroup(objName)->getObjects().at(0).asValueMap();
	return Vec2(posObject.at("x").asFloat(), posObject.at("y").asFloat());
}

void MapManager::addNodeByType(const std::string& type) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto typeLayer = map->getObjectGroup(type);
	auto typeObjects = typeLayer->getObjects();

	int size = typeObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = typeObjects.at(i).asValueMap();
		auto node = this->createChild(obj, "");
		node->setName(type);
	}
}

void MapManager::addDoors() {
	auto doorObjects = this->getObjectVector("door");

	int size = doorObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = doorObjects.at(i).asValueMap();
		std::string require = obj.at("require").asString();

		auto node = this->createChild(obj);
		node->setName("door");
		node->setUserData(new std::string(require));
	}
}

void MapManager::addSpriteByType(const std::string& type, const std::string& filename) {
	auto typeObjects = this->getObjectVector(type);

	int size = typeObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = typeObjects.at(i).asValueMap();

		std::string content = obj.at("content").asString();

		auto node = this->createChild(obj, filename);
		node->setName(type);
		node->setUserData(new std::string(content));
	}
}

void MapManager::addPositionNode(const std::string& type) {
	auto typeObjects = this->getObjectVector(type);

	int size = typeObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = typeObjects.at(i).asValueMap();

		int dx = obj.at("dx").asInt(), dy = obj.at("dy").asInt();
		int newx = obj.at("newx").asInt(), newy = obj.at("newy").asInt();

		auto node = this->createChild(obj);
		node->setName(type);
		node->setUserData(new std::pair<Vec2, Vec2>(Vec2(dx, dy), Vec2(newx, newy)));

		this->addChild(node);
	}
}

void MapManager::createEnemy() {
	auto conf = Config::getInstance();
	auto enmObjects = this->getObjectVector("enm");

	int size = enmObjects.size();
	std::vector<Vec3Pair> res;
	for (int i = 0; i < size / 2; i++) {
		res.push_back(Vec3Pair());
	}

	for (int i = 0; i < size; i++) {
		auto obj = enmObjects.at(i).asValueMap();
		float x = obj.at("x").asFloat(), y = obj.at("y").asFloat();
		int index = obj.at("index").asInt(), type = obj.at("type").asInt();

		if (res[index].first == Vec3::ZERO) {
			res[index].first = Vec3(x, y, type);
		}
		else {
			res[index].second = Vec3(x, y, type);
		}
	}

	for (auto posPair : res) {
		std::string name = "enemy";
		name += std::to_string((int)posPair.first.z);

		auto enemy = Enemy::create("enemy/" + name + "Down0.png");
		enemy->setName(name);
		enemy->setPosition(Vec2(posPair.first.x, posPair.first.y));
		enemy->setVertices(Vec2(posPair.first.x, posPair.first.y), Vec2(posPair.second.x, posPair.second.y));

		auto data = conf->getEnemy(name);
		enemy->setAttribute(data.HP, data.damage, data.speed);

		this->addChild(enemy);
	}
}

int MapManager::getGIDAt(const Vec2& pos, const std::string layerName) {
	Vec2 realPos = transform(pos);
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto layer = map->getLayer(layerName);
	return layer->getTileGIDAt(realPos);
}

void MapManager::setGIDAt(const Vec2& pos, const std::string& layerName, const int& gid) {
	Vec2 realPos = transform(pos);
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto layer = map->getLayer(layerName);

	layer->setTileGID(gid, realPos);
}

Vec2 MapManager::transform(Vec2 v) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	size_t size = getTileSize(), height = map->getMapSize().height;

	return Vec2((int)(v.x / size), (int)(height - v.y / size));
}

bool MapManager::isNull(const Vec2& v) {
	int sum = 0;
	for (auto str : obsObjects) {
		sum += getGIDAt(v, str);
	}

	return (sum == 0);
}

void MapManager::resetMovableObject(const cocos2d::Vec2& v1, const cocos2d::Vec2& v2) {
	int temp = this->getGIDAt(v1, "mov");
	this->setGIDAt(v1, "mov", 0);
	this->setGIDAt(v2, "mov", temp);
}

Node* MapManager::createChild(const cocos2d::ValueMap& obj, const std::string& filename) {
	float x = obj.at("x").asFloat(), y = obj.at("y").asFloat(),
		width = obj.at("width").asFloat(), height = obj.at("height").asFloat();
	Node* node = nullptr;

	if (filename == "") {
		node = Node::create();
		auto body = PhysicsBody::createBox(Size(width, height));
		body->getShape(0)->setContactTestBitmask(1);
		body->setDynamic(false);
		node->setPosition(x + width / 2, y + height / 2);
		node->setPhysicsBody(body);
	}
	else {
		node = BoxSprite::create(filename);
		node->setPosition(x + width / 2, y + height / 2);
		dynamic_cast<BoxSprite*>(node)->setDynamic(false);
	}

	this->addChild(node);
	return node;
}

ValueVector MapManager::getObjectVector(const std::string& name) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto typeLayer = map->getObjectGroup(name);
	auto typeObjects = typeLayer->getObjects();

	return typeObjects;
}