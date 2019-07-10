#include <fstream>

#include "cocos2d.h"
#include "AnimationLoader.h"

using namespace cocos2d;

std::map<std::string, size_t> AnimationLoader::frameCount = std::map<std::string, size_t>();

void AnimationLoader::loadAnimation(const std::string& filename) {
	std::istringstream stream(FileUtils::getInstance()->getStringFromFile(filename));

	if (stream.bad()) {
		return;
	}

	float width, height;
	stream >> width >> height;

	int count;
	stream >> count;//frame name's count

	for (int i = 0; i < count; i++) {
		std::string frameName;
		stream >> frameName;

		frameCount[frameName] = 0;
	}

	stream >> count;//frames' count
	auto cache = SpriteFrameCache::getInstance();

	for (int i = 0; i < count; i++) {
		std::string name, path;
		stream >> name >> path;

		cache->addSpriteFrame(SpriteFrame::create(path, Rect(0, 0, width, height)), name);

		frameCount[name.substr(0, name.length() - 1)]++;
	}
}