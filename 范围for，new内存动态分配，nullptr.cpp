#include<iostream>
using namespace std;
int main(){
	一：范围for语句(用于遍历一个序列)
	int v[] {12,13,14,15,16}
	for(auto x:v){				 数组v中每个元素，一次放入x中并打印x值。把v每个元素拷贝到x中，打印x值。（把v中的元素拷贝到x中）
		cout << x << endl;
	}
	for(auto &x:v){				把x作为v的引用，省去的拷贝的动作
		cout << x<< endl;
	}

	二：动态内存分配问题：c中供程序使用的存储空间，有程序区，静态存储区，动态存储区
		c++中，把内存进一步详细分为5个区域；
		(1)栈：一般函数内的局部变量都会放到这里，有编译器自动分配个释放
		(2)堆：程序员用malloc/new分配，用free/delete来释放。(忘记释放后，系统会回收)
		(3)全局/静态存储器：放全局变量和静态变量static。程序结束时系统释放。
		(4)常量存储区:"i love china"
		(5)程序代码区

		堆和栈不同的用途和区别
		(1)栈： 空间是有限的。这是系统规定的，跟配速度块，程序员也控制不了。
		(2)堆： 只要不超出你实际拥有的物理内存，也在操作系统允许能够分配的最大内存大小之内，都可以分配给你。
			分配速度比栈慢，你可以随时用new/malloc来分配，free/delete来释放。非常灵活。

			malloc和free ：在c语言中，用malloc和free从堆中来分配和释放内存用。malloc和free()是函数
			malloc(memory allocation)：动态内存分配
			
			一般形式：

			malloc:
			void *malloc(int NumBytes)   NumBytes:要分配的字节数。分配成功则返回指向被分配内存的指针，分配失败则返回null。
			当这段分配的内存你不使用的时候，你该用free（）函数来将内存释放掉，供其他地方使用。

			free:
			void free(void *FirsByte):将之前用malloc分配的内存空间还给程序（操作系统），也就是说释放了这块内存，
			这样这块内存就被系统回收，并在需要的时候给其他地方使用。

			例：
				int *p = NULL;   c语言的写法   等价于数字零
				p = (int *)malloc(sizeof(int));
				if(p != NULL){如果分配成功
					*p = 5;
					cout <<*p << endl;
					free(p);     释放到分配的内存
				}

				int *p = (int *)malloc(sizeof(int ) *100);     分配可以放得下100个整数的内存空间
				if(p != NULL){
					int *q = p;
					*q++ = 1;
					*q++ = 5;
					cout << *p << endl;    		结果为一
					cout << *(p+1) << endl;   	结果为五
					free(p);
				}

				char *point = NULL;
				point = (char *)malloc(sizeof(char)*100);    100 个位置
				if(point 1= NULL){
					strcpy_s(point,100,"hello world");   100是限定字符串的长度
					cout << point << endl;
					free(point);
				}


			new 和delete：是运算符(标识符)。 c++ 中就用new/delete分配个释放内存，不再使用malloc和free来分配和释放内存
			new,delete 也和 malloc/free 管理一样的时候就是分配和释放内存。同时new,delete还干的更多的事。

			new 一般使用格式：
				(1)指针变量名 = new 类型标识符
				(2)指针类型名 = new 类型标识符(初始值)      		注意这里圆括号括起来，表示初始值
				(3)指针类型名 = new 类型标识符[内存单元的个数]   	注意，这里是[]


				例：
					int *myint = new int;
					if(myint != NULL){
						*myint = 8;    *myint 代表指针指向的变量
						cout << *myint << endl;
						delete myint;   释放单个myint的空间

					}

					int *myint = new int(18);
					if(myint != NULL){
						cout << *myint << endl;
						delete myint;   释放单个myint的空间
					}

					int *pa = new int[100];  开辟一个大小为100的整形数组空间
					if(pa != NULL){
						int *q = pa;
						*q ++ =12; [0] = 12 
						*q ++ =18; [1] = 18 执行完这行，这个q其实已经指向[2];

						cout << *pa << endl;    值为12
						cout << *(pa + 1) << endl 值为18

						delete[] pa;    释放int pa 数组空间 ，new时我们使用 [] ,那么delete就必须用[] ,[]不写数组大小;
					}

		三：nullptr   c++中引入新关键字

			nullptr代表的也是空指针

			char *p = NULL;  NULL实际上就是零
			char *q = nullptr;
			int *p = nullptr;

			if(p = nullptr){
				cout << "good " << endl;
			}

			使用nullptr呢能够避免在整数和指针之间发生混淆
			NULL和nullptr实际上是不同的类型

			结论：对于指正的初始化，和以往用到的指针有关的NULL的场合，能用nullptr的全部都用nullptr进行取代
		}
		额外补充知识
		(1) 配对使用有malloc成功必然有free，有new成功必然有delete。
		(2) free/delete,不要重复调用

		(3)malloc/free 和new/delete区别;	
