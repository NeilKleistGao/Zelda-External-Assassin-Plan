#pragma once
#include "cocos2d.h"
class InteractionMessageBox:
	public cocos2d::Node
{
public:
	virtual bool init();
	CREATE_FUNC(InteractionMessageBox);

	void show(float y, const std::string& name);
	void hide();
};

