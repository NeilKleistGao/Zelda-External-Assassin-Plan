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

	inline bool hasCollection(std::string name) const {
		return (collection.find(name) != collection.end());
	}

	inline std::set<std::string> getAllCollection() const {
		return collection;
	}

	inline Unit::Status getStatus() {
		return this->status;
	}

	inline void setOrigion(const cocos2d::Vec2& pos) {
		origion = pos;
	}

	inline void resetPosition() {
		this->setPosition(origion);
	}

	inline bool checkBulletReady() {
		return (bulletCount > 0);
	}

	inline void fire() {
		this->bulletCount--;
	}

	virtual int getDamage();

	inline void setProtection() {
		this->isProtected = true;
		this->scheduleOnce(schedule_selector(Player::cancelProtection), 1.0f);
	}

	void cancelProtection(float);

	virtual bool hurt(int);

	inline int  getBullet() const {
		return bulletCount;
	}

	inline int getHP() const {
		return this->HP;
	}

private:
	std::set<std::string> collection;
	int bulletCount;
	cocos2d::Vec2 origion;
	bool isProtected;

	inline void addBullet() {
		bulletCount++;
	}
};

