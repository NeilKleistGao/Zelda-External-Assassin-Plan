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

	this->setPhysicsBoxes();

	auto list = this->getEnemyPosition();
	auto conf = Config::getInstance();

	for (auto posPair : list) {
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

void MapManager::addDoors() {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto doorLayer = map->getObjectGroup("door");
	auto doorObjects = doorLayer->getObjects();

	int size = doorObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = doorObjects.at(i).asValueMap();
		float x = obj.at("x").asFloat(), y = obj.at("y").asFloat(),
			width = obj.at("width").asFloat(), height = obj.at("height").asFloat();

		std::string require = obj.at("require").asString();

		auto node = Node::create();
		auto body = PhysicsBody::createBox(Size(width, height));
		body->getShape(0)->setContactTestBitmask(1);
		body->setDynamic(false);
		node->setPosition(x + width / 2, y + height / 2);
		node->setPhysicsBody(body);
		node->setName("door");
		node->setUserData(new std::string(require));

		this->addChild(node);
	}
}

void MapManager::addSpriteByType(const std::string& type, const std::string& filename) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto typeLayer = map->getObjectGroup(type);
	auto typeObjects = typeLayer->getObjects();

	int size = typeObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = typeObjects.at(i).asValueMap();
		float x = obj.at("x").asFloat(), y = obj.at("y").asFloat(),
			width = obj.at("width").asFloat(), height = obj.at("height").asFloat();

		std::string content = obj.at("content").asString();

		auto node = BoxSprite::create(filename);
		node->setPosition(x + width / 2, y + height / 2);
		node->setDynamic(false);
		node->setName(type);
		node->setUserData(new std::string(content));

		this->addChild(node);
	}
}

void MapManager::addPositionNode(const std::string& type) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto typeLayer = map->getObjectGroup(type);
	auto typeObjects = typeLayer->getObjects();

	int size = typeObjects.size();
	for (int i = 0; i < size; i++) {
		auto obj = typeObjects.at(i).asValueMap();
		float x = obj.at("x").asFloat(), y = obj.at("y").asFloat(),
			width = obj.at("width").asFloat(), height = obj.at("height").asFloat();

		int dx = obj.at("dx").asInt(), dy = obj.at("dy").asInt();
		int newx = obj.at("newx").asInt(), newy = obj.at("newy").asInt();

		auto node = Node::create();
		auto body = PhysicsBody::createBox(Size(width, height));
		body->getShape(0)->setContactTestBitmask(1);
		body->setDynamic(false);
		node->setPosition(x + width / 2, y + height / 2);
		node->setPhysicsBody(body);
		node->setName(type);
		node->setUserData(new std::pair<Vec2, Vec2>(Vec2(dx, dy), Vec2(newx, newy)));

		this->addChild(node);
	}
}

std::vector<Vec3Pair> MapManager::getEnemyPosition() {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));

	auto enmLayer = map->getObjectGroup("enm");
	auto enmObjects = enmLayer->getObjects();

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

	return res;
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
	sum += getGIDAt(v, "wall");
	sum += getGIDAt(v, "door");
	sum += getGIDAt(v, "hole");
	sum += getGIDAt(v, "water");
	sum += getGIDAt(v, "obs");
	sum += getGIDAt(v, "mov");
	sum += getGIDAt(v, "box");

	return (sum == 0);
}

void MapManager::resetMovableObject(const cocos2d::Vec2& v1, const cocos2d::Vec2& v2) {
	int temp = this->getGIDAt(v1, "mov");
	this->setGIDAt(v1, "mov", 0);
	this->setGIDAt(v2, "mov", temp);
}