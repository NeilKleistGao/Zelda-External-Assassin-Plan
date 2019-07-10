#pragma once

#include <iostream>
#include <map>

class AnimationLoader
{
public:
	/*
	load animation
	@param	animation file path
	*/
	static void loadAnimation(const std::string&);

	static std::map<std::string, size_t> frameCount;
};

