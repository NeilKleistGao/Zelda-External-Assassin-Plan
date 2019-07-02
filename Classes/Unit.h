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

class Unit : cocos2d::extension::PhysicsSprite {
public:
	void move(const Direction&);
	virtual bool init();
	virtual bool initWithFile(const std::string&);

	void play(std::string, int);
	inline void stop() {
		this->stopAllActions();
	}

private:
	int HP, damage;
	float speed;
};

