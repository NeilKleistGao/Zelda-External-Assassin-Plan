#pragma once
#include<string>

#include<map>
struct enemyData
{
	std::string name;
	int HP;
	int damage;
	int speed;
	enemyData(int a,int b,int c){

		this->HP = a;
		this->damage = b;
		this->speed = c;
	}
};
struct objectData {
	std::string object_name;
	std::string image_path;
	std::string info_text;
	objectData(const std::string &a, const std::string &b) {
		this->image_path = a;
		this->info_text = b;
		
	}
};

 class Config
{
public:
	
	Config() = default;
	~Config() = default;
	void loadConfig(std::string filename);
	 std::map<std::string, enemyData>EnemyData;
	 std::map<std::string, objectData>ObjectData;
	enemyData getEnemy(const std::string &Name);
	objectData getObject(const std::string &Name);
};

