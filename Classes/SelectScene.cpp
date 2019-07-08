#include "SelectScene.h"
#include"SelectUILayer.h"

using namespace cocos2d;
Scene* SelectScene::createScene() {

	return SelectScene::create();
}

 bool SelectScene::init() {

	 if (!Scene::init()) {

		 return false;
	}
	 auto ui = SelectUILayer::create();// create a selectULayer
	 ui->setPosition(Vec2::ZERO);
	 this->addChild(ui);

	 return true;

}