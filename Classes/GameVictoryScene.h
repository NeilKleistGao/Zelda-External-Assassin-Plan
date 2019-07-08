#pragma once
#include "cocos2d.h"
/*Game Victory object*/
class GameVictoryScene :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameVictoryScene);
};



