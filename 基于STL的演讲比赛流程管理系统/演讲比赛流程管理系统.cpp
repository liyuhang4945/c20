#include<iostream>

using namespace std;
#include"speechManager.h"
int main()
{
	//�������������
	SpeechManager sm;

	/*
	���Դ���ѡ���Ƿ�ʵ��
	for (auto it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		std::cout << it->first << it->second.m_Name << std::endl;
	}
	*/
	//�洢�û�����
	int choice = 0;

	while (true)
	{
		sm.show_Menu();
		cout << "����������ѡ��: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}