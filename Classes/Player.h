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

	inline void addCollection(std::string name) {
		collection.insert(name);
	}

	inline bool hasCollection(std::string name) const {
		return (collection.find(name) != collection.end());
	}

	inline std::set<std::string> getAllCollection() const {
		return collection;
	}

private:
	std::set<std::string> collection;
	int bulletCount;
};

