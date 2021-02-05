#include<iostream>
#include<thread>
#include<mutex>
#include<future>
using namespace std;
int mythread()   //线程入口函数
{
	cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
	std::chrono::milliseconds dura(5000);//定义一个5秒时间
	std::this_thread::sleep_for(dura); //休息了一定时长
	cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
	return 5;
} 
int mythread1(int mypar) 
{
		//cout << mypar << endl;
		cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		std::chrono::milliseconds dura(5000);//定义一个5秒时间
		std::this_thread::sleep_for(dura); //休息了一定时长
		cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		return 5;
}
//void mythread2(std::future<int>& tmpf) {
void mythread2(std::shared_future<int>& tmpf) {

	auto result = tmpf.get();
	//auto result = tmpf.get(); 为什么第二次get future会的得到异常；主要是因为get函数的设计，是一个移动语义
	cout << "mythread2 result = " << result << endl;
	return;
}

std::atomic<int> g_mycout = 0;   //我们封装了一个类型为int的对象（值）；我们可以向操作一个int类型变量一样来操作g_mycout
std::mutex g_my_mytex;   //引入互斥量
void mythread3() {   //线程入口函数
	for (int i = 0; i < 100000; i++) {
		//g_my_mytex.lock();  //用互斥量的方式时间比较慢
		//g_mycout++;
		//g_my_mytex.unlock();
		g_mycout++;  //对应的操作时原子操作（不会被打断）
	}
	return;
}

std::atomic<bool> g_ifend = false;   //线程退出标记，这里是原子操作，防止读和写乱套。
void mythread4() {

	std::chrono::milliseconds dura(1000);  //1 秒钟
	while (g_ifend == false) {
		//系统没要求退出，所以本线程可以干自己想干的事情
		cout << "thread id = " << std::this_thread::get_id() << "运行中..." << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "thread id = " << std::this_thread::get_id() << "运行结束..." << endl;
	return;
}
int main() {
	//一:std::future的其他成员函数

	//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;
	//std::future<int> result = std::async(mythread);
	////std::future<int> result = std::async(std::launch::deferred,mythread);

	//cout << "continue....!" << endl;
	////cout << result.get() << endl;    //卡在这里等待线程执行完
	//
	////枚举类型
	//std::future_status status = result.wait_for(std::chrono::seconds(5));    //等待一秒
	//if (status == std::future_status::timeout) {  // 超时：等待子线程一秒钟，希望其返回，如果没有返回，那么status= timeout;

	//	//超时：表示线程还没有执行完
	//	cout << "超时了，线程还没有执行完" << endl;
	//}
	//else if (status == std::future_status::ready) {

	//	//表示线程成功返回
	//	cout << "线程成功执行完毕，返回" << endl;
	//	cout << result.get() << endl;
	//}
	//else if (status == std::future_status::deferred) {
	//	//延迟async 是std::async(std::launch::deferred,mythread);则本条件成立
	//	cout << "线程被延迟执行" << endl;
	//	cout << result.get() << endl;    //在主线程中被执行
	//}


	//二:std::shared_future  也是个类模板。shared_future，get()函数是复制数据
			//std::future的其他成员函数，get()函数式转移数据
	//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
	//std::packaged_task<int(int)> mypt(mythread1);  //把函数mythread通过packaged_task包装起来
	//						//packaged_task<int(int)>  第一个int是函数返回类型，第二个是参数类型
	//std::thread t1(std::ref(mypt), 1);   //线程直接开始执行，第二个参数作为线程入口函数的参数。
	//t1.join();     //等待线程执行完毕。

	////std::future<int> result = mypt.get_future();

	////bool ifcanget = result.valid();   //能够判断result里面是否有值
	//////std::shared_future<int> result_s(std::move(result));   //必须用移动语义,
	////std::shared_future<int> result_s(result.share()); //同上,执行完毕后result_s里有值，而result里空了
	////ifcanget = result.valid();    //值已经为空
	//std::shared_future<int>result_s(mypt.get_future());   //通过get_future返回值直接构造了一个shared_future对象。
	//auto mythread_result = result_s.get();

	////std::thread t2(mythread2, std::ref(result_s));
	//std::thread t2(mythread2, std::ref(result_s));
	//t2.join();

	//三：原子操作std::atomic
	//(3.1)原子操作概念引出范例
	//互斥量：多线程编程中保护共享数据： 锁，操作共享数据，开锁
	//有两个线程，多一个变量进行操作，一个线程读变量值，另一个线程往这个变量中写值。
	//读线程A
	//int tmpvalue = atomvalue;  //这个atomvalue 代表的是多个线程之间要共享的变量
	//写线程B
	//atomvalue = 6;   //改成汇编代码，就有多条汇编代码执行。

	//把原子操作理解成：不需要用到互斥量加锁（无锁）技术的多线程并发编程方式
	//原子操作：是在多线程中不会被打断的程序执行片段。；原子操作，比互斥量效率上更胜一筹。
	//互斥量的加锁是针对一个代码段（几行代码），而原子操作针对的一般是一个变量，而不是一个代码段

	//原子操作：一般指不可分割的操作，也就是说这种操作状态要么是完成的，要么是没完成的，不可能出现半完成状态
	//std::atomic来代表原子操作，std::atomic是个类模板。其实std::atomic这个东西是用来封装某个类型的值

	//(3.2)基本的std::atomic用法范例
	/*thread mytobj1(mythread3);
	thread mytobj2(mythread3);
	mytobj1.join();
	mytobj2.join();
	cout << "两个线程执行完毕，最终的g_mycout的结果是：" << g_mycout << endl;*/
	thread mytobj1(mythread4);
	thread mytobj2(mythread4);
	std::chrono::milliseconds dura(5000);  //5秒钟
	std::this_thread::sleep_for(dura);
	g_ifend = true;  //对原子对象的写操作，然线程自行运行结束
	mytobj1.join();
	mytobj2.join();
	cout << "程序执行完毕，退出" << endl;
	cout << "I LOVE CHINA" << endl;
	return 0;

	//(3.3)心得：一般用于统计或者计数（累计发出去了多少个数据包，累计接受到了多少个数据包）
}