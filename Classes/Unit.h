#pragma once

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

enum Direction {
	Up = 0,
	Down,
	Left,
	Right
};

class Unit : public cocos2d::extension::PhysicsSprite {
public:
	Unit() : HP(100), speed(10.0f), damage(5) {
	}

	void move(const Direction&);
	virtual bool init();
	virtual bool initWithFile(const std::string&);

	void play(std::string, int);
	inline void stop() {
		this->stopAllActions();
	}

protected:
	int HP, damage;
	float speed;
};