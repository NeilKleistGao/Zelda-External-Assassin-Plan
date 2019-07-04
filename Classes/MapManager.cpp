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
	this->addByType("obs");
	this->addByType("mov");
}

cocos2d::Vec2 MapManager::getObjectPosition(const std::string& objName) {
	auto map = dynamic_cast<TMXTiledMap*>(this->getChildByName("map"));
	auto posObject = map->getObjectGroup(objName)->getObjects().at(0).asValueMap();
	return Vec2(posObject.at("x").asFloat(), posObject.at("y").asFloat());
}

void MapManager::addByType(const std::string& type) {
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

		if (x >= 0 && x <= visibleSize.width && y >= 0 && y <= visibleSize.height) {
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
}