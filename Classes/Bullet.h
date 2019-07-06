#pragma once

#include <iostream>
#include "BoxSprite.h"

class Bullet : public BoxSprite{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);

	void setVelocity(const cocos2d::Vec2&);

private:
	const float speed = 250.0f;
};

