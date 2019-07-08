#pragma once
/*save the game process*/
class Process
{
public:
	static Process* getInstance();
	void FileModify();//modify process
	int FileGet();//get the process data
private:
	static Process* instance;
};

