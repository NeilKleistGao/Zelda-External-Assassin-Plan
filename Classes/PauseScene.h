#pragma once

#include "cocos2d.h"
#include "Player.h"

class PauseScene :public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();//create a pause scene;

	virtual bool init();//initialize the scene

	CREATE_FUNC(PauseScene);
};

