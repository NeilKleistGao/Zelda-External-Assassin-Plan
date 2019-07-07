#pragma once

#include <iostream>
#include <fstream>

void logMessage(std::string content) {
	std::ofstream stream("game.log", std::ios::app);
	stream << content << std::endl;
	stream.close();
}