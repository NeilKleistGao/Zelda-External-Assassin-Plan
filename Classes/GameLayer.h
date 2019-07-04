#pragma once

#include "cocos2d.h"
#include"GameScene.h"
class GameLayer :
	public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);

	inline void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
		theWorld = world;
	}

	void onContactBegin(cocos2d::Node*, cocos2d::Node*);
	void onContactEnd(cocos2d::Node*, cocos2d::Node*);

	void interact();
	void push();

private:
	cocos2d::PhysicsWorld* theWorld;
	bool isInteractable, isMovable, isPushable;

	const int interactingFlag = 3154;
};

