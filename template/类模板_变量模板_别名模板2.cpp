#include <iostream>


using namespace std;

namespace _nmsp1
{
	//泛化
	template<typename T,typename U>
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

	template<>  //全特化所有类型模板参数都用具体类型代码，所以<>里就为空
	struct TC<int, int>  //可以把他看成是新类型，可以添加新的成员函数
	{
		TC()
		{
			cout << "TC<int,int>特化版本的构造函数" << endl;
		}
		void functest1();   //把他拿到外面去写
		//{
		//	cout << "functest1特化版本" << endl;
		//}

		void functest2()   //与functest1()同理，也可以写到类外面
		{
			cout << "functest2特化版本" << endl;
		}
	};
	void TC<int, int>::functest1()
	{
		cout << "functest1特化版本" << endl;
	}

}
namespace _nmsp2 {
	template<typename T, typename U>
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
		static int m_stc;   //声明一个静态成员变量
	};

	template<>
	void TC<double, int>::functest1()   //functest1成员函数的全特化版本
	{
		cout << "普通成员函数TC<double,int>::functest1的全特化" << endl;
	}

	template<typename T,typename U>
	int TC<T, U>::m_stc = 50;    //定义静态成员变量

	template<>   //静态成员变量的全特化版本
	int TC<double, int>::m_stc = 100;
}

namespace _nmsp3 {

	template<typename T, typename U>
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

	template<typename U>  //模板参数数量上的偏特化
	struct TC<float, U>
	{
		TC()
		{
			cout << "TC<float,U>偏特化版本构造函数" << endl;
		}
		void functest1();
	};

	template<typename U>
	void TC<float, U>::functest1()
	{
		cout << "TC<float, U>::functest1偏特化版本" << endl;
	}



	template<typename T,typename U>
	struct TC<const T, U*>
	{
		TC()
		{
			cout << "TC<cosnt T,U*>偏特化版本构造函数" << endl;
		}
		void functest1();
	};

	template<typename T, typename U>
	void TC<const T, U*>::functest1()
	{
		cout << "TC<const U, U*>::functest1偏特化版本" << endl;
	}
}
int main()
{
	//二：类模板的各种特化
		//一般来讲，所写的类模板都是泛化版本
		//特化的类模板是通过泛化的类模板来生成的，所以：先要有泛化版本，才能有特化版本。
			//所谓特化版本，就是特殊对待的版本。
		//(2.1)类模板的全特化
			//全特化：就是把TC这个泛化版本中的所有模板参数都用具体的类型来代替构成一个特殊的版本(全特化版本)。
			//在理解上：泛化版本的类模板与全特化版本的类模板，只是名字上相同（都叫TC),在其他方面，可以把实例化后的他们理解成是两个完全不同的类。

	_nmsp1::TC<int, float> mytc;
	mytc.functest1();

	_nmsp1::TC<int, int> mytc1;
	mytc1.functest1();
	mytc1.functest2();
	cout << "----------------------" << endl;

		//(2.2)普通成员函数的全特化
	_nmsp2::TC<double, int> mytc2;
	mytc2.functest1();
	cout << "----------------------" << endl;

		//(2.3)静态成员变量的全特化
		//特别值得一提的是：如果进行了普通成员函数的全特化，或者是静态成员变量的全特化，
					//那么，就无法用这些全特化时指定的类型来对整个类模板进行全特化了。 
	cout << "mytc2.m_stc = " << mytc2.m_stc << endl;
	cout << "----------------------" << endl;

		//(2.4)类模板的偏特化（局部特化）
			//一方面：模板参数数量上的偏特化，另一方面是模板参数范围上的偏特化
			//2.4.1)模板参数数量上的偏特化
	_nmsp3::TC<float, int> mytc3;
	mytc3.functest1();
	cout << "----------------------" << endl;
			//2.4.2)模板参数范围上的偏特化
				//int -> const int   ,  T -> T*  ,  T -> T&   ,T -> T&&
	_nmsp3::TC<const float, int> mytc4;   //调用的是泛化版本
	mytc4.functest1();   
	
	_nmsp3::TC<const float, int*> mytc5;   //调用的是<const T,U*>的特化版本
	mytc5.functest1();
	return 0;
}