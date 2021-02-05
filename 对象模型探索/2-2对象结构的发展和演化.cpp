#include<iostream>
#include<string>
using namespace std;
class A
{
public:
	//int a = 100;  //非静态成员变量
	//static int aa;//静态成员变量是跟着类走
	//static int bb;

	//static void sfunc() {}   //静态成员函数
	//void mufunc() {}  //普通成员函数

	//virtual void myfunc3() {};
	//virtual void myfunc4() {};
	//virtual void myfunc5() {};
	//virtual void myfunc6() {};
	//virtual void myfunc7() {};

	char a;  //1个字节
	int i;  //四个字节
};

class myobject
{
public:
	myobject() {};  //构造函数
	virtual ~myobject() {};   //析构函数
	float getvalue() const // 普通成员函数
	{
		return m_value;
	}
	static int s_getcount()   //静态成员函数
	{
		return ms_scount;
	}
	virtual void vfrandfuc() {};   //虚函数
protected:
	float m_value;   //普通成员变量
	static int ms_scount;   //静态成员变量
};
int main() {
	//对象结构的发展和演化
	//(1)非静态的成员变量(普通成员变量)跟着对象走(存在对象内部),也就是每个类对象都有自己的成员变量
	A obj;
	int ilen = sizeof(obj);
	cout << ilen << endl;
	return 0;
}

	//(2)静态成员变量跟对象没有什么关系，所以肯定不对保存的对象内部，是保存在对象外面(表示所占用的内存空间和类对象无关)
	//跟着类走，依赖一整个类

	//(3)成员函数:不管静态还是非静态，全部都保存在类对象之外。
	//不管几个成员函数，不管是否是静态的成员函数，对象的sizeof都不会增加。

	//(4)虚函数:不管几个虚函数，sizeof()都是4个字节。
	//(4.1)类里面只要有一个虚函数(或者说至少有一个虚函数)，这个类会产生一个 指向 "虚函数" 的指针。
	//有两个虚函数，那么这个类就会产生两个指向虚函数的指针。
	//类本身指向虚函数的指针(一个或者一堆)要有地方存放，存放在一个表格里，这个表格我们就称为 "虚函数表(virtual table)"。
	//这个虚函数表一般是保存在可执行文件中的，在程序执行的时候载入到内存中来。
	//虚函数是基于累的，跟着类走的；

	//(4.2)类对象为什么增加的四个字节？其实是因为虚函数的存在，因为有了虚函数的存在，导致系统往类对象中添加了一个指针。
	//这个指针正好指向这个虚函数表，这个指向叫  "vptr" ;这个 vptr的值有系统在适当的时机(比如构造函数中通过增加额外的代码来给值)


	//-----------总结:对于类中
	//(1)静态数据成员不计算在对象sizeof内()
	//(2)普通成员函数和静态成员函数不计算在类对象的sizeof()内。
	//(3)虚函数不计算在类对象的sizeof()内，但是虚函数会让类对象的sizeof()增加4个字节一容纳虚函数表指针。
	//(4)虚函数表[vtbl]是基于类的(跟着类走的，跟对象没关系，不是基于对象的。)
	//(5)如果有多个数据成员，那么为了提高访问速度，某些编译器可能会将数据成员之间的内存占用比例进行调整。(内存字节对齐)
	//(6)不管什么类型指针 char *p ,int  *q; 该指针占用的内存大小是固定的
	
	int ilen2 = sizeof(char*);
	int ilen3 = sizeof(int*);

	cout << "ilen2 = " << ilen2 << endl;
	cout << "ilen3 = " << ilen3 << endl;

	myobject obj1;
	int iline11 = sizeof(obj1);
	cout << "iline11= " << iline11 <<  endl;    //八字节
	return 0;
}