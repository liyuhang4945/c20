#include<iostream>
using namespace std;
#include"contactMS.h"

// 增删改查 show clear 退出

int main()
{

	//通讯录初始化
	Addressbooks abs;


	//showMenu();
	// 退出
	//功能选择变量
	int select = 0;
	while (true)
	{
		//菜单调用
		showMenu();
		cin >> select;
		switch (select)
		{
		case 1://1:添加联系人
			addContacts(&abs);
			break;
		case 2://2:显示联系人
			showContacts(&abs);
			break;
		case 3://3:删除联系人
			deleteContacts(&abs);
			break;
		case 4://4:查找联系人
			findContacts(&abs);
			break;
		case 5://5:修改联系人
			modifyContacts(&abs);
			break;
		case 6://6:清空联系人
			cleanABS(&abs);
			break;
		case 0://退出
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}

		system("pause");
		system("cls");
	}
	return 0;
}