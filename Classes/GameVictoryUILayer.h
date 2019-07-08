#pragma once
#include"cocos2d.h"
/*create Victory UI*/
class GameVictoryUILayer :
	public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameVictoryUILayer);
	void Refresh(float dt);//刷新界面（文字）
	void DataRetore();//保存进度信息
};

