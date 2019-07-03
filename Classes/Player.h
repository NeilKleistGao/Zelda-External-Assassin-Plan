#pragma once

#include <iostream>
#include <set>
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
	std::set<std::string> collection;
	int bulletCount;
};

