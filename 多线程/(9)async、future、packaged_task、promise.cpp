#include<iostream>
#include<thread>
#include<mutex>
#include<future>
using namespace std;
//class A {
//public:
//	int mythread(int mypar)   //线程入口函数
//	{
//		cout << mypar << endl;
//		cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
//		std::chrono::milliseconds dura(5000);//定义一个5秒时间
//		std::this_thread::sleep_for(dura); //休息了一定时长
//		cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
//		return 5;
//	}
//};
//int mythread()   //线程入口函数
//{
//	cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
//	std::chrono::milliseconds dura(5000);//定义一个5秒时间
//	std::this_thread::sleep_for(dura); //休息了一定时长
//	cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
//	return 5;
//}
//int mythread(int mypar) 
//{
//		cout << mypar << endl;
//		cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
//		std::chrono::milliseconds dura(5000);//定义一个5秒时间
//		std::this_thread::sleep_for(dura); //休息了一定时长
//		cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
//		return 5;
//}
void mythread(std::promise<int> &tmpp,int calc)     //注意第一个参数
{
	//做一系列复杂的操作
	calc++;
	calc *= 10;
	std::chrono::milliseconds dura(5000);//定义一个5秒时间
    std::this_thread::sleep_for(dura); //休息了一定时长

	//计算出结果
	int result = calc;    //保存结果
	tmpp.set_value(result);    //结果我保存到了tmpp这个对象中。
	return;
}
void mythread2(std::future<int>& tmpf) {

	auto result = tmpf.get();
	cout << "mythread2 result" << result << endl;
	return;
}
int main() {
	//一：std::async、std::future创建后台任务并返回值
	//希望线程返回一个结果；
	//std::async 是个函数模板，用来启动一个异步任务，启动起来一个异步任务之后，返回一个std::future对象,std::future是个类模板
	//什么叫“启动一个异步任务”，就是自动创建一个线程并开始执行对应的线程入口函数，返回一个std::future对象，
	//这个std::future对象里边就含有线程入口函数所返回的结果（线程返回的结果）；可以通过调用future对象的成员函数get()来获取结果。
	//"future"：将来的意思，也称呼std::future提供了一种访问异步操作结果的机制，就是说，这个结果没有办法马上拿到，
						//在线程执行完毕的时候，就能够拿到结果了，。
			//future的终极理解：这个future(对象)里会保存一个值，在将来的某个时刻能够拿到。

	//下列程序通过std::future对象的get()成员函数等待线程执行结束并返回结果
	//这个get()函数很牛，不拿到将来的返回值誓不罢休，不拿到值就等待，知道拿到值为止。
	//通过额外向std::async()传递一个参数，改参数，类型是std::launch类型(枚举类型),；来表达一些特殊的目的;
		//a)std::launch::deferred:表示线程入口函数调用被延迟到std::future的wait()或者get()函数调用时才执行。
		//如果wait或者get()没有被调用，那么线程会执行吗？
				//实际上线程根本就没有创建，更不会执行；
		//std::launch::deferred：延迟调用，并且没有创建新线程，是在主线程中调用的线程入口函数;

		//b)std::launch::async,在调用async函数的时候就开始创建线程。
					//async()函数，默认使用的就是std::launch::async
	//A a;
	//int temper = 12;

	//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
	////std::future<int> result = std::async(mythread);   //创建一个线程开始执行，绑定关系;并不卡到这里
	////std::future<int>result = std::async(std::launch::deferred,&A::mythread, &a, temper);  //成员函数的写法。第二个参数的成员引用，才能保证线程里用的是同一个对象
	//std::future<int>result = std::async(std::launch::async,&A::mythread, &a, temper);
	//cout << "contine....!" << endl;
	//int def;
	//def = 0;
	//cout << result.get() << endl;   //卡在这里等待mythread()执行完毕，拿到结果。
	////cout << result.get() << endl;   //get()只能调用一次

	////result.wait();  //等待线程返回，本身不返回结果。
	//cout << "I LOVE CHINA" << endl;


	//二：std::packaged_task:打包任务，把任务包装起来
	
	//是个类模板，它的模板参数是各种课调用对象；通过packaged_task来吧各种可调用对象包装起来，方便将来作为线程入口函数来调用。
	//packaged_task包装起来的课调用对象还可以直接调用，所以，从这个角度来讲，packaged_task对象，也是一个可调用对象
	
	//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
	//std::packaged_task<int(int)> mypt(mythread);  //把函数mythread通过packaged_task包装起来
	//						//packaged_task<int(int)>  第一个int是函数返回类型，第二个是参数类型
	//std::thread t1(std::ref(mypt), 1);   //线程直接开始执行，第二个参数作为线程入口函数的参数。
	//t1.join();     //等待线程执行完毕。
	//std::future<int> result = mypt.get_future();
	//				//std::future对象里包含有线程入口函数的返回结果，这里result保存mythread返回的结果。
	//cout << result.get() << endl;
	//cout << "I LOVE CHINA!" << endl;


	//另一种写法
		//std::packaged_task<int(int)> mypt([](int mypar){
		//cout << mypar << endl;
		//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		//std::chrono::milliseconds dura(5000);//定义一个5秒时间
		//std::this_thread::sleep_for(dura); //休息了一定时长
		//cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		//return 5;
		//
		//});
		//std::thread t1(std::ref(mypt), 1);   //线程直接开始执行，第二个参数作为线程入口函数的参数。
		//t1.join();     //等待线程执行完毕。
		//std::future<int> result = mypt.get_future();
		////std::future对象里包含有线程入口函数的返回结果，这里result保存mythread返回的结果。
		//cout << result.get() << endl;

	
	//另另一种写法，因为packaged_task对象是一个可调用对象,没有创建新的线程
		//std::packaged_task<int(int)> mypt([](int mypar){
		//cout << mypar << endl;
		//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		//std::chrono::milliseconds dura(5000);//定义一个5秒时间
		//std::this_thread::sleep_for(dura); //休息了一定时长
		//cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		//return 5;
		//});

		//mypt(105);   //直接调用，相当于函数调用,没有创建新的线程
		//std::future<int> result = mypt.get_future();
		//cout << result.get() << endl;

	//另另另一种写法，因为packaged_task对象是一个可调用对象，没有创建新的线程
		//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
		//std::packaged_task<int(int)> mypt([](int mypar){
		//cout << mypar << endl;
		//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		//std::chrono::milliseconds dura(5000);//定义一个5秒时间
		//std::this_thread::sleep_for(dura); //休息了一定时长
		//cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//打印新线程id
		//return 5;
		//});

		//vector <std::packaged_task<int(int)>> mytasks;

		//mytasks.push_back(std::move(mypt));;  //容器，这里用了移动语义，入进去之后mypt就为空。
		//
		//std::packaged_task<int(int) > mypt2;    //用来接收mypt
		//auto iter = mytasks.begin();
		//mypt2 = std::move(*iter);   //移动语义
		//mytasks.erase(iter);    //删除第一个元素，迭代器已经失效了，所以后续代码不可以再使用iter；
		//mypt2(123);
		//std::future<int> result = mypt2.get_future();
		//cout << result.get() << endl;


	//三：std::promise,类模板
	//能够在某个线程中给它赋值，然后可以在其他线程中，把这个值取出来用；
	//总结：通过promise保存一个值，在将来某个时刻我们通过把一个future绑定到这个promise上来得到这个绑定的值。
	std::promise<int> myprom;   //声明一个std::promise对象myporm，保存的值类型为int;
	std::thread t1(mythread, std::ref(myprom), 180);
	t1.join();
	std::future<int> ful = myprom.get_future();   //promise和future绑定，用于获取线程返回值。
	//auto result = ful.get();    //get()只能调用一次，不能调用多次
	//cout << "result = " << result << endl;

	std::thread t2(mythread2, std::ref(ful));
	t2.join();   //等mythread2线程执行完毕

	cout << "I LOVE CHINA" << endl;
	return 0;


	//四：小结：到底怎么用，什么时候用；
	//学习这些东西的目的，并不是要把他们都用在咋们自己的实际开发中。
	//相反，如果能够用最少的东西能够写出一个稳定、高效的多线程程序、那就更厉害
	//阅读高手写的代码，从而快速实现自己代码的积累，技术会有大幅度提升。
	//学习这些东西的理由的解释：为将来能够读懂高手甚至大师写的代码而铺路。
}