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
//�ṩ�˵�ҳ�潻��
//���ݽ��������̿���
//�ļ���д


//�ݽ�������
class SpeechManager
{
public:
	SpeechManager();

	//չʾ�˵�
	void show_Menu();

	//��ʼ������
	void initSpeech();

	//����ѡ�ַ���
	void createSpeaker();

	void startSpeech();

	//��ǩ
	void speechDraw();

	//��ʼ����
	void speechContest();
	//��ʾ�������
	void showScore();

	void saveRecord();

	//�˳�ϵͳ
	void exitSystem();


	void loadRecord();

	//�鿴�����¼
	void showRecord();
	~SpeechManager();

	bool fileIsEmpty;
	std::map<int, std::vector<std::string>> m_Record;
	//��һ�ֲ�����
	std::vector<int> v1;
	//�ڶ��ֲ�����
	std::vector<int> v2;
	//����ʤ����
	std::vector<int> vVictory;

	std::map<int, Speaker> m_Speaker;

	//�ݽ���������
	int m_Index;
};

