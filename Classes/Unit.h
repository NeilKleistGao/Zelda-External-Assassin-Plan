#pragma once

#include <iostream>
#include <map>
#include "cocos2d.h"
#include "BoxSprite.h"

class Unit : public BoxSprite {
public:
	enum Direction {
		Up,
		Down,
		Left,
		Right
	};

	enum Status {
		Stand,
		Swim,
		Jump
	};

	Unit() : HP(4), speed(150.0f), damage(5), animationDelta(0.2f) {
	}

	inline void setDirection(const Direction& d) {
		animationIndex = (direction == d) ? animationIndex : 0;
		direction = d;
	}

	void move(Status = Stand);
	void stop();
	virtual bool init();
	virtual bool initWithFile(const std::string&);

	virtual void update(float);

	inline Direction getDirection() const {
		return direction;
	}

	inline void setAttribute(int hp, int dmg, float spd) {
		HP = hp;
		damage = dmg;
		speed = spd;
	}

	virtual bool hurt(int dmg);

	virtual int getDamage();

	inline bool getIsMoving() {
		return isMoving;
	}

protected:
	std::map<std::string, int> frameCount;
	Direction direction;
	Status status;
	int HP, damage, animationIndex;
	float speed;

private:
	std::string frameName;
	
	bool isMoving;
	float timer;

	const float animationDelta;
};