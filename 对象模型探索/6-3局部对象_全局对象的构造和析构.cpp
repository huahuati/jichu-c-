#include<iostream>
using namespace std;

namespace _nmspl
{
	//一：局部对下那个的构造和析构
	//只要出了对象的作用域，编译器总会在适当的地方插入调用对象析构函数的代码。
	class A
	{
	public:
		A()
		{
			cout << "A()::A()" << endl;
		}
		~A()
		{
			cout << "A::A()" << endl;
		}
		int m_i;
	};
	void func()
	{
		A obja;  //现用现定义，要使用对象时才定义对象。
					//局部对象里边的m_i是随机值。
		obja.m_i;	
		int mytest = 1;
		if(mytest ==0)
		{
			return;
		}
		int b = 0;
		b = 10;
		return;
	}
}
namespace _nmsp2 {
	//二：全局对象的构造和析构
	//全局变量是放在数据段
	//全局对象在不给初值的情况下，编译器默认会把全局对象所在内存全部清为0；
	//全局变量在编译阶段就会把空间分配出来(变量的地址在编译期间就确定好)。

	//全局对象构造和析构的步骤：
		//a)全局对象g_aobj获得地址(编译时确定好的，内存也是编译时分配好的，内存运行期间一直存在)
		//b)把全局对象g_aobj的内存内容清0的能力(也叫静态初始化)
		//c)调用全局对象g_aobj所对应的类A的构造函数
		//d)调用main()函数
		//e)调用全局对象g_aobj所对应A的析构函数
	class A
	{
	public:
		A()
		{
			cout << "A()::A()" << endl;
		}
		~A()
		{
			cout << "A::A()" << endl;
		}
		int m_i;
	};
	int g_aobj;   //全局对象,该全局对象在main函数执行之前就构造完毕，可以在main函数中直接使用了。
					//在main函数执行完毕后，才被析构掉
		
	void func()
	{
		printf("g_aobj全局对象的地址=%p\n", &g_aobj);
	}
}
int main()
{
	_nmsp2::g_aobj = 6;
	//_nmspl::func();
	_nmsp2::func();
	return 0;
}