#pragma once
#include<iostream>
using namespace std;

//��ݳ������
class Identity
{
public:
	Identity();
	// �����˵������麯�� Ҫ�����������д�������޷���������
	virtual void operMenu() = 0;
	string m_userName;//�û���
	string m_Pwd;//����
	~Identity();

};

Identity::Identity()
{
}

Identity::~Identity()
{
}