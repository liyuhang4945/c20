#pragma once
#include<iostream>
using namespace std;

//身份抽象基类
class Identity
{
public:
	Identity();
	// 操作菜单，纯虚函数 要求子类必须重写，该类无法创建对象
	virtual void operMenu() = 0;
	string m_userName;//用户名
	string m_Pwd;//密码
	~Identity();

};

Identity::Identity()
{
}

Identity::~Identity()
{
}