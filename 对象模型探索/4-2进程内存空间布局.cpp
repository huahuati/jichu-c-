#include<iostream>
using namespace std;

int* ptest = new int(120);
int g1;
int g2;
int g3 = 12;
int g4 = 32;
int g5;
int g6 = 0;
static int g7;
static int g8 =0;
static int g9 = 10;

void mygfunc()
{
	return;
}

//定义一个类
class MYACLA
{
public:
	int m_i;
	static int m_si;  //声明不是定义
	int m_j;
	static int m_sj;
	int m_k;
	static int m_sk;
};

int MYACLA::m_sj = 0;   //这才是定义


int main() {
	//第二节 进程内存空间布局
	//不同的数据在内存中会有不同的保存时机，保存位置

	//当运行一个可执行文件时，操作系统就会把这个可执行文件加载到内存；此时进程有一个虚拟的地址空间(内存空间)
	//linux有个nm命令：能够列出可执行文件中的全局变量存放的地址；

	printf("ptest地址=%p\n", &ptest);
	printf("g1地址=%p\n", &g1);
	printf("g2地址=%p\n", &g2);
	printf("g3地址=%p\n", &g3);
	printf("g4地址=%p\n", &g4);
	printf("g5地址=%p\n", &g5);
	printf("g6地址=%p\n", &g6);
	printf("g7地址=%p\n", &g7);
	printf("g8地址=%p\n", &g8);
	printf("g9地址=%p\n", &g9);
	printf("MYACLS::m_sj地址=%p\n", &(MYACLA::m_sj));

	printf("mygfunc()地址=%p\n", mygfunc);
	printf("main()地址=%p\n", main);

	cout << (void*)mygfunc << endl;
	return 0;
}