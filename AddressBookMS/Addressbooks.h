#pragma once
const int MAX = 1000;//��ϵ������Ϊ1000��
struct Contacts
{
	string name;
	int sex;
	int age;
	string phone;
	string addr;
};
struct Addressbooks
{
	Contacts contacts[MAX];
	int size = 0;//������Ա���� ��ʼ��Ϊ��
};