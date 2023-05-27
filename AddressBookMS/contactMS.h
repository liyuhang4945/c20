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
	cout << "******1:�����ϵ��******" << endl;
	cout << "******2:��ʾ��ϵ��******" << endl;
	cout << "******3:ɾ����ϵ��******" << endl;
	cout << "******4:������ϵ��******" << endl;
	cout << "******5:�޸���ϵ��******" << endl;
	cout << "******6:�����ϵ��******" << endl;
	cout << "******0:�˳���ϵ��******" << endl;
	cout << "************************" << endl;

}

void addContacts(Addressbooks* abs)
{
	//�ж�ͨѶ¼�Ƿ�����
	if (abs->size == MAX)
	{
		return;
	}
	else
	{
		//�����ϵ��
		//����
		string name;
		cout << "������������";
		cin >> name;
		abs->contacts[abs->size].name = name;
		int sex = 0;


		while (true)
		{
			cout << "�������Ա�\t1---��\t2---Ů" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->contacts[abs->size].sex = sex;
				break;
			}
			else
			{
				cout << "������������������" << endl;
			}
		}


		int age = 18;
		while (true)
		{
			cout << "���������䣺";
			cin >> age;
			if (age >= 0 && age < 180)//�����޶�
			{
				abs->contacts[abs->size].age = age;
				break;
			}
			else
			{
				cout << "������������������" << endl;
			}

		}
		string phone;
		cout << "������绰��";
		cin >> phone;
		abs->contacts[abs->size].phone = phone;

		cout << "�������ַ��";
		string address;
		cin >> address;
		abs->contacts[abs->size].addr = address;

		(abs->size)++;
		cout << "��ӳɹ���" << endl;
	}
}

void showContacts(Addressbooks* abs)
{
	if (abs->size == 0)
	{
		cout << "����Ϊ��" << endl;
		return;
	}
	else
	{
		cout << "����\t�Ա�\t����\t�绰\t��ַ" << endl;
		for (int i = 0; i < abs->size; i++)
		{
			print_contact(&(abs->contacts[i]));
		}
	}
}

void print_contact(const Contacts* cs)
{
	cout << cs->name << "\t"
		<< (cs->sex == 1 ? "��" : "Ů") << "\t"
		<< cs->age << "\t"
		<< cs->phone << "\t"
		<< cs->addr << endl;
}

void deleteContacts(Addressbooks* abs)
{
	cout << "��������Ҫɾ���˵�������";
	string name;
	cin >> name;
	int flag = isExist(abs, name);
	if (flag == -1)
	{
		cout << "���޴���" << endl;
	}
	else
	{
		for (int i = flag; i < abs->size; i++)
		{
			abs->contacts[i] = abs->contacts[i + 1];
		}
		abs->size--;
		cout << "ɾ���ɹ�" << endl;

	}
}


void findContacts(Addressbooks* abs)
{
	cout << "��������Ҫ�����˵�����:";
	string name;
	cin >> name;
	int flag = isExist(abs, name);
	if (flag == -1)
	{
		cout << "���޴���" << endl;
	}
	else
	{
		cout << "����\t�Ա�\t����\t�绰\t��ַ" << endl;
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
	//�޸Ķ�Ӧ��������Ϣ
	string name;
	cout << "������Ҫ�޸ĵ��˵�����:";
	cin >> name;
	int flag = isExist(abs, name);
	if (flag == -1)
	{
		cout << "�޸ĵ��˲����ڣ�" << endl;
	}
	else
	{
		string name;
		cout << "������������";
		cin >> name;
		abs->contacts[flag].name = name;
		int sex = 0;


		while (true)
		{
			cout << "�������Ա�\t1---��\t2---Ů" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->contacts[flag].sex = sex;
				break;
			}
			else
			{
				cout << "������������������" << endl;
			}
		}


		int age = 0;
		while (true)
		{
			cout << "���������䣺";
			cin >> age;
			if (age >= 0 || age < 120)
			{
				abs->contacts[flag].age = age;
				break;
			}
			else
			{
				cout << "������������������" << endl;
			}

		}
		string phone;
		cout << "������绰��";
		cin >> phone;
		abs->contacts[flag].phone = phone;

		cout << "�������ַ��";
		string address;
		cin >> address;
		abs->contacts[flag].addr = address;
	}
}


void cleanABS(Addressbooks* abs)
{
	abs->size = 0;
}