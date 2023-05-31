#include"speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}
//读取数据
void SpeechManager::loadRecord()
{
	//每次都先清空在读取数据
	this->m_Record.clear();
	std::ifstream ifs("speech.csv", std::ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		std::cout << "文件不存在" << std::endl;

		ifs.close();
		return;
	}

	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		std::cout << "文件为空" << std::endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}


	//文件不为空
	this->fileIsEmpty = false;

	//将已读取的单个字符放回去；
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
	std::cout << "****** 欢迎参加演讲比赛 ************" << std::endl;
	std::cout << "****** 1.开始演讲比赛 **************" << std::endl;
	std::cout << "****** 2.查看往届记录 **************" << std::endl;
	std::cout << "****** 3.清空比赛记录 **************" << std::endl;
	std::cout << "****** 0.退出比赛程序 **************" << std::endl;
	std::cout << "************************************" << std::endl;

}


void SpeechManager::exitSystem()
{
	std::cout << "欢迎下次使用" << std::endl;
	exit(0);
}


void SpeechManager::initSpeech()
{
	//初始化容器
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;

}

//创建选手
void SpeechManager::createSpeaker() {
	std::string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++) {
		std::string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		//创建选手编号，放入v1容器中
		this->v1.push_back(i + 10001);

		//将选手编号以及对应选手，放入map容器中
		this->m_Speaker.insert(std::make_pair(i + 10001, sp));
	}
}


void SpeechManager::startSpeech() {
	//第一轮比赛
	//抽签
	this->speechDraw();
	//比赛
	this->speechContest();
	//显示晋级结果
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	this->speechDraw();
	//比赛
	this->speechContest();
	//显示晋级结果
	this->showScore();

	this->saveRecord();
	//每次比赛完重新装载记录
	this->loadRecord();
	std::cout << "本届比赛完毕！" << std::endl;
	system("pause");
	system("cls");

}


//抽签
void SpeechManager::speechDraw() {
	std::cout << "第" << this->m_Index << ">轮比赛选手正在抽签" << std::endl;
	std::cout << "抽签后演讲顺序如下" << std::endl;

	if (this->m_Index == 1) {

		/*random_shuffle 在 C++14 中已弃用，并在 C++17 中完全删除
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
	std::cout << "---------第" << this->m_Index << ">轮比赛正式开始----------" << std::endl;
	//临时容器 保存key分数 value 选手编号
	std::multimap<double, int, std::greater<double>> groupScore;

	//记录人数，6人一组
	int num = 0;

	//比赛人员容器
	vector<int>v_Src;
	if (this->m_Index == 1) {
		v_Src = this->v1;
	}
	else {
		v_Src = this->v2;
	}

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		//评委打分
		deque<double> d;
		//随机数种子
		srand(time(NULL));
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		//排序
		sort(d.begin(), d.end(), greater<double>());

		//去除最高分和最低分
		d.pop_back();
		d.pop_front();

		double sum = (accumulate(d.begin(), d.end(), 0.0));

		double avg = sum / (double)d.size();


		//cout << this->m_Speaker[*it].m_Name << "\t编号" << *it << "\t平均分" << avg << endl;

		//平均分放入map容器
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//key 是平均分 value 是具体编号
		groupScore.insert(make_pair(avg, *it));

		//每六人一组 取出前三名
		if (num % 6 == 0)
		{
			cout << "---第" << num / 6 << "小组名次---" << endl;
			for (auto it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号" << it->second << "姓名" << this->m_Speaker[it->second].m_Name
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//取走前三名
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

	cout << "---------第" << this->m_Index << "轮比赛完毕---------------" << endl;

	system("pause");

}



void SpeechManager::showScore() {
	using namespace std;

	cout << "-------------第" << this->m_Index << "轮晋级选手信息如下-----------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (auto it = v.begin(); it != v.end(); it++) {
		cout << "编号:  " << *it << "姓名:  " << this->m_Speaker[*it].m_Name << "得分:  "
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

	//选手数据写入
	for (auto it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";

	}
	ofs << std::endl;

	ofs.close();

	std::cout << "记录完成" << std::endl;

}

void SpeechManager::showRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++) {
		std::cout << "第" << i + 1 << "届" << std::endl
			<< "冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " \n"
			<< "亚军编号：" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " \n"
			<< "季军编号：" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << std::endl;
	}

	system("pause");
	system("cls");
}