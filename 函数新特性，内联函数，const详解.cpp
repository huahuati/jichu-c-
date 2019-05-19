一：函数回顾与后置返回类型
	
	函数定义中，形参如果在函数体内用不到的话，则可以不给形参变量名字，只给其类型。
	函数声明时，可以只有形参类型，没有形参名。
	把函数返回类型放到函数名字之前，这种写法，叫前置返回类型。

	c++11 中，后置返回类型，就是在函数声明和定义中，把返回类型写在参数列表之后。
		写法： 
			auto func123(int  ,int )-> void;  //函数声明原形
			auto func123(int a ,int b)-> void;
			auto：自动类型推断

二：内联函数：
	在函数定义以前增加了关键字 inline，导致该函数变成内联函数。
	函数体很小，调用很频繁的函数。我们引入 inline (内联函数)

	(1) inline  影响编译器，在编译阶段时对 inline 这种函数进行处理，系统尝试将调用的动做替换为函数本体。通过这种方式，来提升性能。
	(2) inline只是我们开发者对编译器的一个建议，编译器可以尝试去做，这取决于编译器的诊断功能，决定权在编译器，我们无法控制。
	(3) 内联函数的定义就要放在头文件中。这样需要用到这个内联函数的.cpp文件都呢能够通过#include把这个内联函数的源代码#include进来，
		一边找到这个函数的本体源代码并尝试将该函数的调用替换内函数体内的语句。

	优缺点：
		代码膨胀问题：所以内联函数 函数体尽量要小。

		注意：各种编译器对 inline 的处理各不相同。inline函数尽量简单，代码尽可能少。循环，根治，递归调用尽量不要出现在 inline 中
		否则的话，编译器跟可能就会因为你写这些代码的原因拒绝然这个函数成为一个 inline 函数体尽量要小。

		constexpr 函数 可以看成更严格的一种内联函数。

三：函数杂合用法总结
	(1)函数放回类型为 void ，表示函数不返回任何类型。但是我们可以调用一个返回类型是 void 的函数。让函数可以作为另一个返回类型是 void 
	   的函数的返回值

	   例：
		   void funca(){}

		   void funcb{

		   		return funca();
		   }

	(2)函数返回指正和返回引用的用法：

	   例：
	   		int *myfunc(){
	   			int tempvalue = 9;
	   			return &tempvalue;    这不可以，应为函数执行完毕后，tempvalue这段内存被系统回收，你不能够再使用。
	   		}

	   		int &myfunc(){
	   			int tempvalue = 9;
	   			cout << &tempvalue << endl;
	   			return tempvalue   				又是一个巨大隐患
	   		}      								可以用变量来接收 函数引用  int n = myfunc();

	(3)没有形参可以保持形参列表为空(),或者 int myfuc(void)
	(4)如果一个函数如果不调用的话，则该函数可以只有声明部分，没有定义部分。
	(5)普通函数，定义只能定义一次(定义放在.cpp文件中),声明可以声明多次。一般函数定义.cpp文件会#include自己的函数声明文件.h
	(6)void func(int &ta, int &tb),在c++中，更习惯引用类型的形参来取代指针类型的形参。提倡在c++中多使用引用类型的实参。
	(7)c++中，函数允许同名，但是形参列表的参数类型或者数量应该有明显的区别。

四：const char * , char const *, char * const 三者的区别
	
	const int abc = 12;

	char *p :  const的混用：

	(1)const char * p; 代表p 指向的东西不能通过p来修改(p所指向的目标，那个目标中的内容不能通过p来改变)

	char str[] = "I LOVE CHINA"
	const char *p ;
	p = str;
	//*p = 'Y';    语法错误
	p++;
	str[0] = 'Y';  这是ok的

	(2) char const * 等价于 const char *

	(3)char * const
	   char = str[] = 'I LOVE CHINA';
	   char * const p =str  				定义的时候必须初始化，p一旦指向了一个东西之后，就不可以再指向其他的东西了
	   p++;     							不可以
	   *p = 'Y';							但是可以修改p指向的目标的内容。
								
	(4)const char * const p = str 等价于 char const * const p = str; p的指向和p的内容都不能变

	(5)
		int i = 100;
		const int &a = i;     代表a 的内容不能通过 a 修改
		i = 100 可以通过i来修改

	(6)const int &b = 31;	给引用分配了内存
	   cout <<b << endl;  可以通过