#pragma once
#include <vector>
#include <set>
#include "cocos2d.h"

typedef std::pair<cocos2d::Vec2, cocos2d::Vec2> Vec2Pair;
typedef std::pair<cocos2d::Vec3, cocos2d::Vec3> Vec3Pair;

class MapManager :
	public cocos2d::Node
{
public:
	static MapManager* create(const int&);
	virtual bool init(const int&);

	/*
	return the size of single tile
	*/
	size_t getTileSize();

	/*
	get initial position of player
	*/
	inline cocos2d::Vec2 getPlayerPosition() {
		return this->getObjectPosition("player");
	}

	/*
	get initial position of boss
	*/
	inline cocos2d::Vec2 getBossPosition() {
		return this->getObjectPosition("boss");
	}

	/*
	check if this tile is water
	@param	position
	*/
	inline bool isWater(const cocos2d::Vec2& v) {
		return (getGIDAt(v, "water") != 0);
	}

	/*
	check if this tile is a hole
	@param	position
	*/
	inline bool isHole(const cocos2d::Vec2& v) {
		return (getGIDAt(v, "hole") != 0);
	}

	/*
	set the offset of map
	@param offset
	*/
	inline void setOffset(const cocos2d::Vec2& v) {
		offset += v;
	}

	/*
	get the offset
	*/
	inline cocos2d::Vec2 getOffset() {
		return offset;
	}

	/*
	if an object can be placed in this tile
	@param	position
	*/
	bool isNull(const cocos2d::Vec2&);

	/*
	remove door image from map
	@param	position
	*/
	inline void openDoor(const cocos2d::Vec2& pos) {
		this->setGIDAt(pos, "door", 0);
	}

	/*
	exchange image between two tile
	@param	tile1's and tile2's position
	*/
	void resetMovableObject(const cocos2d::Vec2&, const cocos2d::Vec2&);

private:
	/*
	add all physics objects
	*/
	void setPhysicsBoxes();
	/*
	add physics node(without image) by type
	@param	name of type
	*/
	void addNodeByType(const std::string&);
	/*
	add boxSprite by type
	@param	name of type
	*/
	void addSpriteByType(const std::string&, const std::string&);
	/*
	add physics position(without image) by type
	@param	name of type
	*/
	void addPositionNode(const std::string&);
	/*
	add door objects by type
	@param	name of type
	*/
	void addDoors();
	/*
	get position of an object
	@param name of object layer
	*/
	cocos2d::Vec2 getObjectPosition(const std::string&);

	/*
	create a node with valuemap
	*/
	cocos2d::Node* createChild(const cocos2d::ValueMap&, const std::string& filename = "");

	/*
	get objects vector by name
	*/
	cocos2d::ValueVector getObjectVector(const std::string&);

	/*
	get tile's GID
	@param	position
			name of layer
	*/
	int getGIDAt(const cocos2d::Vec2&, const std::string);
	/*
	set tile's GID
	@param	position
			name of layer
			GID
	*/
	void setGIDAt(const cocos2d::Vec2&, const std::string&, const int&);

	/*
	get all enemies' 
	*/
	void createEnemy();

	/*
	turn position in global world into position in tiledmap
	*/
	cocos2d::Vec2 transform(cocos2d::Vec2);

	cocos2d::Vec2 offset;

	const std::string obsObjects[7] = {"wall", "door", "hole", "water", "obs", "mov", "box"};
};

