#include<iostream>
#include<mutex>
#include<thread>
#include<future>
#include<list>

#include<windows.h>


using namespace std;

//#define __WINDOWSJQ_    //定义一个开关,WINDOWS开关
//本类用于自动释放windows下的临界区，反之忘记LeaveCriticalSection()导致死锁情况的发生
class CWinLock {     //叫RAII类（Resourse Acquisition is initialization） 中文“资源获取及初始化”
				//容器，只能指针这种类，都属于RAII类
public:
	CWinLock(CRITICAL_SECTION* pCripem) {   //构造函数
		m_pCritical = pCripem;
		EnterCriticalSection(m_pCritical);
	}
	~CWinLock() {   //析构函数
		LeaveCriticalSection(m_pCritical);
	}
private:
	CRITICAL_SECTION *m_pCritical;
};
class A {
public:
	//把收到的消息(玩家命令)入到一个队列的线程里
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRechQueue()执行，插入一个元素" << i << endl;
#ifdef __WINDOWSJQ_ 
			//EnterCriticalSection(&my_winsec);  //进入临界区(加锁)
			//EnterCriticalSection(&my_winsec);  //两次进入临界区(加锁)
			CWinLock wlock(&my_winsec);     //wlock，wlock2都属于RAII类
			//CWinLock wlock2(&my_winsec);     //调用两次也没问题     
			msgRecvQueue.push_back(i);
			//LeaveCriticalSection(&my_winsec);	//离开临界区(解锁)
			//LeaveCriticalSection(&my_winsec);	//两次进入必须两次离开，没问题
#else
			std::lock_guard<std::mutex> sbguard(my_mutex);
			//std::lock_guard<std::recursive_mutex> sbguard(my_mutex);

			//testfun1();    //加了三次锁，报异常(只要lock超过1次就报异常)

			//std::chrono::milliseconds timeout(100);  //100毫秒
			//if (my_mutex.try_lock_for(timeout)) {   //等待一百毫秒尝试获取锁头
			//	//在这100毫秒之内拿到了锁
			//	msgRecvQueue.push_back(i);
			//	my_mutex.unlock();   //用完了要解锁；
			//}
			//else {
			//	//这次没拿到锁头
			//	std::chrono::microseconds sleeptime(100);
			//	std::this_thread::sleep_for(sleeptime);
			//}
			msgRecvQueue.push_back(i);  
#endif
		}
	}
	bool outMsgLULProc(int& command) 
	{	
#ifdef __WINDOWSJQ_ 
		EnterCriticalSection(&my_winsec);
		if (!msgRecvQueue.empty()) {
			int command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();   //移除第一个元素，但不返回
			LeaveCriticalSection(&my_winsec);

			return true;
		}
		LeaveCriticalSection(&my_winsec);

#else
		my_mutex.lock();
		if (!msgRecvQueue.empty()) {
			//消息队列不为空
			int command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();   //移除第一个元素，但不返回
			my_mutex.unlock();

			return true;
		}
		my_mutex.unlock();
#endif
		return false;
	}

	//把数据从消息队列中取出的线程；
	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 100000; ++i) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "outMsgLULProc()执行，去除一个元素" << command << endl;
			}
			else {
				//消息队列为空
				cout << " outMsgRecvQueue()执行，但目前消息队列中为空" << i << endl;
			}
		}
		cout << "end" << endl;
	}
	A() {
#ifdef __WINDOWSJQ_ 
		InitializeCriticalSection(&my_winsec);   //用临界区之前要先初始化
#endif
	}
	//void testfun1() {
	//	std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
	//	//干一些事情
	//	testfun2();    //奔溃
	//}
	//void testfun2(){
	//	std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
	//	//干另一些事情
	//}
private:
	list<int> msgRecvQueue;   //容器(消息队列)，专门用于代表玩家给我们发送过来的命令
	mutex my_mutex;//创建一个互斥量(一个互斥量就是一把锁)
	//std::recursive_mutex my_mutex;  //递归式的独占互斥量
	//std::timed_mutex my_mutex;   //带超时功能的独占互斥量；

#ifdef __WINDOWSJQ_     //解开开关
	CRITICAL_SECTION my_winsec;    //windwos中的临界区，非常类似于c++的mutex
#endif 
};
int main() {
	//一：windows临界区
	//以下代码实现
		//#define __WINDOWSJQ_    //定义一个开关,WINDOWS开关
		//#ifdef __WINDOWSJQ_     //解开开关
		//	CRITICAL_SECTION my_winsec;    //windwos中的临界区，非常类似于c++的mutex
		//#endif 
		//
		//#ifdef __WINDOWSJQ_ 
		//	EnterCriticalSection(&my_winsec);   //进入临界区
		//	msgRecvQueue.push_back(i);
		//	LeaveCriticalSection(&my_winsec);   //退出临界区
		//#else

	//二：多次进入临界区实验
		//#ifdef __WINDOWSJQ_ 
		//	EnterCriticalSection(&my_winsec);  //进入临界区(加锁)
		//	EnterCriticalSection(&my_winsec);  //两次进入临界区(加锁)
		//	msgRecvQueue.push_back(i);
		//	LeaveCriticalSection(&my_winsec);	//离开临界区(解锁)
		//	LeaveCriticalSection(&my_winsec);	//两次进入必须两次离开
		//#endif
				//在同一线程中(不同线程就会卡住等待)中，windows中的“相同临界区变量”代表的临界区的进入EnterCriticalSection()。
						//可以被多次调用，但是EnterCriticalSection()，就得几次LeaveCriticalSection();

		//my_mutex.lock();
		//my_mutex.lock();  //报异常，和windows有区别
		//msgRecvQueue.push_back(i);     
		//my_mutex.unlock();
		//my_mutex.unlock();
				//在c++11中加两次锁就会报错，不允许同一个线程中lock同一个互斥量多次，否则报异常。
	//三：自动析构技术
		//std::lock_guard<std::mutex>
			//std::lock_guard<std::mutex> sbguard(my_mutex);
			//std::lock_guard<std::mutex> sbguard1(my_mutex);
						//lock_guard也不能调用两次

			//class CWinLock {  //本类用于自动释放windows下的临界区，反之忘记LeaveCriticalSection()导致死锁情况的发生
			//public:
			//	CWinLock(CRITICAL_SECTION* pCripem) {   //构造函数
			//		m_pCritical = pCripem;
			//		EnterCriticalSection(m_pCritical);
			//	}
			//	~CWinLock() {   //析构函数
			//		LeaveCriticalSection(m_pCritical);
			//	}
			//private:
			//	CRITICAL_SECTION* m_pCritical;
			//};

			//上面的class CWinLock   类似于std::lock_guard<std::mutex> sbguard(my_mutex);
				//但是windows的临界区可以连续两次调用该类

	//四：recursive_mutex递归的独占互斥量
	//std::mutex:独占互斥量，自己拿到lock时，被人就lock不了
	//recursive_mutex:递归的独占互斥量，允许同一个线程，同一个互斥量多次被lock()。效率上比mutex要差一些
		//std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
		//testfun1();

		//如果出现recursive_mutex，就要考虑代码的效率是不是有问题，最好能不使用
		//递归次数有限制，递归太多可能报异常


	//五：带超时的互斥量std::time_mutex和std::recursive_timed_mutex
	//std::timed_mutex :是带超时功能的独占互斥量

			//try_lock_for():参数是等待一段时间。如果我拿到了锁，或者等待超过时间没拿到锁头，就走下来；
			//std::chrono::milliseconds timeout(100);  //100毫秒
			//if (my_mutex.try_lock_for(timeout)) {   //等待一百毫秒尝试获取锁头
			//	//在这100毫秒之内拿到了锁
			//	msgRecvQueue.push_back(i);
			//	my_mutex.unlock();   //用完了要解锁；
			//}
			//else {
			//	//这次没拿到锁头
			//	std::chrono::microseconds sleeptime(100);
			//	std::this_thread::sleep_for(sleeptime);
			//}

			//try_lock_unti()：参数是一个未来的时间点，在这个未来时间没到的时间段内。如果拿到了锁，那么就走下来
								//如果时间到了，没拿到锁，程序流程也走下来。
									//std::chrono::milliseconds timeout(100);
									//my_mytex.try_lock_unti(chrono::steady_clock::now() + timeout);
					
	//std::recursive_timed_mutex:带超时功能的递归互斥量
	A myobja;
	std::thread muOutnMsgObj(&A::outMsgRecvQueue, &myobja);
	std::thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myInMsgObj.join();
	muOutnMsgObj.join();
	return 0;
}