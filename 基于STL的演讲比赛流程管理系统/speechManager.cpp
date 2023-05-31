#include"speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}
//��ȡ����
void SpeechManager::loadRecord()
{
	//ÿ�ζ�������ڶ�ȡ����
	this->m_Record.clear();
	std::ifstream ifs("speech.csv", std::ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		std::cout << "�ļ�������" << std::endl;

		ifs.close();
		return;
	}

	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		std::cout << "�ļ�Ϊ��" << std::endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}


	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	//���Ѷ�ȡ�ĵ����ַ��Ż�ȥ��
	ifs.putback(ch);

	std::string data;

	int index = 0;
	while (ifs >> data)
	{
		//std::cout << data;
		std::vector<std::string>v;
		int pos = -1;
		int  start = 0;
		while (true)
		{
			pos = static_cast<int> (data.find(",", start));
			if (pos == -1)
			{
				break;
			}

			std::string temp = data.substr(start, pos - start);

			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(std::make_pair(index, v));
		index++;

	}
	std::cout << std::endl;
	ifs.close();

}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::show_Menu()
{
	std::cout << "**********************" << std::endl;
	std::cout << "****** ��ӭ�μ��ݽ����� ************" << std::endl;
	std::cout << "****** 1.��ʼ�ݽ����� **************" << std::endl;
	std::cout << "****** 2.�鿴�����¼ **************" << std::endl;
	std::cout << "****** 3.��ձ�����¼ **************" << std::endl;
	std::cout << "****** 0.�˳��������� **************" << std::endl;
	std::cout << "************************************" << std::endl;

}


void SpeechManager::exitSystem()
{
	std::cout << "��ӭ�´�ʹ��" << std::endl;
	exit(0);
}


void SpeechManager::initSpeech()
{
	//��ʼ������
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;

}

//����ѡ��
void SpeechManager::createSpeaker() {
	std::string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++) {
		std::string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		//����ѡ�ֱ�ţ�����v1������
		this->v1.push_back(i + 10001);

		//��ѡ�ֱ���Լ���Ӧѡ�֣�����map������
		this->m_Speaker.insert(std::make_pair(i + 10001, sp));
	}
}


void SpeechManager::startSpeech() {
	//��һ�ֱ���
	//��ǩ
	this->speechDraw();
	//����
	this->speechContest();
	//��ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index++;
	this->speechDraw();
	//����
	this->speechContest();
	//��ʾ�������
	this->showScore();

	this->saveRecord();
	//ÿ�α���������װ�ؼ�¼
	this->loadRecord();
	std::cout << "���������ϣ�" << std::endl;
	system("pause");
	system("cls");

}


//��ǩ
void SpeechManager::speechDraw() {
	std::cout << "��" << this->m_Index << ">�ֱ���ѡ�����ڳ�ǩ" << std::endl;
	std::cout << "��ǩ���ݽ�˳������" << std::endl;

	if (this->m_Index == 1) {

		/*random_shuffle �� C++14 �������ã����� C++17 ����ȫɾ��
		std::random_shuffle(v1.begin(), v1.end());*/

		std::random_device rd;
		std::shuffle(v1.begin(), v1.end(), std::default_random_engine(rd()));


		for (auto it = v1.begin(); it != v1.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "---------------" << std::endl;
	}
	else {
		std::random_device rd;
		std::shuffle(v2.begin(), v2.end(), std::default_random_engine(rd()));
		for (auto it = v2.begin(); it != v2.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "---------------" << std::endl;
	}
	system("pause");

}


void SpeechManager::speechContest() {
	using namespace std;
	std::cout << "---------��" << this->m_Index << ">�ֱ�����ʽ��ʼ----------" << std::endl;
	//��ʱ���� ����key���� value ѡ�ֱ��
	std::multimap<double, int, std::greater<double>> groupScore;

	//��¼������6��һ��
	int num = 0;

	//������Ա����
	vector<int>v_Src;
	if (this->m_Index == 1) {
		v_Src = this->v1;
	}
	else {
		v_Src = this->v2;
	}

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		//��ί���
		deque<double> d;
		//���������
		srand(time(NULL));
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		//����
		sort(d.begin(), d.end(), greater<double>());

		//ȥ����߷ֺ���ͷ�
		d.pop_back();
		d.pop_front();

		double sum = (accumulate(d.begin(), d.end(), 0.0));

		double avg = sum / (double)d.size();


		//cout << this->m_Speaker[*it].m_Name << "\t���" << *it << "\tƽ����" << avg << endl;

		//ƽ���ַ���map����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//key ��ƽ���� value �Ǿ�����
		groupScore.insert(make_pair(avg, *it));

		//ÿ����һ�� ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "---��" << num / 6 << "С������---" << endl;
			for (auto it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "���" << it->second << "����" << this->m_Speaker[it->second].m_Name
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//ȡ��ǰ����
			int count = 0;
			for (auto it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {

				if (this->m_Index == 1) {
					this->v2.push_back((*it).second);
				}
				else {
					this->vVictory.push_back((*it).second);
				}
			}
			cout << endl;
			groupScore.clear();
		}
	}

	cout << "---------��" << this->m_Index << "�ֱ������---------------" << endl;

	system("pause");

}



void SpeechManager::showScore() {
	using namespace std;

	cout << "-------------��" << this->m_Index << "�ֽ���ѡ����Ϣ����-----------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (auto it = v.begin(); it != v.end(); it++) {
		cout << "���:  " << *it << "����:  " << this->m_Speaker[*it].m_Name << "�÷�:  "
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}

	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}


void SpeechManager::saveRecord() {
	std::ofstream ofs;
	ofs.open("speech.csv", std::ios::out | std::ios::app);

	//ѡ������д��
	for (auto it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";

	}
	ofs << std::endl;

	ofs.close();

	std::cout << "��¼���" << std::endl;

}

void SpeechManager::showRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++) {
		std::cout << "��" << i + 1 << "��" << std::endl
			<< "�ھ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " \n"
			<< "�Ǿ���ţ�" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << " \n"
			<< "������ţ�" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << std::endl;
	}

	system("pause");
	system("cls");
}