#pragma once
#include"Unit.h"
#include<vector>
/*定义敌人类*/
class Enemy :
	public Unit
{
public:
	void setVertices(const cocos2d::Vec2&, const cocos2d::Vec2&);//设置偏移量

	 void patrol(float);            //设置方向逻辑

	static Enemy* create();
	static  Enemy* create(const std::string&);
	virtual bool init();
	virtual bool initWithFile(const std::string&);

private:
	cocos2d::Vec2 vertex1, vertex2, origion;
};

