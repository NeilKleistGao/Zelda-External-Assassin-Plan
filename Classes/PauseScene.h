#pragma once
#include "cocos2d.h"
class PauseScene :public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(PauseScene);

};

