#include<iostream>
#include<string>

using namespace std;


namespace _nmsp1
{
	int mf(int tmp1, int tmp2)
	{

		return 1;
	}
	int mf2(int tmp1, int tmp2)
	{

		return 10;
	}
	typedef int(*FunType)(int, int);   //函数指针类型定义
	template	<typename T, typename F = FunType>
	void testfunc(T i, T j, F funcpoint = mf)
	{
		cout << funcpoint(i, j) << endl;
	}

	template<typename T = int, typename U>
	void testfunc(U m)
	{
		T tmpvalue = m;
		cout << tmpvalue << endl;
	}
}

namespace _nmsp2
{
	//template<typename T, typename U,auto val = 100>
	template<typename T, typename U, int val = 100>  //同上，可是在visual studio 2019中出现错误！！！
	auto Add(T tv1, U tv2)
	{
		return tv1 + tv2 + val;
	}

	template<double* p>
	void mft()
	{
		cout << "mft()执行了" << endl;
	}
	double g_d = 1.3;   //全局量

	//-------------------
	//template<typename T,int value>
	template<typename, int>     //同上，没有用到的话，就可以省略
	auto Add2()
	{
		return 100;
	}

	template<class  T, typename int value>   //（typename int value)typename 在这里是画蛇添足 ，不能用class来代替
	auto Add3()
	{
		return 100;
	}
}
int main(void)
{

	//六：缺省参数
	_nmsp1::testfunc(15, 16);
	_nmsp1::testfunc(15, 16,_nmsp1::mf2);

	_nmsp1::testfunc(12);

	cout << "分界线-----" << endl;
	//七：非类型模板参数
		//7.1)基本概念, 六中涉及到的模板参数都是 “类型模板参数”需用用typename(class)来修饰
			//模板参数还可以是“非类型模板参数（普通的参数)”
			//c++17开始，支持非类型模板参数为auto类型。
			//指定非类型模板参数的值时，一般给的是常量。因为编译器在编译的时候就要能够确定非类型模板参数的值
			//并不是任何类型的参数都可以作为非类型模板参数（int 类型可以 ，但double float或者类类型string等等可能就不可以，不过 double * 这种指针类型就可以）
			//一般允许做非类型模板参数的类型如下：可能不断增加
				//a)整形或者枚举类型；
				//b)指针类型：
				//c)左值 引用类型；
				//d)auto 或者decltype(auto)
		//7.2)比较奇怪的语法
			//a)不管类型还是非类型模板参数，如果代码中没有用到，则参数名可以省略
			//b)类型前面可以增加一个typename修饰以明确表示一个类型，一般跟模板有关的类型名是不需要修饰的
	cout << _nmsp2::Add<float,float>(23.3f, 11.8f) << endl;
	cout << _nmsp2::Add<float,float,800>(23.3f, 11.8f) << endl;

	_nmsp2::mft<&_nmsp2::g_d>();

	cout << _nmsp2::Add2<int, 45>() << endl;

	cout << _nmsp2::Add3<int, 45>() << endl;
	return 0;
}