#pragma once
#include "cocos2d.h"

class GameUILayer :
	public cocos2d::Layer
{
public:
	~GameUILayer();

	virtual bool init();
	CREATE_FUNC(GameUILayer);

	/*
	recieve notification and show message box
	@param	data of notification(Player*)
	*/
	void recieveAndShow(cocos2d::Ref*);
	/*
	recieve notification and show message box
	@param	data of notification(nullptr)
	*/
	void recieveAndHide(cocos2d::Ref*);
};