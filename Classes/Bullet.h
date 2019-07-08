#pragma once

#include <iostream>
#include "BoxSprite.h"

class Bullet : public BoxSprite{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);

	/*
	set the velocity of this bullet
	@param	v: the 2D velocity
	*/
	void setVelocity(const cocos2d::Vec2&);

private:
	//default speed of bullet
	const float speed = 250.0f;
};

