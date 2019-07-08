#pragma once
#include<string>

#include<map>
struct enemyData//Define a structure to store enemy data
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
struct objectData {//
	std::string object_name;//name
	std::string image_path;//file path
	std::string info_text;//message
	objectData(const std::string &a, const std::string &b) {
		this->image_path = a;
		this->info_text = b;
		
	}
};

class Config
{
public:
	static Config* getInstance();

	void loadConfig(std::string filename);//Load configuration file 
	enemyData getEnemy(const std::string &Name);//get the enemy data
	objectData getObject(const std::string &Name);//gat the object data
private:
	static Config* conf;
	//define two map container
	std::map<std::string, enemyData>EnemyData;
	std::map<std::string, objectData>ObjectData;

};

