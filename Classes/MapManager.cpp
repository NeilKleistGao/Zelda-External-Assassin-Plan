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

	int gid1 = this->getGIDAt(Vec2(1, 1), "wall"),
		gid2 = this->getGIDAt(Vec2(65, 65), "wall");

	return true;
}

size_t MapManager::getTileSize() {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	return map->getTileSize().width;
}

void MapManager::setPhysicsBoxes() {
	this->addNodeByType("obs");
	this->addNodeByType("mov");
	this->addSpriteByType("box", "Game/boxClose.png");
	this->addPositionNode("trans");
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

void MapManager::addPositionNode(const std::string& type) {
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

		int dx = obj.at("dx").asInt(), dy = obj.at("dy").asInt();

		auto node = Node::create();
		auto body = PhysicsBody::createBox(Size(width, height));
		body->getShape(0)->setContactTestBitmask(1);
		body->setDynamic(false);
		node->setPosition(x + width / 2, y + height / 2);
		node->setPhysicsBody(body);
		node->setName(type);
		node->setUserData(new Vec2(dx, dy));

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

int MapManager::getGIDAt(const Vec2& pos, const std::string layerName) {
	Vec2 realPos = transform(pos);
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto layer = map->getLayer(layerName);
	return layer->getTileGIDAt(realPos);
}

void MapManager::setGIDAt(const Vec2& pos, const std::string& layerName, const int gid) {
	Vec2 realPos = transform(pos);
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto layer = map->getLayer(layerName);

	layer->setTileGID(gid, realPos);
}

Vec2 MapManager::transform(Vec2 v) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	size_t size = getTileSize(), height = map->getMapSize().height;

	v.x -= offset.x;
	v.y -= offset.y;

	return Vec2((int)(v.x / size), (int)(height - v.y / size));
}

bool MapManager::isNull(const Vec2& v) {
	int sum = 0;
	sum += getGIDAt(v, "wall");
	sum += getGIDAt(v, "door");
	sum += getGIDAt(v, "hole");
	sum += getGIDAt(v, "water");
	sum += getGIDAt(v, "obs");

	return (sum == 0);
}

void MapManager::resetMovableObject(const cocos2d::Vec2& v1, const cocos2d::Vec2& v2) {
	int temp = this->getGIDAt(v1, "mov");
	this->setGIDAt(v1, "mov", 0);
	this->setGIDAt(v2, "mov", temp);
}