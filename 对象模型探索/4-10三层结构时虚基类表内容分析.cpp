#include<iostream>
using namespace std;

class Grand //爷爷类
{
public:
	int m_grand;
};


class A1 :virtual public Grand
{
public:
	int m_a1;
};
class A2 :virtual public Grand
{
public:
	int m_a2;
};
class C1 :public A1, public A2
{
public:
	int m_c1;
};

int main()
{
	//一：三层结构时虚基类表内容分析
	cout << sizeof(Grand) << endl; 
	cout << sizeof(A1) << endl;     
	cout << sizeof(A2) << endl;     
	cout << sizeof(C1) << endl;  

	C1 c1obj;
	c1obj.m_grand = 2;   //21-24字节
	c1obj.m_a1 = 5;      //5-8字节
	c1obj.m_a2 = 6;		//13-16字节
	c1obj.m_c1 = 8;		//17-20字节
						//vptr1 1-4字节
						//vptr2 9-12字节

	//分析发现：没有用到vptr2，只用到vptr1
	//访问虚基类成员时，速度会变慢

	//二：虚基类为什么这么设计
	//为什么这么设计
	return 0;

}