#pragma once
#include "cocos2d.h"
class SelectScene :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();//Create a scene to select a checkpoint

	virtual bool init();//Initialize the scene

	CREATE_FUNC(SelectScene);
};

