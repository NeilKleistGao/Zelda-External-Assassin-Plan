#include "GameProcess.h"
#include "cocos2d.h"

using namespace cocos2d;

Process* Process::instance = nullptr;

Process* Process::getInstance() {
	if (!instance) {
		instance = new(std::nothrow) Process();
	}

	return instance;
}

void Process::FileModify() {
	UserDefault* FileProcess = UserDefault::getInstance();
	FileProcess->setIntegerForKey("CheckPoint", FileProcess->getIntegerForKey("CheckPoint") + 1);
}

int Process::FileGet() {
	if (UserDefault::getInstance()->isXMLFileExist()) {
		return UserDefault::getInstance()->getIntegerForKey("CheckPoint");
	}
	else {
		UserDefault* FileProcess = UserDefault::getInstance();
		FileProcess->setIntegerForKey("CheckPoint", 0);
		return 0;
	}
}