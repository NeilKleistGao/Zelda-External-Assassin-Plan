#pragma once

#include<set>
#include "cocos2d.h"
#include "Player.h"

class PauseUILayer : public cocos2d::Layer
{
public:
	virtual bool init();//Initialize the layer
	CREATE_FUNC(PauseUILayer);

	void recievePlayerData(Player*);//Display the objects currently owned by the player
};

