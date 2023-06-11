#include<iostream>
#include<fstream>
#include<string>
#include"globalFile.h"
#include"identity.h"
#include"manager.h"
#include"student.h"
#include"teacher.h"
using namespace std;

/// <summary>
/// ��¼
/// </summary>
/// <param name="fileName">�ļ�����</param>
/// <param name="type">�������</param>
void LoginIn(string fileName, int type) {
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (ifs.is_open() == NULL) {
		cout << "�ļ���ʧ��" << endl;
		ifs.close();
		return;
	}

	//�洢��Ϣ
	int id = 0;
	string name;
	string pwd;

	//?��????
	if (type == 1) {
		cout << "����������ѧ��:" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "����������ְ����:" << endl;
		cin >> id;
	}

	cout << "��������������:" << endl;
	cin >> name;

	cout << "��������������:" << endl;
	cin >> pwd;

	if (type == 1) {
		//��֤ѧ�����
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "ѧ����֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);

				//����ѧ������Ӳ˵�
				return;
			}
		}

	}
	else if (type == 2) {
		//��֤��ʦ���
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "��ʦ��֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);

				//�����ʦ�Ӳ˵�
				return;
			}
		}
	}
	else if (type == 3) {
		//��֤����Ա���

		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			if (fName == name && fPwd == pwd) {
				cout << "����Ա��֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Manager(name, pwd);

				//�������Ա�Ӳ˵�
				return;
			}
		}
	}

	cout << "��֤ʧ��" << endl;
	system("pause");
	system("cls");
	ifs.close();

}
int main() {

	int select = 0;
	while (true)
	{
		cout << "-------��ӭʹ�û���ԤԼϵͳ-------" << endl;
		cout << "��ѡ���������" << endl;
		cout << "\t\t-----------------------\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     1,ѧ������      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     2,��    ʦ      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     3,�� �� Ա      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     0,��    ��      |\n";
		cout << "\t\t-----------------------\n";
		cout << "�����룺";

		//ѡ��
		cin >> select;
		switch (select)
		{
		case 1://ѧ��
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://��ʦ
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://����Ա
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			system("cls");
			return 0;
			break;
		default:
			cout << "�������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
