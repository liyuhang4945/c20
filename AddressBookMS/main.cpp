#include<iostream>
using namespace std;
#include"contactMS.h"

// ��ɾ�Ĳ� show clear �˳�

int main()
{

	//ͨѶ¼��ʼ��
	Addressbooks abs;


	//showMenu();
	// �˳�
	//����ѡ�����
	int select = 0;
	while (true)
	{
		//�˵�����
		showMenu();
		cin >> select;
		switch (select)
		{
		case 1://1:�����ϵ��
			addContacts(&abs);
			break;
		case 2://2:��ʾ��ϵ��
			showContacts(&abs);
			break;
		case 3://3:ɾ����ϵ��
			deleteContacts(&abs);
			break;
		case 4://4:������ϵ��
			findContacts(&abs);
			break;
		case 5://5:�޸���ϵ��
			modifyContacts(&abs);
			break;
		case 6://6:�����ϵ��
			cleanABS(&abs);
			break;
		case 0://�˳�
			cout << "��ӭ�´�ʹ��" << endl;
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