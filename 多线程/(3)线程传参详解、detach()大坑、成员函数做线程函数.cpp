#include<iostream>
#include<string>
#include<thread>
using namespace std;

class A {
public:
	mutable int m_i;
	//类型转换构造函数，可以把一个int转换成类a对象
	A(int a) :m_i(a) { 
		cout << "A::A(int a) 构造函数执行" << this << "threadid = " << std::this_thread::get_id << endl; 
	}
	A(const A &a):m_i(a.m_i)
	{ 
		cout << "A::A(const A &a) 拷贝构造函数执行" << this << "threadid = " << std::this_thread::get_id << endl; 
	}
	~A() { cout << "A::~A()析构函数执行" << this << "threadid = " << std::this_thread::get_id << endl; }

	void thread_work(int num) {
		cout <<"子线程thrad_work执行" <<this << "threadid = " << std::this_thread::get_id << endl;

	}
};

//void myprint(const int&i, char* pmybuf) {
//	cout << i << endl;   //detach的时候，i并不是mvar的引用，实际是值传递，那么我们认为，
//						//即便主线程detach了子线程，那么子线程中用i值任然是安全的。
//	cout << pmybuf << endl;  //detach子线程时，使用指针一定会有问题
//	return;
//}

//void myprint(const int& i, const string &pmybuf) {
//	cout << i << endl;
//	cout << pmybuf.c_str() << endl;  
//	return;
//}
//void myprint(const int& i, const A& pmybuf){
//	cout << &pmybuf << endl;   //这里打印的是pmybuf对象的地址
//	return ;
//
//}

//void myprint2(const A& pmybuf) {
//	pmybuf.m_i = 199;   //我们修改该值不会影响到main函数
//	cout << "子线程myprint2的参数地址是" << &pmybuf << "threadid = " << std::this_thread::get_id << endl;
//}
//
//void myprint2( A& pmybuf) {   //使用std::red不许用加const
//	pmybuf.m_i = 199;   //我们修改该值不会影响到main函数
//	cout << "子线程myprint2的参数地址是" << &pmybuf << "threadid = " << std::this_thread::get_id << endl;
//}

//void myprint2(unique_ptr<int> pzn) {   //创建只能指针线程时，使用unique_ptr,并使用了move函数时，则不能使用detach()
//
//}
int main() {
	//一：传递临时对象作为线程参数
	//(1.1)要避免的陷阱(解释1)
		//把子线程函数中的 char * 改成  const string &
	//(1.2)要避免的陷阱(解释2)
	//事实一：只要用临时构造的A类对象作为参数传递给线程，那么就一定能够在主线程执行完毕前，
	//把线程函数的第二个参数构建出来，从而确保即便detach()子线程也安全运行
	//(1.3)总结
	//a)若传递int这种简单类型参数，建议都是值传递，不要用引用。防止节外生枝。
	//b)如果传递类对象，避免隐式类型转换。全部都在创建线程这个一行构建出临时对象来，然后在函数参数里用引用来接，
			//否则系统还会多构造一次对象,否则会构造三次对象。
	//终极结论：
	//c)建议不使用detach()，只使用join()：这样就不存在局部变量实效导致线程对内存的非法引用问题。

	//二：临时对象作为线程参数继续讲
	//(2.1)线程ID概念：id是个数字，每个线程(不管是主线程还是子线程)实际上都对应着一个数字，而且每个线程对应的数字都不同。
				//也就是说，不同的线程，它的线程id（数字）必然是不同的。
	//线程id可以用c++标准库里的函数来获取。std::this_thread::get_id()来获取
	//(2.2)临时对象构造实际抓捕

	//三：传递类对象、只能指针作为线程参数
	//std::red 函数

	//四：用成员函数指针做线程函数   operator()
	//int mvar = 1;
	//int& mvary = mvar;
	//char mybuf[] = "this is a test!";
	////thread myobj(myprint, mvar, mybuf);  //mybuf是在什么时候转换成string的？
	//						//事实上存在，mybuf被回收了(main函数执行完了)，系统采用mybuf去转string的可能性。
	//thread myobj(myprint, mvar, string(mybuf)); // 这个直接将mybuf转换成string对象，这个一个可以保证在线程中用肯定有效的对象。
	////myobj.join();



	//int mvar = 1;
	//int mysecondpar = 12;
	////thread myobj(myprint, mvar, mysecondpar);   //没用临时对象，主线程中的局部对象可能被释放
	//thread myobj(myprint, mvar, A(mysecondpar));//希望mysecondpar转成A类型对象传递给myprint的第二个参数
	//							//用detach时，在创建线程的同时构造临时对象的方法传递参数是可行的。
	//
	////myobj.join();




	//cout << "主线程id是" << std::this_thread::get_id << endl;
	//int mvar = 1;
	//std::thread myobj(myprint2, A(mvar));
	////myobj.join();
	//myobj.detach();



	//A myobj(10);   //生成一个类对象
	//thread  mytobj(myprint2, myobj);  //myobj将类对象作为线程参数
	//mytobj.join();
	//mytobj.detach();
	//cout << "I LOVE CHINA" << endl;


	//A myobj(10);   //生成一个类对象
	//thread  mytobj(myprint2, std::ref(myobj));  //myobj将类对象作为线程参数
	/*unique_ptr<int> myp(new int(100));
	std::thread mytobj(myprint2, std::move(myp));*/

	A myobj(10);
	thread mytobj(&A::thread_work, myobj, 15);  //第一个参数是成员函数的地址，第二个参数是类对象
												//第三个是成员函数的参数
	mytobj.join();
	//mytobj.detach();
	cout << "I LOVE CHINA" << endl;
	return 0;
}