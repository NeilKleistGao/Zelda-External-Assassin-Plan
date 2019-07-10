#include "Config.h"

#include "base/Decryptor.h"
#include "cocos2d.h"

#include <fstream>
#include <stdio.h>
#include <sstream>
#include <map>
#include <vector>

using namespace cocos2d;

Config* Config::conf = nullptr;//initial conf as NULLptr

Config* Config::getInstance() {//create single case
	if (!conf) {
		conf = new(std::nothrow) Config();
	}

	return conf;
}
/*config .csv  file*/

void Config::loadConfig(std::string filename) {
	FileUtils::getInstance();
	if (filename == "config/enemy.csv") {
		std::istringstream EnemyFile(FileUtils::getInstance()->getStringFromFile(filename));
		std::string data;
		char buff[128];

		EnemyFile.getline(buff,128);//ignore the first line
		while (EnemyFile.getline(buff, 128)) {
			data = buff;
			std::istringstream sin(data);
			std::vector<std::string> fields; //define a vector
			std::string field;
			
			while (getline(sin, field, ',')) //Read the characters in the string stream sin into the field string with a comma as the separator
			{
				fields.push_back(field); //Add the string just read to the vector fields
			}
			EnemyData.insert(std::pair<std::string, enemyData>(fields[0], enemyData(atoi(fields[1].c_str()), atoi(fields[2].c_str()), atoi(fields[3].c_str()))));
		}
	}
	else if (filename == "config/objects.csv") {
		std::istringstream ObjectFile(FileUtils::getInstance()->getStringFromFile(filename));
		std::string data;
		char buff[128];

		ObjectFile.getline(buff, 128);//ignore the first line
		while (ObjectFile.getline(buff, 128)) {
			data = buff;
			std::istringstream sin(data);
			std::vector<std::string> fields; //define a vector
			std::string field;
			while (getline(sin, field, ',')) //Read the characters in the string stream sin into the field string with a comma as the separator
			{
				fields.push_back(field); //Add the string just read to the vector fields
			}
			ObjectData.insert(std::pair<std::string, objectData>(fields[0], objectData(fields[1],fields[2])));
		}
	}
	
	else {
		printf("filename error");
	}


}
/*Use the map container to return the details of the pair by the corresponding name*/
enemyData Config:: getEnemy(const std::string &Name) {
	 for(auto it=EnemyData.begin();it!=EnemyData.end();it++){
		 if(it->first==Name){//Iterator lookup
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

