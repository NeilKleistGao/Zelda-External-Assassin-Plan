#include "Config.h"
#include<fstream>
#include<stdio.h>
#include <sstream>
#include<map>
#include<vector>

Config* Config::conf = nullptr;

Config* Config::getInstance() {
	if (!conf) {
		conf = new(std::nothrow) Config();
	}

	return conf;
}

void Config::loadConfig(std::string filename) {
	if (filename == "config/enemy.csv") {
		std::fstream EnemyFile(filename);
		std::string data;
		std::getline(EnemyFile,data);//������һ��
		while (std::getline(EnemyFile, data)) {
			std::istringstream sin(data);
		std::	vector<std::string> fields; //����һ���ַ�������
			std::string field;
			
			while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
			{
				fields.push_back(field); //���ոն�ȡ���ַ�����ӵ�����fields��
			}
			EnemyData.insert(std::pair<std::string, enemyData>(fields[0], enemyData(atoi(fields[1].c_str()), atoi(fields[2].c_str()), atoi(fields[3].c_str()))));
	}
		EnemyFile.close();
	}
	else if (filename == "config/objects.csv") {
		std::fstream ObjectFile(filename);
		std::string data;
		std::getline(ObjectFile, data);//������һ��
		while (std::getline(ObjectFile, data)) {
			std::istringstream sin(data);
			std::vector<std::string> fields; //����һ���ַ�������
			std::string field;
			while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
			{
				fields.push_back(field); //���ոն�ȡ���ַ�����ӵ�����fields��
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

