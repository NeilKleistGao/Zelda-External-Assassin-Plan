#pragma once
#include"cocos2d.h"
class GameVictoryUILayer :
	public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameVictoryUILayer);
	void Refresh(float dt);
	void DataRetore();
};

