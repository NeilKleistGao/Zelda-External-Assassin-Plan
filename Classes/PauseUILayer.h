#pragma once
#include "cocos2d.h"
#include<set>
class PauseUILayer : public cocos2d::Layer
{
private:	std::set<std::string>collection;
public:
	virtual bool init();
	CREATE_FUNC(PauseUILayer);
	void getCollection();
};

