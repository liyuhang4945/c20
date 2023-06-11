#pragma once 
#include<iostream>
using namespace std;
#include"identity.h"

class Manager
	:public Identity
{
public:
	Manager();

	Manager(string name, string pwd);
	//菜单界面

	virtual void operMenu();
	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputerRoom();


	//清空预约
	void cleanFile();

};

