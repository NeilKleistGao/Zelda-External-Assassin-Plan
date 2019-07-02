#pragma once

#include <iostream>
#include <map>
#include "Unit.h"

class Player :
	public Unit
{
public:
	static Player* create();
	static Player* create(const std::string&);
	virtual bool init();
	virtual bool initWithFile(const std::string&);

private:
	std::map<std::string, int> collection;
	int bulletCount;
};

