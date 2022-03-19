#include <iostream>
using namespace std;
namespace _nmsp1 {

	//int Sub(int tv1, int tv2)
	//{
	//	return tv1 - tv2;
	//}

	//float Sub(float tv1, float tv2)
	//{
	//	return tv1 - tv2;
	//}

	//利用函数模板就可以写一个函数支持以上两种操作
	//template<typename T>   //T:称呼为类型模板参数，代表的是一个类型
	template<class T>      //该语句同上，class 可以取代typename，但是这里的class并没有 “类的函数” T的名字可以任意取
	T Sub(T tv1, T tv2)
	{
		return tv1 - tv2;
	}

	//---------------------------
	//template<typename T,typename U,typename V>
	template<typename V,typename U,typename T>
	V add(T tv1, U tv2)
	{
		return tv1 + tv2;
	}

	template<typename T, typename U>
	auto ADD(T tv1, U tv2)		//auto 用于表达推导返回值类型的含义
	{
		return tv1 + tv2;
	}

	template<typename T, typename U>
	auto ADD1(T tv1, U tv2) -> decltype(tv1 + tv2)   //返回类型后置语法，这个auto只是返回类型后置语法的组成部分，并没有类型推导的含义
	{
		return tv1 + tv2;
	}


	template<typename T>
	T MyDouble(T tmpvalue)
	{
		return tmpvalue * 2;
	}

	double MyDouble(double tmpvalue)
	{
		return tmpvalue * 2;
	}
}
int main(void){

	//一：基本范例
	//a)模板的定义是以template关键字开头
	//b)类型模板参数T前面用typename来修饰，所以，遇到typename就该知道其后面跟的是一个类型
			//typename可以被class取代，但此处的class没有 "类的含义"
	//c)类型模板参数T（代表是一个类型）以前前面的修饰符typename/class 都用<>括起来
	//d)T这个名字可以换成任意其他标识符，对程序没有影响。用T只是一种编程习惯。
	int subv = _nmsp1::Sub(3, 5);
	cout << "subv = " << subv << endl;

	double subv2 = _nmsp1::Sub(4.7, 2.1);
	cout << "subv2 = " << subv2 << endl;

	//string a("abc"), b("def");
	//string addresult = _nmsp1::Sub(a, b);

	//cout << "addresult = " << addresult << endl;

	//二：实例化
		//实例化：编译时，用具体的 "类型" 代替 "类型模板参数" 的过程就叫做实例化（也叫做代码生成器）
		//.obj文件在编译完成之后就会产生
		//.obj文件的格式一般会被认为是一种COFF-- 通用对象文件格式
		//实例化之后的函数名分别叫做Sub<int> 和 Sub<double>
		//通过函数模板实例化之后的函数名包含三部分：
			//1)模板名 2)后面跟着一对<>  3)<>中间是一个具体类型
		//实例化是在编译期间发生的.
		//在编译阶段，编译器就会查看函数模板的函数体部分，来确定能够针对该类型string进行Sub函数模板的实例化
			//在遍历阶段，编译器需要能够找到函数模板的函数体部分
	//int subv3 = _nmsp1::Sub(1, 1.1);   这种不行
	double subv4 = _nmsp1::Sub(double(3), 1.1);   //强制类型转换可以
	int subv5 = _nmsp1::Sub<int>(1, 1.1);   //这样在<int>中指定类型就可以

	//三：模板类型的推断
	//(3.1)常规的参数推断
		//通过<>可以值指定一部分模板参数的类型，另外一部分模板参数的类型可以通过调用时给的实参来推断
		//通过auto代替函数模板返回类型
		//decltype,可以与auto结合使用来构成返回类型的后置语法。这种后置语法其实也就是使用auto和decltype结合来完成返回值类型的推导

	//(3.2)各种推断的比较以及空模板参数列表的推断
		//a)自动推断
		//b)指定类型模板参数，优先级比自动推断高
		//c)指定空模板参数列表,意思是告诉编译器，要调用MyDouble的函数模板，而不是普通函数
	cout << "----------------------分界线-----------------" << endl;
	//cout << _nmsp1::add(12, 17.8) << endl;  //编译器不能自动推断出V
	cout << _nmsp1::add<int, double, double>(12, 17.8) << endl;   //	//template<typename T,typename U,typename V>
	cout << _nmsp1::add<double>(12, 17.8) << endl;
	
	cout << _nmsp1::ADD(12, 17.8) << endl;
	cout << _nmsp1::ADD1(12, 17.8) << endl;


	cout << "----------------------分界线----------------" << endl;
	cout << _nmsp1::MyDouble(15) << endl;   //可以推断出T类型是int;

	int result1 = _nmsp1::MyDouble<int>(16.9);  //明确指出模板参数
	
	auto result2 = _nmsp1::MyDouble<>(16.9);	//此种场合下，空的<>没有用处，但是语法上允许。

	auto result3 = _nmsp1::MyDouble(16.9);		//调用的是普通函数，对于编译器，模板也合适,普通函数也合适，编译器会优先调用普通函数
	return 0;
}
