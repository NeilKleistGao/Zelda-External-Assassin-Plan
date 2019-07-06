#pragma once

#include "cocos2d.h"
#include "GameScene.h"

class GameLayer :
	public cocos2d::Layer
{
public:
	virtual bool init(int);
	static GameLayer* create(int);

	inline void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
		theWorld = world;
	}

	void onContactBegin(cocos2d::Node*, cocos2d::Node*);
	void onContactEnd(cocos2d::Node*, cocos2d::Node*);

	void interact();
	void push();
	void fire();

	void check(float);
	void turnOff(float);
	void turnOn(float);

	void resume(cocos2d::Ref*);

private:
	cocos2d::PhysicsWorld* theWorld;
	bool isInteractable, isMovable, isTransition;

	int currentLevel;

	const int interactingFlag = 3154, movableFlag = 2517;
	const cocos2d::Vec2 unavailablePos = cocos2d::Vec2(-99999999, -99999999);
};

