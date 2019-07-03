#pragma once
#include "cocos2d.h"

class MapManager :
	public cocos2d::Node
{
public:
	static MapManager* create(const int&);
	virtual bool init(const int&);

	size_t getTileSize();

	cocos2d::Vec2 getPlayerPosition();

private:
	void setPhysicsBoxes();
	void addByType(const std::string&);
};

