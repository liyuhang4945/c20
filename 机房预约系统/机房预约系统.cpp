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
/// 登录
/// </summary>
/// <param name="fileName">文件名字</param>
/// <param name="type">身份类型</param>
void LoginIn(string fileName, int type) {
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (ifs.is_open() == NULL) {
		cout << "文件打开失败" << endl;
		ifs.close();
		return;
	}

	//存储信息
	int id = 0;
	string name;
	string pwd;

	//?ж????
	if (type == 1) {
		cout << "请输入您的学号:" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "请输入您的职工号:" << endl;
		cin >> id;
	}

	cout << "请输入您的姓名:" << endl;
	cin >> name;

	cout << "请输入您的密码:" << endl;
	cin >> pwd;

	if (type == 1) {
		//验证学生身份
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "学生验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);

				//进入学生身份子菜单
				return;
			}
		}

	}
	else if (type == 2) {
		//验证教师身份
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "教师验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);

				//进入教师子菜单
				return;
			}
		}
	}
	else if (type == 3) {
		//验证管理员身份

		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			if (fName == name && fPwd == pwd) {
				cout << "管理员验证登录成功" << endl;
				system("pause");
				system("cls");

				person = new Manager(name, pwd);

				//进入管理员子菜单
				return;
			}
		}
	}

	cout << "验证失败" << endl;
	system("pause");
	system("cls");
	ifs.close();

}
int main() {

	int select = 0;
	while (true)
	{
		cout << "-------欢迎使用机房预约系统-------" << endl;
		cout << "请选择您的身份" << endl;
		cout << "\t\t-----------------------\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     1,学生代表      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     2,教    师      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     3,管 理 员      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     0,退    出      |\n";
		cout << "\t\t-----------------------\n";
		cout << "请输入：";

		//选择
		cin >> select;
		switch (select)
		{
		case 1://学生
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://教师
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "欢迎下次使用" << endl;
			system("pause");
			system("cls");
			return 0;
			break;
		default:
			cout << "输入错误" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
