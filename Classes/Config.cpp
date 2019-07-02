#include "Config.h"
#include<fstream>
#include<stdio.h>
#include <sstream>
#include<map>
#include<vector>
void Config::loadConfig(std::string filename) {
	if (filename == "enemy.csv") {
		std::fstream EnemyFile(filename);
		std::string data;
		std::getline(EnemyFile,data);//跳过第一行
		while (std::getline(EnemyFile, data)) {
			std::istringstream sin(data);
		std::	vector<std::string> fields; //声明一个字符串向量
			std::string field;
			
			while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			{
				fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
			}
			EnemyData.insert(std::pair<std::string, enemyData>(fields[0], enemyData(atoi(fields[1].c_str()), atoi(fields[2].c_str()), atoi(fields[3].c_str()))));
	}
		EnemyFile.close();
	}
	else if (filename == "objects.csv") {
		std::fstream ObjectFile(filename);
		std::string data;
		std::getline(ObjectFile, data);//跳过第一行
		while (std::getline(ObjectFile, data)) {
			std::istringstream sin(data);
			std::vector<std::string> fields; //声明一个字符串向量
			std::string field;
			while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			{
				fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
			}
			ObjectData.insert(std::pair<std::string, objectData>(fields[0], objectData(fields[1],fields[2])));
		}
		ObjectFile.close();
	}
	
	else {
		printf("filename error");
	}


}
enemyData Config:: getEnemy(const std::string &Name) {
	 for(auto it=EnemyData.begin();it!=EnemyData.end();it++){
		 if(it->first==Name){
			 return it->second;
		 }

	 }printf("there is no such Enemy");
	
}
   objectData Config::getObject(const std::string &Name) {
	   for (auto it = ObjectData.begin(); it !=ObjectData.end(); it++) {
		   if (it->first == Name) {
			   return it->second;
		   }
	}printf("there is no such Object");

}

