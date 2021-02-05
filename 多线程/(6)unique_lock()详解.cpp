#include<iostream>
#include<list>
#include<mutex>
#include<thread>

using namespace std;
class A {
public:
	std::unique_lock<std::mutex> rtn_unique_lock()
	{
		std::unique_lock<std::mutex> tmpguard(my_mutex2);
		return tmpguard;  //从函数返回一个局部的unique_lock对象是可以的
						//返回这种局部对象tmpguard会导致系统生成unique_lock对象，并调用unique_lock对象的移动构造函数。
	}
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRechQueue()执行，插入一个元素" << i << endl;
			//my_mutex1.lock();   //要先lock，后续才能用unique_lock的std::adopt_lock参数
			//std::unique_lock<std::mutex> sbguard1(my_mutex1,adopt_lock);
			//std::unique_lock<std::mutex> sbguard1(my_mutex1,std::try_to_lock);  //使用前提是先前没有lock
			//if (sbguard1.owns_lock()) {
			//std::unique_lock<std::mutex> sbguard1(my_mutex1, std::defer_lock);  //没有加锁的my_mutex1
			std::unique_lock<std::mutex> sbguard1(my_mutex1);
			std::mutex* ptx = sbguard1.release();   //现在有责任自己解锁my_mutex1;
			msgRecvQueue.push_back(i);
		
			ptx->unlock();   //必须自己负责unlock();
		}
	}
	bool outMsgLULProc(int& command) 
	{	
		//std::lock_guard<std::mutex> sbguard(my_mutex1);
		std::unique_lock<std::mutex> sbguard1(my_mutex1);

		//std::chrono::milliseconds dura(20000);   //1秒 = 1000毫秒 
		//std::this_thread::sleep_for(dura);   //休息一定的时长

		if (!msgRecvQueue.empty()) {
		    command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();
			return true;
		}
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
private:
	list<int> msgRecvQueue;   //容器(消息队列)，专门用于代表玩家给我们发送过来的命令
	mutex my_mutex1;//创建一个互斥量(一个互斥量就是一把锁)
	mutex my_mutex2;
};
int main() {
	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);  
	thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myOutMsgObj.join();
	myInMsgObj.join();


	//一：用unique_lock取代lock_guard
	//unique_lock是个类模板,工作中，一般lock_gurad(推荐使用);lock_guard取代了mutex的lock和unlock();
	//unique_lock比lock_guard灵活很多
	//二：unique_lock()的第二个参数
		//lock_guard可以带第二个参数：std::lock_guard<std::mutex> sbguard(my_mutex,adopt_lock);//adopt_lock标记作用
	//(2.1)std::adopt_lock:表示互斥量已经被lock了(必须要把互斥量提前lock了，否则会报异常)。
			//std::adopt_lock标记的效果就是 假设调用方线程已经拥有了互斥的所有权(已经lock()成功了);
			//通知lock_guard()不需要在构造函数中lock这个互斥量了。

	//unique_lock也可以带std::adopt_lock标记，含义相同。就是不希望unique_lock()的构造函数中lock这个mutex
	//(2.2)std::try_to_lock
	//会尝试用mutex的lock()去锁定这个mutex，但如果没有锁定成功，也会立即返回，不会阻塞再哪里
	//用try_to_lockd的前提是自己不能先去lock。

	//(2.3)std::defer_lock
	//使用前提：不能先lock(),否则会报异常。
	//defer_lock的意思就是，并没有给mutex加锁：初始化一个没有加锁的mutex。
	//借着defer_lock的话题，介绍一些unique_lock的重要成员函数

	//三：unique_lock的成员函数
	//(3.1)lock()
			///std::unique_lock<std::mutex> sbguard1(my_mutex1, std::defer_lock);  //没有加锁的my_mutex1
			///sbguard1.lock();   //不用自己unlock()
	//(3.2)unlock();
			//std::unique_lock<std::mutex> sbguard1(my_mutex1, std::defer_lock);  //没有加锁的my_mutex1
			//sbguard1.lock();   //不用自己unlock()
			//处理一些共享代码
			//sbguard1.unlock();
	//try_lock(),尝试给互斥量加锁，如果拿不到所，则返回false,如果拿到了锁，返回true,这个函数不阻塞
			//if (sbguard1.try_lock() == true)   //返回true表示拿到锁了
			//{
			//	msgRecvQueue.push_back(i);

			//}
	//(3.4)release(),返回它所管理的mutex对象指针，并释放所有权；也就是所，这个unique_lock和mutex不在有关系
				//严格区分unlock()和release()的区别，不要混淆
				//如果原来mutex对象处于加锁状态，则有责任接管过来并负责解锁。(release返回的是原始的mutex指针)
					//std::unique_lock<std::mutex> sbguard1(my_mutex1);
					//std::mutex* ptx = sbguard1.release();   //现在有责任自己解锁my_mutex1;
					// ptx->unlock();

	//为什么有时候需要unlock():因为你lock锁住的代码段越少，执行越快，整个程序运行效率越高
			//把锁住代码的多少，称为所的 "粒度" ，粒度一般用粗细来描述；
	//a)锁住的代码少，这个粒度叫细。执行效率高
	//b)锁住的代码多，粒度叫粗，执行效率低
	//学会尽量选择合适粒度的代码进行保护，粒度太细，可能漏掉共享数据的保护，粒度太粗，影响效率。

	//四：unique_lock所有权的传递
		//std::unique_lock<std::mutex> sbguard1(my_mutex1);   //所有权概念
			//sbguard1拥有my_mutex1的所有权
		//sbguard1可以把自己对mutex(my_mutex1)的所有权转移给其他的unique_lock对象；
		//所以，unique_lock对象这个mutex的所有权是属于 "可以转移" ,但是不能复制
			//std::unique_lock<std::mutex> sbguard1(my_mutex1)
			//std::unique_lock<std::mutex> sbguard2(sbguard1)   //复制所有权是非法的
			//std::unique_lock<std::mutex> sbguard2(std::move(sbguard1)) ;  //移动语义，
						//相当于sbguard2和my_mutex1绑定到一起了，现在sbguard1指向空，sbguard2指向了my_mutex1。

	//a)std::move
	//b)return unique_lock<std::mutex>
			//std::unique_lock<std::mutex> rtn_unique_lock()
			//{
			//	std::unique_lock<std::mutex> tmpguard(my_mutex2);
			//	return tmpguard; 
			//			
			//}
	return 0;
}