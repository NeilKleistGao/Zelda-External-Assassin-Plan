#pragma once
#include "cocos2d.h"
class InteractionMessageBox:
	public cocos2d::Node
{
public:
	virtual bool init();
	CREATE_FUNC(InteractionMessageBox);

	void show(float y, const std::string& name);//Set a message box where will be a prompt when you reach the item
	void hide();//hide the messagebox.
};

