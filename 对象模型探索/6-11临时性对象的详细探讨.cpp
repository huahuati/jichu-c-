#include<iostream>
#include<string>
using namespace std;

namespace _nmspl
{
	//拷贝构造函数相关的临时性对象
	class A
	{
	public:
		A()
		{
			cout << "A::A()构造函数被执行" << endl;
		}
		A(const A& tmpobj)
		{
			cout << "A::A()拷贝构造函数被执行" << endl;

		}
		~A()
		{
			cout << "A::~A()析构函数被执行" << endl;

		}
	};

	A operator + (const A& obj1, const A& obj2)
	{
		A tmpobj;

		return tmpobj;  //编译器产生临时对象，把tmpobj对象的内容通过调用拷贝构造函数，把tempobj的内容拷贝给这个临时对象
								//然后返回的是这个临时对象
	}
	void func()
	{
		A myboj1;
		A myboj2;
		A reusltobj = myboj1 + myboj2;  //从operator +里返回的临时对象直接构造到了resultobj 里。

		return;
	}
}
namespace _nmsp2
{
	//二：拷贝赋值运算符相关的临时性对象
	class A
	{
	public:
		A()
		{
			cout << "A::A()构造函数被执行" << endl;
		}
		A(const A& tmpobj)
		{
			cout << "A::A()拷贝构造函数被执行" << endl;

		}
		A& operator = (const A& tmpaobj)
		{
			cout << "A::operaotr()拷贝赋值运算符被执行" << endl;
			return *this;
		}
		~A()
		{
			cout << "A::~A()析构函数被执行" << endl;

		}
	};
	A operator + (const A& obj1, const A& obj2)
	{
		A tmpobj;

		return tmpobj;  //编译器产生临时对象，把tmpobj对象的内容通过调用拷贝构造函数，把tempobj的内容拷贝给这个临时对象
								//然后返回的是这个临时对象
	}
		void func()
		{
			A myboj1;
			A myboj2;
			A reusltobj;
			reusltobj = myboj1 + myboj2;  //拷贝赋值运算符

			return;
		}
}

namespace _nmsp3
{
	//三：直接对象产生临时变量问题
	//(3.1)临时对象被摧毁
	//(3.2)临时对象因绑定而被保留
	class A
	{
	public:
		A()
		{
			cout << "A::A()构造函数被执行" << endl;
		}
		A(const A& tmpobj)
		{
			cout << "A::A()拷贝构造函数被执行" << endl;

		}
		A& operator = (const A& tmpaobj)
		{
			cout << "A::operaotr()拷贝赋值运算符被执行" << endl;
			return *this;
		}
		~A()
		{
			cout << "A::~A()析构函数被执行" << endl;

		}
		int m_i;
	};
	A operator + (const A& obj1, const A& obj2)
	{
		A tmpobj;
		tmpobj.m_i = obj1.m_i + obj2.m_i;
		return tmpobj;
	}
	void func()
	{
		A myobj1;
		myobj1.m_i = 1;
		A myobj2;
		myobj2.m_i = 2;


		//A tmpobjal = (myobj1 +myobj2);  编译器往必要的地方，帮组我们插入代码，来产生临时对象供编译器完成我们程序开发者代
					//要实现的意图
		printf("(myboj1 + myobj2).m_i = %d\n", (myobj1 + myobj2).m_i);
		//myobj1 + myobj2;   //产生了临时对象，然后该临时对象立即被析构了。

	
		cout << "分界线 ----临时对象被摧毁-----" << endl;
		const char* p = (string("123") + string("456")).c_str();//这一行有问题，因为临时对象过了这行就被摧毁
		string aaa = (string("123") + string("345"));
		const char * q = aaa.c_str();   //这个应该ok

		printf("p = %s\n", p);
		printf("q = %s\n", q);

		cout << "分界线 ----临时对象被保留-----" << endl;
		const string& aaa =string("123") + string("456");
		printf("aaa = %s\n", aaa.c_str());
		return;
	}
}
int main()
{
	//_nmspl::func();
	//_nmsp2::func();
	_nmsp3::func();
	return 0;
}