#pragma once
#include<iostream>
#include"Addressbooks.h"
using namespace std;

void showMenu();

void addContacts(Addressbooks* abs);

void showContacts(Addressbooks* abs);
void print_contact(const Contacts* cs);

void deleteContacts(Addressbooks* abs);

int isExist(Addressbooks* abs, string name);


void findContacts(Addressbooks* abs);

void modifyContacts(Addressbooks* abs);

void cleanABS(Addressbooks* abs);
void showMenu() {
	cout << "************************" << endl;
	cout << "******1:添加联系人******" << endl;
	cout << "******2:显示联系人******" << endl;
	cout << "******3:删除联系人******" << endl;
	cout << "******4:查找联系人******" << endl;
	cout << "******5:修改联系人******" << endl;
	cout << "******6:清空联系人******" << endl;
	cout << "******0:退出联系人******" << endl;
	cout << "************************" << endl;

}

void addContacts(Addressbooks* abs)
{
	//判断通讯录是否已满
	if (abs->size == MAX)
	{
		return;
	}
	else
	{
		//添加联系人
		//姓名
		string name;
		cout << "请输入姓名：";
		cin >> name;
		abs->contacts[abs->size].name = name;
		int sex = 0;


		while (true)
		{
			cout << "请输入性别\t1---男\t2---女" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->contacts[abs->size].sex = sex;
				break;
			}
			else
			{
				cout << "输入有误请重新输入" << endl;
			}
		}


		int age = 18;
		while (true)
		{
			cout << "请输入年龄：";
			cin >> age;
			if (age >= 0 && age < 180)//年龄限定
			{
				abs->contacts[abs->size].age = age;
				break;
			}
			else
			{
				cout << "输入有误请重新输入" << endl;
			}

		}
		string phone;
		cout << "请输入电话：";
		cin >> phone;
		abs->contacts[abs->size].phone = phone;

		cout << "请输入地址：";
		string address;
		cin >> address;
		abs->contacts[abs->size].addr = address;

		(abs->size)++;
		cout << "添加成功！" << endl;
	}
}

void showContacts(Addressbooks* abs)
{
	if (abs->size == 0)
	{
		cout << "人数为空" << endl;
		return;
	}
	else
	{
		cout << "姓名\t性别\t年龄\t电话\t地址" << endl;
		for (int i = 0; i < abs->size; i++)
		{
			print_contact(&(abs->contacts[i]));
		}
	}
}

void print_contact(const Contacts* cs)
{
	cout << cs->name << "\t"
		<< (cs->sex == 1 ? "男" : "女") << "\t"
		<< cs->age << "\t"
		<< cs->phone << "\t"
		<< cs->addr << endl;
}

void deleteContacts(Addressbooks* abs)
{
	cout << "请输入您要删除人的姓名：";
	string name;
	cin >> name;
	int flag = isExist(abs, name);
	if (flag == -1)
	{
		cout << "查无此人" << endl;
	}
	else
	{
		for (int i = flag; i < abs->size; i++)
		{
			abs->contacts[i] = abs->contacts[i + 1];
		}
		abs->size--;
		cout << "删除成功" << endl;

	}
}


void findContacts(Addressbooks* abs)
{
	cout << "请输入您要查找人的姓名:";
	string name;
	cin >> name;
	int flag = isExist(abs, name);
	if (flag == -1)
	{
		cout << "查无此人" << endl;
	}
	else
	{
		cout << "姓名\t性别\t年龄\t电话\t地址" << endl;
		print_contact(&(abs->contacts[flag]));
	}
}

int isExist(Addressbooks* abs, string name)
{
	for (int i = 0; i < abs->size; i++)
	{
		if (name == abs->contacts[i].name)
		{
			return i;
		}
	}
	return -1;
}


void modifyContacts(Addressbooks* abs)
{
	//修改对应姓名的信息
	string name;
	cout << "输入你要修改的人的姓名:";
	cin >> name;
	int flag = isExist(abs, name);
	if (flag == -1)
	{
		cout << "修改的人不存在！" << endl;
	}
	else
	{
		string name;
		cout << "请输入姓名：";
		cin >> name;
		abs->contacts[flag].name = name;
		int sex = 0;


		while (true)
		{
			cout << "请输入性别\t1---男\t2---女" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->contacts[flag].sex = sex;
				break;
			}
			else
			{
				cout << "输入有误请重新输入" << endl;
			}
		}


		int age = 0;
		while (true)
		{
			cout << "请输入年龄：";
			cin >> age;
			if (age >= 0 || age < 120)
			{
				abs->contacts[flag].age = age;
				break;
			}
			else
			{
				cout << "输入有误请重新输入" << endl;
			}

		}
		string phone;
		cout << "请输入电话：";
		cin >> phone;
		abs->contacts[flag].phone = phone;

		cout << "请输入地址：";
		string address;
		cin >> address;
		abs->contacts[flag].addr = address;
	}
}


void cleanABS(Addressbooks* abs)
{
	abs->size = 0;
}