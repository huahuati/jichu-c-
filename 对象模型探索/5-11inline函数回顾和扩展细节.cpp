#include<iostream>
using namespace std;

namespace _nmspl  //命名空间
{
	//一：inline函数回顾
	//使用inline之后，编译器内部会有一个比较复杂的测试算法来评估这个inline函数的复杂度；
	//可能会统计这个inline函数中，赋值次数，内部函数调用，虚函数调用等次数  --权重

	//(1)开发者写的inline只是对编译器的一个建议，但如果编译器评估inline函数复杂度过高，这个inline建议就被编译器忽略
	//(2)如果inline被编译器采纳,那么inline函数的扩展，就要在调用inline函数的那个点上进行
			//那么可能带来额外的问题 ，比如：参数求值，可能产生临时对象的生成和管理

	//二：inline扩展细节
	//(2.1)形参被对应实参取代
	//(2.2)局部变量引用(局部变量，能少用尽量少用，能不用尽量不用)
	//(3.3)inline失败情形
	inline int myfunc(int testc)
	{
		int tempvalue = testc * (5 + 4) * testc;  //局部变量的引用
		//return testc * (5 + 4) * testc;
		return tempvalue;
	}
	inline int myfunc1(int testc)   //inline调用会失败
	{
		if (testc > 10)
		{
			testc--;
			myfunc1(testc);
		}
		return testc;
	}
	int rtnvalue()
	{
		return 5;
	}
	void func()
	{
	    //int i = myfunc(12+15);   //编译器会先求值，然后用实参在替换形参
		//int a = 80;
		//int i = myfunc(a + 15);  //编译器会先计算a和15的和值，然后再替换掉形参

		//int i = myfunc(rtnvalue() + 5); //编译器会先调用rtnvalue()得到返回值，返回值和15做加法，然后在替换掉型参。
		int i = myfunc(5);
		int ii = myfunc1(11);
		cout << i << endl;
	}
}
int main()
{
	_nmspl::func();

	return 0;
}