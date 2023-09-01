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

# 1.2

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

# 1.3全局函数 

```
class Para {
public:
	Para() { cout << "create" << endl; }
	~Para()
	{
		cout << "drop" << endl;
	}
	Para(const Para& p) { cout << "copy" << endl; }
	string name;
};
void ThreadMain(int p1,double p2,string str,Para p4) {
	cout << "ThreadMain:" << p1 << " " << p2 << " " << str << endl;
}
 
 
int main(int argc, char* argv[]) {
 
	thread th;
	Para p;
	p.name = "he";
	th = thread(ThreadMain, 101, 1.1, "test", p);
	th.join();
	return 0;
}
```

create
copy
copy
ThreadMain:101 1.1 test
drop
drop
drop

传值，会调用两次拷贝，

# 1.4 参数传递的坑

- 传递空间已销毁
- 多线程共享访问同一空间
- 传递的指针变量的生命周期小于线程

```
class Para {
public:
	Para() { cout << "create" << endl; }
	~Para()
	{
		cout << "drop" << endl;
	}
	Para(const Para& p) { cout << "copy" << endl; }
	string name;
};
void ThreadMain(int p1,double p2,string str,Para p4) {
	cout << "ThreadMain:" << p1 << " " << p2 << " " << str << endl;
}
void ThreadMainPtr(Para* p) {
	this_thread::sleep_for(chrono::seconds(1));
	cout << "ThreadMain:" << p->name<<endl;
}
 
void ThreadMainRef(Para& p) {
	this_thread::sleep_for(chrono::seconds(2));
	cout << "ThreadMain:" << p.name << endl;
}
int main(int argc, char* argv[]) {
 
	{
		thread th;
		Para p;
		p.name = "a";
		th = thread(ThreadMainRef, ref(p));
		th.join();
	}
	{
		//传递指针参数
		//
		thread th;
		Para p;
		p.name = "a";
		th = thread(ThreadMainPtr, &p);//错误线程访问的内部资源提前释放
		th.detach();
		
	}
	getchar();
	{
		thread th;
		Para p;
		p.name = "he";
		th = thread(ThreadMain, 101, 1.1, "test", p);
		th.join();
	}
	return 0;
}
```

# 1.5 成员函数作为入口 封装线程基类接口



```
#include<thread>
// Linux-lpthread
#include<iostream>
#include<string>
using namespace std;
 
class MyThread{
public:
	//入口线程函数
	void Main() {
		cout << "Mythread" << endl;
		cout << name << " " << age;
	}
	string name = "";
	int age = 100;
};
 
class XThread
{
public:
	XThread();
	virtual void Start() {
		is_exit_ = false;
		th_ = std::thread(&XThread::Main, this);
	}
 
	virtual void Wait() {
		if (th_.joinable()) {
			th_.join();
		}
	}
 
	virtual void Stop() {
		is_exit_ = true;
		Wait();
	}
	~XThread();
	string name;
	bool is_exit() { return is_exit_; }
private:
	virtual void Main() = 0;
	std::thread th_;
	bool is_exit_ = false;
};
 
class TestThread:public XThread {
public:
	void Main() override{
		cout << "Test main begin" << endl;
		while (!is_exit())
		{
			
			this_thread::sleep_for(100ms);
			cout << "." << flush;
		}
		cout << "test main end" << endl;
	}
 
};
XThread::XThread()
{
}
 
XThread::~XThread()
{
}
int main(int argc, char* argv[]) {
 
	{
		TestThread t;
		t.name = "hello";
		t.Start();
		getchar();
		this_thread::sleep_for(3000ms);
		t.Stop();
		t.Wait();
	}
	getchar();
	{
		/*MyThread myth;
		myth.name = "01";
		myth.age = 20;
 
		thread th(&MyThread::Main, &myth);
		th.join();*/
	}
	return 0;
}
```

# lambda 临时函数作为线程入口函数

```
// lambda 临时函数作为线程入口函数
// [] ()-> 返回值类型{}
 
class TestLambda {
public:
	void Start()
	{
		thread th(
			[this]() {cout << "name = " << this->name << endl; }
		);
		th
			.join();
	}
	string name = "Test Lambda class";
};
 
int main(int argc, char* argv[]) {
 
	{
		thread th(
			[](int i) {cout << "test lambda" << i << endl; }
		, 123);
		th.join(); 
	}
	{
		
	}
	return 0;
}
```

# 多线程状态

## 状态说明：

- 初始化
  - 线程创建
- 就绪
  - 等待cpu调度
- 运行
  - 正在运行
- 阻塞
  - 阻塞挂起 {pend{锁，事件，信号量。} suspend{主动pend}delay{延时阻塞}，pendtime{因为锁等超时等待}}
- 退出

## 竞争状态和临界区

- 多线程同时读写共享数据
- 读写共享数据的代码片段



对临界区进行保护 ，使同时只有一个线程读取

## 互斥体和锁 mutex

mutex

```
static std::mutex mux;
void TestThread()
{
	//获取锁资源，没有就等待
	mux.lock();
	cout << "==================" << endl;
	cout << "Test 001" << endl;
	cout << "Test 002" << endl;
	cout << "Test 003" << endl;
	cout << "==================" << endl;
	mux.unlock();
}
int main(int argc,char* argv[]) {
 
	for (int i = 0; i < 10; i++) {
		thread th(TestThread);
		th.detach();
	}
	getchar();
	return 0;
}
```

## 互斥锁的坑_线程抢占不到资源

```
void ThreadMainMux(int i)
{
	for (;;) {
		mux.lock();
		cout << i << "in" << endl;
		this_thread::sleep_for(1000ms);
		mux.unlock();
		this_thread::sleep_for(1ms);
	}
}

解决方法：在解锁之后，等待一会。
```

## 超时锁应用timed_mutex(避免长时间死锁)

- 记录锁获取情况

- 多次超时

- 记录日志，获取错误情况

- ```
  timed_mutex tmux;
   
  void ThreadMainTime(int i) {
  	for (;;) {
  		if (!tmux.try_lock_for(chrono::milliseconds(1000))) {
  			cout << i << "[try_lock_for timeout]" << endl;
  			continue;
  		}
  		cout << i << "in [i]"<<endl;
  		this_thread::sleep_for(2000ms);
  		tmux.unlock();
  		this_thread::sleep_for(1ms);
  	}
  }
  ```

## 递归锁 recursive_mutex 和recursive_timed_mutex用于业务组合

- 同一把锁可以锁多次，避免一些不必要的死锁

- 组合业务，用到同一个锁

- ```
  void Task1() {
  	rmux.lock();
  	cout << "in task 1" << endl;
  	rmux.unlock();
  }
  void Task2() {
  	rmux.lock();
  	cout << "in task 2" << endl;
  	rmux.unlock();
  }
  void ThreadMainRef(int i) {
  	for (;;) {
  		rmux.lock();
  		Task1();
  		cout << i << "in []" << endl;
  		this_thread::sleep_for(2000ms);
  		Task2();
  		rmux.unlock();
  		this_thread::sleep_for(1ms);
  		
  	}
  }
  ```



## 共享锁shared_mutex

- 14 共享超时互斥锁shared_timed_mutex

- 17 共享互斥shared_mutex

- 写时 互斥，读取不需要

- ```
  //17
  //shared_mutex smux;
  shared_timed_mutex stmux;
   
  void ThreadRead(int i) {
  	for (;;) {
  		stmux.lock_shared();
  		cout << i << " read" << endl;
  		this_thread::sleep_for(500ms);
  		stmux.unlock_shared();
  		this_thread::sleep_for(1ms);
  	}
  }
   
  void ThreadWriter(int i)
  {
  	for (;;)
  	{
  		//读取
  		stmux.lock_shared();
  		stmux.unlock_shared();
  		//互斥
  		stmux.lock();
  		cout << i << "Write" << endl;
  		this_thread::sleep_for(1000ms);
  		stmux.unlock();
  		this_thread::sleep_for(1ms);
  	}
  }
  ```

```

```

## 利用栈特性自动释放锁RALL

Rall （资源获取即初始化）使用局部对象来管理资源的技术，生命周期由操作系统来管理

