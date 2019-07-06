#include "PauseScene.h"
#include "PauseUILayer.h" 

using namespace cocos2d;

Scene* PauseScene::createScene() {

	return PauseScene::create();
}

bool PauseScene::init() {

	if (!Scene::init()) {

		return false;
	}
	auto ui =PauseUILayer ::create();
	ui->setName("layer");
	ui->setPosition(Vec2::ZERO);
	this->addChild(ui);

	return true;

}