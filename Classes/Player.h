#pragma once

#include <iostream>
#include <set>
#include "Unit.h"

class Player :
	public Unit
{
public:
	static Player* create();
	static Player* create(const std::string&);
	virtual bool init();
	virtual bool initWithFile(const std::string&);

	/*
	add a collection to player
	@param	collection name
	*/
	inline void addCollection(std::string name) {
		if (name == "bullet") {
			this->addBullet();
		}
		else if (name == "healthPotion") {
			HP = 4;
		}
		else {
			collection.insert(name);
		}
	}

	/*
	check if player has this collection
	@param	collection name
	*/
	inline bool hasCollection(std::string name) const {
		return (collection.find(name) != collection.end());
	}

	/*
	get all collections
	*/
	inline const std::set<std::string>& getAllCollection() const {
		return collection;
	}

	/*
	return status of player
	*/
	inline Unit::Status getStatus() {
		return this->status;
	}

	/*
	set origion position
	*/
	inline void setOrigion(const cocos2d::Vec2& pos) {
		origion = pos;
	}

	/*
	place player at origion position
	*/
	inline void resetPosition() {
		this->setPosition(origion);
	}

	/*
	check if player can shoot
	*/
	inline bool checkBulletReady() {
		return (getBullet() > 0);
	}

	/*
	shoot and use one bullet
	*/
	inline void fire() {
		this->bulletCount--;
	}

	/*
	return the damage player can make
	*/
	virtual int getDamage();

	/*
	set if player will take damage
	@param	true for no damage
	*/
	inline void setProtection(bool st) {
		this->isProtected = st;
	}

	/*
	hurt player and test if player is dead
	*/
	virtual bool hurt(int);

	/*
	get bullet count
	*/
	inline int  getBullet() const {
		return bulletCount;
	}

	/*
	get HP
	*/
	inline int getHP() const {
		return this->HP;
	}

	/*
	blink when taking damage
	*/
	void blink(float);

private:
	std::set<std::string> collection;
	int bulletCount;
	cocos2d::Vec2 origion;
	bool isProtected;

	inline void addBullet() {
		bulletCount++;
	}
};

