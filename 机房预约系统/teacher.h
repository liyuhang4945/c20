#pragma once
#include<iostream>
using namespace std;
#include "identity.h"
class Teacher :
	public Identity
{
public:
	Teacher();






	Teacher(int m_EmpId, string name, string pwd);

	virtual void operMenu();
	//菜单功能
	void showAllOrder();

	void validOrder();


	//教师编号
	int m_EmpId;
};

