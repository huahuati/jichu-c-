#include<iostream>
using namespace std;

namespace _nmspl
{
	//二：malloc来分配0个字节
	//老手程序员和新手程序员最大的区别:老手程序员对于不会或者没闹明白的东西可以不去用，但是一般不会用错。
		//新手程序员正好相反，发现系统没有报什么异常就觉得是正确的；
	//即便malloc(0)返回的是一个有效的内存地址，也不要去动这个内存，不要修改内容，也不要去读。所以不要写这种代码
	void func()
	{
		void* p = malloc(0);   //new调用的也是malloc
		//char* p = new char[0];
		char* q = (char*)p;
		strcpy_s(q, 100, "这里是一个测试");   //100表示最大的内存
												//这行导致程序出现暗疾和隐患
		free(p);   //出现异常

		int abc;
		abc = 1;
	}

}

int main()
{
	_nmspl::func();
	return 0;
}