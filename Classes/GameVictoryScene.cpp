#include "GameVictoryScene.h"
#include"GameVictoryUILayer.h"
using namespace cocos2d;

Scene* GameVictoryScene::createScene()//provide a path to create();
{
	return GameVictoryScene::create();
}

bool GameVictoryScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//create GameVivtoryUILayer  
	auto ui = GameVictoryUILayer::create();
	ui->setPosition(Vec2::ZERO);
	this->addChild(ui);

	return true;
}