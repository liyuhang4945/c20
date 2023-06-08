#include<iostream>

using namespace std;

int main() {

	int select = 0;
	while (true)
	{
		cout << "-------欢迎登录机房预约系统-------" << endl;
		cout << "请输入您的身份" << endl;
		cout << "\t\t-----------------------\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     1,学生代表      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     2,老    师      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     3,管 理 员      |\n";
		cout << "\t\t|                     |\n";
		cout << "\t\t|     0,退    出      |\n";
		cout << "\t\t-----------------------\n";
		cout << "输入您的选择：";

		//接受用户输入
		cin >> select;
		switch (select)
		{
		case 1://学生身份
			break;
		case 2://老师
			break;
		case 3://管理员
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
