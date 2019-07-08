#include <fstream>

#include "AnimationLoader.h"

using namespace cocos2d;

void AnimationLoader::loadAnimation(const std::string& filename) {
	std::ifstream stream(filename);

	try {
		if (stream.bad() || !stream.is_open()) {
			return;
		}

		float width, height;
		stream >> width >> height;

		int count;
		stream >> count;

		auto cache = SpriteFrameCache::getInstance();

		for (int i = 0; i < count; i++) {
			std::string name, path;
			stream >> name >> path;

			cache->addSpriteFrame(SpriteFrame::create(path, Rect(0, 0, width, height)), name);
		}

		stream.close();
	}
	catch (...) {
		if (stream.is_open()) {
			stream.close();
		}
	}
}