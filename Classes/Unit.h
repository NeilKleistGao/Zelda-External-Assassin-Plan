#pragma once

#include <iostream>
#include <map>
#include "cocos2d.h"
#include "BoxSprite.h"

class Unit : public BoxSprite {
public:
	/*
	direction of unit's face
	*/
	enum Direction {
		Up,
		Down,
		Left,
		Right
	};

	/*
	the movement status of unit
	*/
	enum Status {
		Stand,
		Swim,
		Jump
	};

	/*
	player's default data
	if this unit is an enemy, reset it by using setAttribute
	*/
	Unit() : HP(4), speed(150.0f), damage(5), animationDelta(0.2f) {
	}

	/*
	set direction of unit face
	*/
	inline void setDirection(const Direction& d) {
		animationIndex = (direction == d) ? animationIndex : 0;
		direction = d;
	}

	/*
	move and play animation
	*/
	void move(Status = Stand);
	/*
	stop both movement and animation
	*/
	void stop();
	virtual bool init();
	virtual bool initWithFile(const std::string&);

	/*
	update animation
	*/
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