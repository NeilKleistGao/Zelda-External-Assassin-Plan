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

	inline bool isWater(const cocos2d::Vec2& v) {
		return (getGIDAt(v, "water") != 0);
	}

	inline bool isHole(const cocos2d::Vec2& v) {
		return (getGIDAt(v, "hole") != 0);
	}

	inline void setOffset(const cocos2d::Vec2& v) {
		offset += v;
	}

	bool isNull(const cocos2d::Vec2&);

	void resetMovableObject(const cocos2d::Vec2&, const cocos2d::Vec2&);

	std::vector<VecPair> getEnemyPosition();

private:
	void setPhysicsBoxes();
	void addNodeByType(const std::string&);
	void addSpriteByType(const std::string&, const std::string&);
	void addPositionNode(const std::string&);
	cocos2d::Vec2 getObjectPosition(const std::string&);

	int getGIDAt(const cocos2d::Vec2&, const std::string);
	void setGIDAt(const cocos2d::Vec2&, const std::string&, const int);

	cocos2d::Vec2 transform(cocos2d::Vec2);

	cocos2d::Vec2 offset;
};

