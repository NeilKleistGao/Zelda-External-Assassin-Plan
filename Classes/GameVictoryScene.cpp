#include "GameVictoryScene.h"
#include"GameVictoryUILayer.h"
using namespace cocos2d;

Scene* GameVictoryScene::createScene()
{
	return GameVictoryScene::create();
}

bool GameVictoryScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto ui = GameVictoryUILayer::create();
	ui->setPosition(Vec2::ZERO);
	this->addChild(ui);

	return true;
}