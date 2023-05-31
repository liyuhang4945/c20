#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<numeric>
#include"Speaker.h"
#include<algorithm>
#include<random>
#include <functional>
#include<deque>
#include<string>
#include<fstream>
//提供菜单页面交互
//对演讲比赛流程控制
//文件读写


//演讲管理类
class SpeechManager
{
public:
	SpeechManager();

	//展示菜单
	void show_Menu();

	//初始化容器
	void initSpeech();

	//创建选手方法
	void createSpeaker();

	void startSpeech();

	//抽签
	void speechDraw();

	//开始比赛
	void speechContest();
	//显示晋级结果
	void showScore();

	void saveRecord();

	//退出系统
	void exitSystem();


	void loadRecord();

	//查看往届记录
	void showRecord();
	~SpeechManager();

	bool fileIsEmpty;
	std::map<int, std::vector<std::string>> m_Record;
	//第一轮参赛者
	std::vector<int> v1;
	//第二轮参赛者
	std::vector<int> v2;
	//三名胜出者
	std::vector<int> vVictory;

	std::map<int, Speaker> m_Speaker;

	//演讲比赛轮数
	int m_Index;
};

