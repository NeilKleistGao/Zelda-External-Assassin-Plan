#pragma once
#include "cocos2d.h"

class HelloWorldUILayer :
	public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(HelloWorldUILayer);

	void update(float);
};

