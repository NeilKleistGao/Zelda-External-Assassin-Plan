#pragma once

#include <iostream>
#include "cocos2d.h"

class BoxSprite :
	public cocos2d::Sprite
{
public:
	/*
	create a sprite with physics body and box
	@param	filename: the path of texture
	*/
	static BoxSprite* create(const std::string& filename = "");
	/*
	init this object
	@param	filename: the path of texture
	*/
	virtual bool initWithFile(const std::string&);

	/*
	set whether this physics body is dynamic or static
	@param	isDynamic: true for dynamic, and false for static
	*/
	inline void setDynamic(bool isDynamic) {
		auto body = this->getPhysicsBody();
		body->setDynamic(isDynamic);
	}
};

