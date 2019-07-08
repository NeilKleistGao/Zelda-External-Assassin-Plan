#include "GameProcess.h"
#include "cocos2d.h"

using namespace cocos2d;

Process* Process::instance = nullptr;//Initially empty object

Process* Process::getInstance() {//create single case
	if (!instance) {
		instance = new(std::nothrow) Process();
	}

	return instance;
}

void Process::FileModify() {//use cocos::Userdefault restore the data
	UserDefault* FileProcess = UserDefault::getInstance();
	FileProcess->setIntegerForKey("CheckPoint", FileProcess->getIntegerForKey("CheckPoint") + 1);
}

int Process::FileGet() {//get the process 
	if (UserDefault::getInstance()->isXMLFileExist()) {//if it have such checkPoint then return it
		return UserDefault::getInstance()->getIntegerForKey("CheckPoint");
	}
	else {//if no such a check create it ,and return 0
		UserDefault* FileProcess = UserDefault::getInstance();
		FileProcess->setIntegerForKey("CheckPoint", 0);
		return 0;
	}
}