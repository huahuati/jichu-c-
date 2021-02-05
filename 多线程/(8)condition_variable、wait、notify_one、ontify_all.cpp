#include<iostream>
#include<thread>
#include<mutex>
#include<list>

using namespace std;
class A {
public:
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			std::unique_lock<std::mutex> sbguard1(my_mutex1);
			cout << "inMsgRechQueue()执行，插入一个元素" << i << endl;
			msgRecvQueue.push_back(i);
			//假如outMsgRecvQueue()正在处理一个失误，需要一段时间，而不是正卡在wait()等待，那么此时这个notify_one()这个可能就没有效果。
			my_cond.notify_one();   //我们尝试吧wait()的线程唤醒，执行这种，那么outMsgRecvQueue()里边的wait()就会被唤醒。
									//唤醒之后的事情后续研究；

			//my_cond.notify_one();  可以唤醒两个线程，但是实际上只能唤醒一个，因为不能同时又两个线程拿到锁。
		}	
		return;
	}

	void outMsgRecvQueue() {
		int command = 0;
		while (true) {
			std::unique_lock<std::mutex> sbguard1(my_mutex1);

			//wait用来等一个东西
			//如果第二个参数lambda表达式返回值是true,那么wait()直接返回。
			//如果第二个参数lambda表达式返回值是false，那么wait()将解锁互斥量，并堵塞到本行。
					//那么堵到什么时候为止呢?堵塞到其他某个线程调用notify_one()成员函数为止；
			//如果wait()没有第二个参数：my_cond.wait(sbguard1）,那么就跟第二个参数lambda表达式返回false效果一样。
					//那么wait()将解锁互斥量，并堵塞到本行。堵塞到其他某个线程调用notify_one()成员函数为止；
			//当其他线程用notify_one（）将本wait(原来是睡着/堵塞)的状态唤醒后，wait就开始执行了，wait执行了什么?
					//a)wait()不断的尝试重新获取互斥量锁，如果获取不到，那么流程就卡在wait()这里等待获取，
								//如果wait()获取到了锁（加了锁），那么就继续执行。
					//b)上锁(实际上获取到锁了就等于上了锁)
							//b.1)如果wait有第二个参数(lambda)，就判断这个lambda表达式，
										//如果lambda表达式为false,那wait又对互斥量解锁，然后又休眠，等待唤醒
							//b.2)如果lambda表达式为true，则wait返回，流程走下来(此时互斥锁被锁着)。
							//b.3)如果wait没有第二个参数，则wait返回，流程走下来。
			my_cond.wait(sbguard1, [this] {    //一个lambda就是一个课调用对象(函数)，也可以是任何一个可调用对象
				if (!msgRecvQueue.empty())
					return true;
				return false;
				});
			//流程只要能走到这里来，这个互斥量一定是锁着的。同时msgRecvQueue至少是有一条数据的
			command = msgRecvQueue.front();  //返回第一个元素，但不检查元素是否存在
			msgRecvQueue.pop_front();
			cout << "outMsgRecvQueue()执行，去除一个元素" << command <<"threadId = " <<std::this_thread::get_id() << endl;
			sbguard1.unlock();  //因为unique_lock的灵活性，我们可以随时的unlock解锁，以免锁住太长时间
			
		
			//执行一些具体动做
			///...
			//执行100毫秒
			//...
			//假如outMsgRecvQueue
		}
	}
private:
	list<int> msgRecvQueue;   //容器(消息队列)，专门用于代表玩家给我们发送过来的命令
	mutex my_mutex1;//创建一个互斥量(一个互斥量就是一把锁)
	std::condition_variable my_cond;   //生成一个条件变量对象
};
int main() {
	//一：条件变量std::condition_variable、wait()、notify_one()
	//线程A：等待一个条件满足
	//线程B：专门往消息队列中扔消息(数据)
	//condition_variable实际上是一个类，是一个和条件相关的一个类，说白了就是等待条件达成。
	//这个类是需要和互斥量来配合工作，用的时候我们要生成这个类的对象
	//notify_one()只能唤醒一个线程，

	//二：上述代码的深入思考


	//三：notify_all()
	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);  
	//thread myOutMsgObj2(&A::outMsgRecvQueue, &myobja);     //notify_all()
	thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myOutMsgObj.join();
	//myOutMsgObj2.join();//notify_all()
	myInMsgObj.join();
	return 0;
}