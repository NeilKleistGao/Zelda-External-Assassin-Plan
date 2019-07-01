#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldUILayer.h"

using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto ui = HelloWorldUILayer::create();
	ui->setPosition(Vec2::ZERO);
	this->addChild(ui);
    
    return true;
}