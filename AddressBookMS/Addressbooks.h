#pragma once
const int MAX = 1000;//联系人上限为1000人
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
	int size = 0;//现有人员个数 初始化为零
};