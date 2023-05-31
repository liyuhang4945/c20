#include<iostream>

using namespace std;
#include"speechManager.h"
int main()
{
	//创建管理类对象
	SpeechManager sm;

	/*
	测试创建选手是否实现
	for (auto it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		std::cout << it->first << it->second.m_Name << std::endl;
	}
	*/
	//存储用户输入
	int choice = 0;

	while (true)
	{
		sm.show_Menu();
		cout << "请输入您的选择: " << endl;
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