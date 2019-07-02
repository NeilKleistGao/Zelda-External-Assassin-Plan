#include "process.h"
Process* Process::_instance = nullptr;
Process* Process::getInstance() {
	if (!_instance) {
		_instance = new(std::nothrow) Process();
	}

	return _instance;
}
int Process::FileGet() {
	
	if (UserDefault::getInstance()->isXMLFileExist()) {
		return UserDefault::getIntegerForKey("CheckPoint");
		
	}
	else {
		UserDefault *FileProcess = UserDefault::getInstance();
		FileProcess->setIntegerForKey("CheckPoint", 0);
		return 0;
	}
}
void Process::FileModif() {
	UserDefault *FileProcess = UserDefault::getInstance();
	FileProcess->setIntegerForKey("CheckPoint", FileProcess->getIntegerForKey("CheckPoint")+1);
}
