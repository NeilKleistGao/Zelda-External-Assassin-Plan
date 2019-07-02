#include"GameScene.h"
#include"GameUILayer.h"
using namespace cocos2d;
Scene* GameScene::createScene() {

	return GameScene::create();
}

bool GameScene::init() {

	if (!Scene::init()) {

		return false;
	}
	auto ui =GameUILayer::create();
	ui->setPosition(Vec2::ZERO);
	this->addChild(ui);

	return true;

}