#pragma once
#include <vector>
#include <set>
#include "cocos2d.h"

typedef std::pair<cocos2d::Vec2, cocos2d::Vec2> VecPair;

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

	bool isWater(const cocos2d::Vec2&);
	bool isHole(const cocos2d::Vec2&);

	void change();

	std::vector<VecPair> getEnemyPosition();

private:
	void setPhysicsBoxes();
	void addNodeByType(const std::string&);
	void addSpriteByType(const std::string&, const std::string&);
	cocos2d::Vec2 getObjectPosition(const std::string&);

	cocos2d::Vec2 offset;
};

