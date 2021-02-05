#include<iostream>
#include<string>
#include<thread>
#include<list>
#include<mutex>
using namespace std;
std::mutex resource_mutex;
std::once_flag g_flag;  //这是个系统定义的标记
class MyCAS  //这是一个单例类
{
	static void CreateInstace()  //只被调用1次的函数
	{
		m_instance = new MyCAS();
		static CGarhuishou c1;
	}
private:
	MyCAS() {}  //私有化的构造函数

private:
	static MyCAS* m_instance;  //静态成员变量
public :
	static MyCAS* GetInstance() {
		//提高效率。
		//a)如果if (m_instance != NULL),条件成立，则肯定表示m_instance已经被new过了
		//b)如果if(m_instance == NULL),不代表m_instance 一定没被new过；

		if (m_instance == NULL) {//双重锁定(双重检查)

			std::unique_lock<std::mutex> mymutex(resource_mutex);   //自动加锁
			if (m_instance == NULL)
			{
				m_instance = new MyCAS();
				static CGarhuishou cl;  //用来delete m_instance
			}
		}
		//std::call_once(g_flag, CreateInstace);    //两个线程同时执行到这里，其中一个线程要等另外一个线程CreateInstace的执行完毕。
		return m_instance;
	}

	class  CGarhuishou//类中套类，用来释放对象
	{
	public:
		~CGarhuishou()  //类的析构函数中
		{
			if (MyCAS::m_instance) {
				delete MyCAS::m_instance;
				MyCAS::m_instance = NULL;
			}
		}
	};

	void func() {
		cout << "测试" << endl;
	}
};
MyCAS* MyCAS::m_instance = NULL;
//线程入口函数
void mythread() {
	cout << "我的线程代码开始执行了" << endl;
	MyCAS *p_a = MyCAS::GetInstance();    //这里可能就会有问题。
	cout << "我的线程执行完毕了" << endl;
	return;
}
int main() {
	//一：设计模式大概谈
	//"设计模式":代码的一些写法(这些写法分常规写法不怎么一样):程序灵活，维护起来可能方便，但是别人接管，阅读代码都会很痛苦。
	//用"设计模式"  理念写出来的代码很晦涩。《head first》
	//应付特别大的项目的时候 把项目的开发经验、模块划分经验，总结整理成设计模式(现有开发需求，后有理论和总结)
	//中国式设计模式，不太一样，拿着一个程序(项目)往设计模式上套，一个小小的项目，非得使用设计模式，本末倒置。
	//设计模式肯定有独特的优点，要活学活用，不要深陷其中，生搬硬套。

	//二：单例设计模式
	//单例设计模式使用频率比较高、
	//单例：整个项目中，有某个或者某些特殊的类，属于该类的对象，只能创建1个，多了创建不了。
	//单例类(看代码)
	MyCAS* p_a = MyCAS::GetInstance();  //创建一个对象，返回该类（MyCAS）对象的指针
	//MyCAS* p_b = MyCAS::GetInstance();  //p_b与p_a指向的对象相同
	p_a->func();
	MyCAS::GetInstance()->func(); //改装载的数据装载

	//三：单例设计模式共享数据问题分析、解决
	//面临的问题：需要在我们自己创建的线程（而不是主线程）中来创建MyCAS这个单例类的对象，这种线程可能不止一个（最少两个）。
	//可能会面临GetInstance()这中成员函数要互斥。
	
	//虽然这两个线程都是同一个入口函数，但千万记住，这是两个线程，所以这里会有两个流程（两条通路）同时开始执行mythread这个函数。

	std::thread mytobj1(mythread);
	std::thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();

	//四：std::call_one();  c++ 11 引入的函数,该函数的第二个参数是一个函数名a()；
	//call_once功能是能够保证函数a()只能被调用一次。
	//call_once具备互斥量这种能力，而且效率上，比互斥量消耗的资源更少；；
	//call_once()需要与一个标记结合使用，这个标记 std::once_flag;   once_flag是一个结构
	//call_once()就是通过这个标记来决定对应的函数a()是否执行，调用call_once()成功后，call_one（）就把这个标记设置为已调用的状态。
	//后次再次调用call_one(),只要once_flag被设置为了"已调用"状态，那么对应的函数a()就不会再次执行了。
	
	//总结：建议在主线程中就把MyCAS::GetInstance()对象的初始化工作全部做好，然后子线程只是负责使用。
	return 0;
}