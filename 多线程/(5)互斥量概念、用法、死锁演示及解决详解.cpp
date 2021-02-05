#include<iostream>
#include<thread>
#include<list>
#include<vector>
#include<mutex>
using namespace std;
class A {
public:
	//把收到的消息(玩家命令)入到一个队列的线程里
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRechQueue()执行，插入一个元素" << i << endl;
			
			//my_mutex2.lock();  //死锁解决方案，两个锁锁的顺序一样
			//my_mutex1.lock();  //实际工作中不一定挨着，可能需要保护不同的数据块
			//my_mutex2.lock();
			//std::lock_guard<std::mutex> sbguard1(my_mutex1);
			//std::lock_guard<std::mutex> sbguard2(my_mutex2);   
			std::lock(my_mutex1, my_mutex2);   //相当于每个互斥量都调用了.lock()
			std::lock_guard<std::mutex> sbguard1(my_mutex1,std::adopt_lock);
			std::lock_guard<std::mutex> sbguard2(my_mutex2, std::adopt_lock);
			msgRecvQueue.push_back(i);  //假设这个数字i就是收到的玩家命令，直接弄到消息队列里面
			//my_mutex2.unlock();
			//my_mutex1.unlock();
		}
	}
	bool outMsgLULProc(int& command) 
	{	
		//std::lock_guard<std::mutex> sbguard(my_mutex1);   //sbguard是对象名
															//lock_guard构造函数里执行了mutex::lock();
															//lock_guard析构函数里执行了mutex::unlock();
		//my_mutex2.lock();
		//my_mutex1.lock();
		std::lock(my_mutex1, my_mutex2);
		if (!msgRecvQueue.empty()) {
			//消息队列不为空
			int command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();   //移除第一个元素，但不返回
			my_mutex1.unlock();
			my_mutex2.unlock();

			return true;
		}
		my_mutex1.unlock();
		my_mutex2.unlock();

		return false;
	}

	//把数据从消息队列中取出的线程；
	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 100000; ++i) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				command += 1;
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
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);  //第二个参数是引用，才能保证线程里用的是同一个对象。
	thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myOutMsgObj.join();
	myInMsgObj.join();

	//保护共享数据，操作时，某个用代码把共享数据锁住、操作数据，解锁。
		//其他线程想操作共享数据线程必须等待解锁，锁定住，操作数据，解锁。
	//一：互斥量（mutex）的基本概念
	//互斥量是个类对象。理解成一把锁，多个线程尝试用lock()成员函数来加锁，只有一个线程能够锁定成功。
			//成功的标志是lock()函数返回，如果没锁成功，那么流程会卡在lock()这个不断的尝试去锁。
	//互斥量使用要小心，保护数据不多也不少，少了，没达到保护效果。多了，影响效率

	//二：互斥量的用法
	//(2.1)lock(),unlock()
	//步骤：先lock(),操作共享数据，然后unlock()
	//lock()和unlock()要成对使用,有lock()必然要有unlock,没吊用一次lock(),必然应该调用一次unlock();
	//不应该也不允许调用1次lock()却调用了2次unlock，也不允许调用2次lock却只调用1次unlock(),数量上必须对称。

	//有lock()，忘记unlock()的问题很难排查
	//为了防止忘记unlock(),引入了一个叫std::lock_guard的类模板:忘记unlock不要紧，lock_guard会自动unlock；
	//(2.2)std::lock_guard模板 ：可以直接取代lock()和unlock(),用了lock_guard就不能再使用lock()和unlock().

	//三:死锁
	//比如我有两把锁（死锁这个问题 是至少由两个锁头，也就是两个互斥量才能产生）;金锁（JinLock）,银锁(YinLock)
	//两个线程A，B
	//（1）线程A执行的时候，这个线程先锁金锁，把金锁lock()成功，然后它正要去去lock()银锁；
	//出现上下文切换
	//（2）线程B执行了，这个线程先锁银锁，把银锁lock()成功，线程B正要去lock()金锁;
	//此时此刻，死锁就产生了；
	//（3）线程A因为拿不到银锁，流程走不下去（所有后边代码有解锁金锁头的但是流程走不下去，所以金锁头解不开）
	//（4）线程A因为拿不到金锁，流程走不下去（所有后边代码有解锁银锁头的但是流程走不下去，所以银锁头解不开）

	//(3.1)死锁演示
		//my_mutex1.lock();
		//my_mutex2.lock();

		//my_mutex2.lock();
		//my_mutex1.lock();
	//(3.2)死锁解决方案
		//只要保证这两个上锁的顺序一致就不会产生死锁
		//my_mutex1.lock();
		//my_mutex2.lock();

		//my_mutex1.lock();
		//my_mutex2.lock();

	//(3.3)std::lock()函数模板::用来处理多个互斥量的时候才出场
		//能力：一次锁住两个或者两个以上的互斥量(至少两个，多了不限，1个不行)
		//他不存在在多个线程中 因为所的顺序问题导致死锁的风险问题；
	//std::lock()：如果互斥两种有一个没锁住，它就在哪里等待，等所有互斥量都锁住，它才能往下走。
	//要么两个互斥量都锁住，要么两个互斥量都没锁住。如果只锁了一个，另外一个没锁成功，则它立即把锁定的给解锁
				//std::lock(my_mutex1, my_mutex2);
				//my_mutex1.unlock();
				//my_mutex2.unlock();
	//(3.4)std::lock_guard的std::adopt_lock参数
	//std::adopt_lock：表示互斥量已经lock(),不需要在std::lock_guard<sdt::mutex>里面对对象再次进行lock()了。
			//std::lock(my_mutex1, my_mutex2);   //相当于每个互斥量都调用了.lock()
			//std::lock_guard<std::mutex> sbguard1(my_mutex1, std::adopt_lock);
			//std::lock_guard<std::mutex> sbguard2(my_mutex2, std::adopt_lock);

	//终结：std::lock()：一次锁定多个互斥量；谨慎使用（建议一个一个锁)
	return 0;
}