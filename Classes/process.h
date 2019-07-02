#pragma once
#include "cocos2d.h"

class Process :
	private cocos2d::UserDefault
{
public:
	static Process* getInstance();
	void FileModif();
	int FileGet();
private:
	static Process* _instance;
	Process()=default;
	~Process()=default;
};

