#pragma once

class Process
{
public:
	static Process* getInstance();
	void FileModify();
	int FileGet();
private:
	static Process* instance;
	Process() = default;
	~Process() = default;
};

