# 第一个thread

```
#include<thread>
// Linux-lpthread
#include<iostream>
using namespace std;
 
 
void ThreadMain() {
	cout << "begin sub thread main" << endl;
	cout << "sub thread ID:" << this_thread::get_id << endl;
	this_thread::sleep_for(5s);
	this_thread::sleep_for(chrono::seconds(5));
}
int main(int argc, char* argv[]) {
 
	cout << "main thread ID:" << this_thread::get_id << endl;
	thread th(ThreadMain);
	//阻塞，等待子线程退出
	th.join();
	return 0;
}
```

```
#include<thread>
// Linux-lpthread
#include<iostream>
using namespace std;
bool is_exit = false;
void ThreadMain() {
	cout << "begin sub thread main" << endl;
	
	for (int i = 0; i < 10; i++) {
		if (is_exit==true) {
			break;
		}
		cout << "sub thread ID:" << this_thread::get_id << endl;
		this_thread::sleep_for(1000ms);
	}
}
int main(int argc, char* argv[]) {
 
	
	{
		thread th(ThreadMain);//出错
		th.detach(); //守护线程
		//主线程退出后， 子线程不一定退出
	}
	{
		thread th(ThreadMain);//出错
		this_thread::sleep_for(chrono::seconds(2));
		is_exit = true;//通知子线程退出
		cout << "等待子线程退出" << endl;
		th.join(); //主线程阻塞，等待子线程退出
		cout << "子线程退出" << endl;
	}
	
	getchar();
	return 0;
}
```