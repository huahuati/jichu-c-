#include<iostream>
using namespace std;

class MYACLS
{
public:
	virtual void myvifunc1() 
	{

	}
	virtual void myvifunc2()
	{

	}
};

int main()
{	
	printf("MYACLS::myvifunc1虚函数的地址为%p\n", &MYACLS::myvifunc1);  //打印的是vcall函数(代码)地址，不是真正的虚函数地址
	printf("MYACLS::myvifunc1虚函数的地址为%p\n", &MYACLS::myvifunc2);
	cout << sizeof(MYACLS) << endl;

	MYACLS* pmyobj = new MYACLS();

	//vcall thunk;
	//(1)调整this
	//(2)跳转到真正的虚函数中去
	return 0;
}