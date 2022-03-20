#include <iostream>


using namespace std;

namespace _nmsp1 {
	template<typename T = int,typename U = int>  //TC的泛化版本
	struct TC
	{
		TC()
		{
			cout << "TC泛化版本的构造函数" << endl;
		}
		void functest1()
		{
			cout << "functest1泛化版本" << endl;
	}
	};

	//TC的特化版本
	//template<typename T = char>   // 特化版本中不允许有缺省的模板参数
	template<typename T>
	struct TC<T,int>
	{};
}
namespace _nmsp2 {

	template<typename T, typename U = T*>
	struct TC {

	};
}

namespace _nmsp3 {
	//声明1,指定了V和W
	template<typename T,typename U,typename V = int,typename W = char>
	struct TC;

	//声明2，指定U
	template<typename T, typename U = char, typename V, typename W>
	struct TC;
	
	//定义泛化版本的TC
	template<typename T,typename U,typename V,typename W>
	struct TC
	{

	};

	typedef TC<int, float> IF_TC;  //这个是老式的版本
	
	using IF_TCU = TC<int, float>;
}

namespace _nmsp4 {
	template<typename T, typename U, size_t arrsize = 8>  //这里的size_t也可以替换为auto,进行自动推断
	struct TC
	{
		T m_arr[arrsize];   //arrsize 是在编译器期间，编译器就会传递进来arrsize的大小来确定数组m_arr的大小
		void functest2();
	};

	template<typename T, typename U, size_t arrsize>
	void TC<T,U,arrsize>::functest2()
	{
		cout << "functest2泛化版本" << endl;
	}
}

namespace _nmsp5 {

	template<const char *p>
	struct TC
	{
		TC()
		{
			printf("TC::TC执行了,p=%s\n", p);
		}
	};
	
	const char *g_s = "hello";   //全局指针
	const char shuzu[] = "hello";
}
int main()
{
	//三：缺省参数
		//(3.1)常规缺省参数
			//类型模板参数缺省值的规矩：如果某个模板参数有缺省值，那么从这个有缺省值的模板参数开始，后面所有的参数都得有缺省值。
			//类模板偏特化版本中的类型模板参数不可以有缺省值
	_nmsp1::TC<> mytc;			//使用了缺省模板参数，所以<>中啥也不同提供
	_nmsp1::TC<double> mytc1;		//<>中第一个类型不使用缺省值，第二个类型使用缺省参数
	cout << " ------------------- " << endl;
		
		//(3.2)后面的模板参数依赖前面的模板参数
	_nmsp2::TC<double> mytc2;
	_nmsp2::TC<double,int> mytc3;
	cout << " 1--------------------" << endl;
		//(3.3)在模板声明中指定缺省参数

	_nmsp3::TC<int> mytc4; //第二三四个模板参数采用缺省值，所以<>里只提供了一个类型模板实参。
	cout << "2--------------" << endl;

	//四：类型别名
		//考虑到类型名比较长，所以一般都用typedef ，或者using给这些类型名起一个额外的别名来简化书写。
	_nmsp3::IF_TC mytc5;    //IF_TC 等价于TC<int,folat> ，所以整个代码行等价于: _nmsp3::TC<int,float> mytc5;
	_nmsp3::IF_TCU mytc6;    
	cout << "3--------------" << endl;
	
	//五：非类型模板参数
		//数字是常量，类型一般也限制在整形、指针类型等。
			//(1)全局指针不能作为模板参数
			//(2)字符串长量也无法作为模板参数
			//为什么不允许浮点类型数字作为非类型模板参数呢？
					//因为其保存的不是一个精确的数字。
	_nmsp4::TC<double, double> mytc7;   //缺省的第三个模板参数是8
	for (size_t i = 0; i < 8; ++i)
	{
		mytc7.m_arr[i] = static_cast<double>(i);
	}
	cout << mytc7.m_arr[7] << endl;

	_nmsp4::TC<double, double, 18> mytc8;
	mytc8.m_arr[7] = 16.8;
	cout << mytc8.m_arr[7] << endl;
	cout << "4-------------" << endl;

	//全局指针的探讨
	//_nmsp5::TC<_nmsp5::g_s> mytc9;      //全局指针不能做参数
	_nmsp5::TC<_nmsp5::shuzu> mytc9;	   //给个数组就没问题了 
	cout << "5------------" << endl;

	//字符串常量的探讨
	//_nmsp5::TC<"xiba"> mytc10;     // 字符串常量无法作为模板参数
	return 0;
}