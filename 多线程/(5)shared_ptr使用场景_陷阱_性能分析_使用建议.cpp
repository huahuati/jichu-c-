#include<iostream>
#include<vector>
#include<string>

using namespace std;
shared_ptr<int> create0(int value)  
{
	return make_shared<int>(value);   //返回一个shared_ptr
}

void myfunc(int value) {
	shared_ptr<int> ptmp = create0(10);
	return;     //离开作用域后，ptmp会被自动释放，它所指向的内存也会被自动释放
}
shared_ptr<int> myfunc1(int value) {
	shared_ptr<int> ptmp = create0(10);
	return ptmp;  //系统是根据ptmp这个局部变量来产生一个临时的shared_ptr对象往回返
}

void proc(shared_ptr<int> ptr) {
	return;
}
class CT :public enable_shared_from_this<CT> 
{
public:
	shared_ptr<CT> getself() {
		//return shared_ptr<CT>(this);  //用裸指针初始化了多个shared_ptr的感觉
		return shared_from_this();   //这个就是enable_shared_from_this类中的方法，要通过此方法返回智能指针。
	}
};
class CB;   //声明下CB
class CA {
public:
	shared_ptr<CB> m_pbs;
	~CA() {
		int test;
		test = 1;
	}
};
class CB {
public:
	shared_ptr<CA> m_pas;
	//weak_ptr<CA> m_pas;   //把这里变成弱引用就不会出现问题
	~CB() {
		int test;
		test = 1;
	}
};
int main() {
	//一:std::shared_ptr使用场景
	myfunc(12);    //如果这块不用变量来接收myfunc1返回的结果，那么从myfunc返回的shared_ptr就会被销毁。
					//其所指向的对象也会被销毁
	auto p11 = myfunc1(12);   //用了一个变量来接myfunc1的返回值。
							  //那么myfunc返回的shared_ptr就不会被销毁，它所指向的对象也不会被销毁

	//二:std::shared_ptr使用陷阱分析
		//（2.1）慎用裸指针
		int* p = new int(100);  //裸指针
		//proc(p);   //语法错误，int *p 不能转换成shared_ptr<int>
		proc(shared_ptr<int>(p));  //参数是个临时的shared_ptr，用一个裸指针显示的构造；
		*p = 45; //潜在的不可预料的问题；因为p指向的内存已经被释放
//  --------------- 分界线 --------------
		shared_ptr<int> p2(p);
		proc(p2);
		*p2 = 45;  //把一个普通指针绑定到了一个shared_ptr上之后，内存管理的责任就交给这个shared_ptr了，
					//这个时候就不应该在用裸指针来访问shared_ptr所指向的内存了。

//  ---------------- 分界线 ------------
		shared_ptr<int> myp(new int(100));
		proc(myp);
		*myp = 45;

	//注意：！！！！！！不要用裸指针初始化多个shared_ptr
		int* p = new int(100);
		shared_ptr<int> p1(p);
		shared_ptr<int> p2(p);  //p1和p2无关联（p1和p2每个强引用计数都为1了），会导致p1和p2
								//所指向的内存被释放两次，所以会报异常；
		shared_ptr<int> p1(new int());
		shared_ptr<int> p2(p1);   //这种写法就是ok的，p1和p2指向同一个内存地址并且两者都是互通的。

		//(2.2)慎用get()返回的指针
		//get()功能：返回智能指针所指向对象所对应的的裸指针(有些函数接口能只能使用裸指针)
		//get返回的指针不能delete，否则会异常
		shared_ptr<int> myp(new int(100));
		int* p = myp.get();
		delete p;   //不可删除，会导致异常

		//不能将其他智能指针绑定到get()返回的指针上
		shared_ptr<int> myp(new int(100));
		int* p = myp.get();   //这个指针不能千万不能随意释放，否则myp就没办法正常管理该指针了
		//shared_ptr<int> myp2(p);
		{
			shared_ptr<int> myp2(p); //现在myp和myp2引用计数都为1，但一旦跳出这个程序块；
			shared_ptr<int> myp2(p);//这样写就没有问题
		}
		//离开上边这个myp2的范围，导致myp指向的内存被释放了；
		*myp = 65;  //该内存已经被释放，这样赋值会导致不可预料的后果。
		//结论：永远不要用get得到的指针来初始化另外一个智能指针或者给另外一个智能指针赋值。

		//(2.3)不要把类对象指针(this)作为shared_ptr返回，改用enable_shared_from_this
		shared_ptr<CT> pct1(new CT);
		//shared_ptr<CT> pct2 = pct1;  //这是两个强引用
		shared_ptr<CT> ptc2 = pct1->getself();   //问题出现(return shared_ptr<CT>(this) 调用这个)
		shared_ptr<CT> ptc2 = pct1->getself();   //问题解决(return shared_from_this() 调用这个)
		//用到c++标准库里边的类模板：enable_shared_from_this
		//在外面创建CT对象的智能指针以及通过CT对象返回的this智能指针都是安全的。
		//这个enable_shared_from_this中有一个弱指针weak_ptr,这个弱指针能够监视this，
		//在我们调用shared_from_this()这个方法时，这个方法内部实际上是调用了这个weak_ptr的lock()方法。
		//lock()方法会让shared_ptr指针计数加一，同时返回这个shared_ptr，这个就是工作原理。

		//(2.4)避免循环引用：能够避免内存泄漏
		shared_ptr<CA> pca(new CA);
		shared_ptr<CB> pcb(new CB);
		pca->m_pbs = pcb;  //等价于指向CB对象的有两个强引用
		pcb->m_pas = pca;  //等价于指向CA对象的有两个强引用

		//解决办法，一个类中用强引用，一个类中用弱引用

	
	//三：性能说明
	//(3.1)shared_ptr的尺寸是裸指针的两倍；weak_ptr尺寸裸指针的2倍；
		char* p;
		int ilenp = sizeof(p);   //4字节
		shared_ptr<string> p1;
		int ilensp = sizeof(p1);  //8字节，包含两个裸指针的

		//a)第一个裸指针指向的是这个智能指针所指向的对象
		//b)第二个裸指针指向一个很大的数据结构(控制块)，这个控制块里边有啥?
			//b.1)所指对象的强引用计数：shared_ptr
			//b.2)所指对象的弱引用计数：weak_ptr
			//b.3)其他数据，比如删除器指针，内存分配器；
		//这个控制块是由第一个指向某个对象的shared_ptr来创建
		
		//控制块创建的时机：
		//a)make_shared:分配并初始化一个对象，返回指向此对象shared_ptr,所以make_shared总是能够创建一个控制块；
		shared_ptr<int> p2 = make_shared<int>(100);

		//b)用裸指针创建一个shared_ptr对象时
		int* pi = new int();
		shared_ptr<int> pl(pi);
	//(3.2)移动语义
		shared_ptr<int> p1(new int(100));
		shared_ptr<int> p2(std::move(p1));   //移动语义，移动构造一个新的智能指针对象p2，
											//p1就不在指向该对象(变成空),引用计数依旧是1；
		shared_ptr<int>p3;
		p3 = std::move(p2);   //移动赋值，p2指向空，p3指向该对象，整个对象引用计数依旧为1；
		//移动肯定比开呗块；拷贝要增加引用计数，移动不需要。
		//移动构造函数块过赋值构造函数，移动赋值运算符块过拷贝赋值运算符。

	//四：补充说明和使用建议
		//a)分配器，结局内存分配问题；(没有讲解)
		//shared_ptr<int> p(new int, mydeleter(), mymallocator<int>());

		//b)谨慎使用，奇怪用法不要轻易尝试。

		//c)优先使用make_shared()，不能自己第一自己的删除器
		shared_ptr<string> ps1(new string("i love *"));//分配两次内存
		auto ps2 = make_shared<string>("I Love China!"); //分配1次内存
	return 0;
}