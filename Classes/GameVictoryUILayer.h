#pragma once
#include"cocos2d.h"
/*create Victory UI*/
class GameVictoryUILayer :
	public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameVictoryUILayer);
	void Refresh(float dt);//ˢ�½��棨���֣�
	void DataRetore();//���������Ϣ
};

