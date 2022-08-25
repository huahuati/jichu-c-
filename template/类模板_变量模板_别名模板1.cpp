#include<iostream>
#include<string>
using namespace std;

namespace _nmspl {

	//类模板定义
	template<typename T>   //T 是类型模板参数,表示myvector这个容器所保存的元素类型
	class myvector        //myvector可以称为类名或者类模板，myvector<T>可以称为类型名（myvector后面带来尖括号，表示的就是一个具体类型了）
	{
	public:
		typedef T* myiterator;   //迭代器
	public:
		myvector();   //构造函数
		myvector& operator=(const myvector&);  //赋值运算符重载
		//myvector<int>& operator=(const myvector&);  //赋值运算符重载  ,同上
		myvector( T tmpt)
		{
			
		}
	public:
		void myfunc()
		{
			cout << "myfunc()被调用" << endl;
		}


		static void mystaticfunc()
		{
			cout << "mystaticfunc()被调用" << endl;
		}
	public:
		myiterator mybegin(); //迭代器起始位置
		myiterator myend();   //迭代器结束位置
	};
	

	//类模板实现
	template<typename T>
	myvector<T>::myvector()   //类外构造函数的实现
	{
		
	}
}

namespace _nmsp2
{

	template<typename T>
	struct A
	{
		A(T val1, T val2)
		{
			cout << "A::A(T val1, T val2)执行了!" << endl;
		}

		A(T val1)
		{
			cout << "A::A(T val1)执行了!" << endl;
		}
	};
	
	template<typename T>  //自定义推断指南
	A(T)->A<T>;

}

namespace _nmsp3 {
	template<typename T>
	struct B
	{
		T m_b;
	};

	template<typename T>   //自定义推断指南
	B(T)->B<T>;
}
namespace _nmsp4 {
	template<typename T>
	struct B
	{
		T m_b;
		T m_b1;
	};

	template<typename T>   //自定义推断指南
	B(T,T)->B<T>;
}
int main()
{
	//一：类型模板的基本规范和模板参数的推断
		//类模板：是产生类的模具，通过给定的模板参数，生成具体的类，也就是实例化一个特定的类
		//vecotr<int>,引入类模板的目的，减少代码冗余
		//(1.1)基本范例
			//myvector可以称为类名或者类模板，myvector<T>可以称为类型名（myvector后面带来尖括号，表示的就是一个具体类型了）
			//类模板中，只有被调用的成员函数，编译器才会产生出这些函数的实例化代码(静态函数也是)

	_nmspl::myvector<int> tmpvec;        //T被替换成int
	tmpvec.myfunc();					  //调用普通成员函数
	_nmspl::myvector<string>::mystaticfunc();

		//(1.2) 模板参数的推断
			//c++17中，类模板的类型模板参数也能推断了。
			
	_nmspl::myvector tmpvec2(12);    //无需指定模板参数了
	//_nmspl::myvector<int> tmpvec2(12);   //同上
	tmpvec2.myfunc();

		//(1.3)推断指南（deduction guide)概要了解
			//c++17新概念：主要用来在推断类模板参数时提供推断指引
			//(1.3.1)隐式的推断指南
					//针对类模板A的每个构造函数，都有一个隐式的模板参数推断机制存在，这个机制，被称为隐式的推断指南
					//typename<typename T>
					// A(T,T)->A<T>;
					// 表达出现 -> 左侧部分内容或者形式时，请推断成 -> 右侧的类型，右侧类型也被称为“指南类型”
					// -> 左侧部分：该推断指南所对应的构造函数(注意构造函数，只有有构造函数才可以)的函数声明，多个参数之间用“，”分隔
					// -> 右侧部分： 类模板名，接着一个尖括号，尖括号中是模板参数名。
					// 整个推断指南的含义：当用调用带两个参数的构造函数通过类模板A创建相关对象时，请用所提供的构造函数的实参来推断类模板A的模板参数类型
				//一句话：推断指南的存在意义就是让编译器 能够把模板参数的类型推断出来
				//假设
					//template<typename T>
					//A(T,T) -> A<double>;
					//那么 A obj1(15,16);  代码行   相当于A<int> aobj1(15,16);
			
			//(1.3.2) 自定义的推断指南
				//_nmsp3::B bobj3{15};   不报错的原因
					//a)类B是聚合类，是可以通过{}初始化的
					//b)B bobj3{15}  这种形式正好就相当于调用了类模板B的带一个参数{15}的构造函数，尽管类模板B中不存在构造函数
					//c)因为 	template<typename T> B(T)->B<T>;推断指南的存在，当调用了用类模板B带一个参数的构造函数时，推断出来的类型为B<T>
								//所以，最总推断出来的类型为B<int>类型。
	//(1.3.1)		
	_nmsp2::A aobj1(5, 1);  //自动实例化出 A<int>

	_nmsp2::A aobj2(12.8);

	//_nmsp2::A* aobj3 = NULL;   //这样不能推断

	//(1.3.2)
	_nmsp3::B<int> bobj1;			 //需要明确指定模板参数类型
	_nmsp3::B<int> bobj2{ 15 };	 //可以用初始化列表的方式来定义对象bobj2,成员变量m_b = 15;

	_nmsp3::B bobj3{15};     //因为自定义了推断指南，所以不用明确指定模板参数类型
	
	_nmsp4::B bobj4{ 15,16 };
	return 0;
}
