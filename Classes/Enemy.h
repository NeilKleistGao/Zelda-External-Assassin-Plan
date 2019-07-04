#pragma once
#include"Unit.h"
#include<vector>
class Enemy :
	public Unit
{
public:
	void setVertices(const cocos2d::Vec2&, const cocos2d::Vec2&);

	 void patrol(float);

	static Enemy* create();
	static  Enemy* create(const std::string&);
	virtual bool init();
	virtual bool initWithFile(const std::string&);

private:
	cocos2d::Vec2 vertex1, vertex2, origion;
};

