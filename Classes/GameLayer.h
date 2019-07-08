#pragma once

#include <iostream>
#include "cocos2d.h"
#include "GameScene.h"

class GameLayer :
	public cocos2d::Layer
{
public:
	~GameLayer();

	virtual bool init(int);
	static GameLayer* create(int);

	/*
	function for physics contact, called when contact begins
	@param	two objects having contact
	*/
	void onContactBegin(cocos2d::Node*, cocos2d::Node*);
	/*
	function for physics contact, called when contact ends
	@param	two objects having contact
	*/
	void onContactEnd(cocos2d::Node*, cocos2d::Node*);

	/*
	interact to other objects
	*/
	bool interact();
	/*
	push movable objects
	*/
	void push();
	/*
	shoot function
	*/
	void fire();
	/*
	close the message box if it is open
	*/
	void close();

	/*
	check if player is alive or player is in a dangrous place
	*/
	void check(float);
	/*
	turn off the light so that we can reset the scene
	*/
	void turnOff(float);
	/*
	turn on the light after finishing reseting
	*/
	void turnOn(float);

	/*
	resume from pause
	*/
	void resume(cocos2d::Ref*);

private:
	bool isInteractable, isMovable, isTransition;//whether player/scene can interact/move/make transition

	int currentLevel, bgmID, interactionID;//the level of this checkpoint and music ID
	int damageTaken;//the damage player will take from enemies

	float damageTimer;//calculate the time for damage

	const int interactingFlag = 3154, movableFlag = 2517;//tag of object which player is interacting to/pushing
};

