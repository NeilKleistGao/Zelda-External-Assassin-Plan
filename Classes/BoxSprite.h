#pragma once

#include <iostream>
#include "cocos2d.h"

class BoxSprite :
	public cocos2d::Sprite
{
public:
	static BoxSprite* create(const std::string& filename = "");
	virtual bool initWithFile(const std::string&);
};

