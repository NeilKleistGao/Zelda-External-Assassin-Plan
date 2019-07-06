#pragma once

#include<set>
#include "cocos2d.h"
#include "Player.h"

class PauseUILayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PauseUILayer);

	void recievePlayerData(Player*);
};

