#pragma once
#include "cocos2d.h"

class GameUILayer :
	public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameUILayer);

	void update(float);
};