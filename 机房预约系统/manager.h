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
	//�˵�����

	virtual void operMenu();
	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputerRoom();


	//���ԤԼ
	void cleanFile();

};

