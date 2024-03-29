#include"GameScene.h"
#include"GameUILayer.h"
#include "GameLayer.h"

using namespace cocos2d;

Scene* GameScene::createScene(int level) {
	auto scene = GameScene::createWithPhysics();
	auto theWorld = scene->getPhysicsWorld();

	theWorld->setGravity(Vec2::ZERO);

	auto game = GameLayer::create(level);
	game->setPosition(Vec2::ZERO);
	scene->addChild(game, 1);

	auto ui = GameUILayer::create();
	ui->setPosition(Vec2::ZERO);
	scene->addChild(ui, 2);

	return scene;
}