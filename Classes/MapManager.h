#pragma once
#include "cocos2d.h"

class MapManager :
	public cocos2d::Node
{
public:
	static MapManager* create(const int&);
	virtual bool init(const int&);

	size_t getTileSize();

	inline cocos2d::Vec2 getPlayerPosition() {
		return this->getObjectPosition("player");
	}

	inline cocos2d::Vec2 getBossPosition() {
		return this->getObjectPosition("boss");
	}

private:
	void setPhysicsBoxes();
	void addByType(const std::string&);
	cocos2d::Vec2 getObjectPosition(const std::string&);
};

