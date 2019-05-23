一：隐式类型转换 ：系统自动进行，不需要程序开发人员介入

		int m = 3 + 45.6;			int之前计算结果为48.6000000,它小数部分截掉，也属于隐式类型转换的一种行为。
		double n = 3 + 45.6


二：显示类型转换(强制类型转换)

		int k  = 5 % 3.2   				语法错误
		int k  = 5 % (int)3.2；      	c语言风格的强制类型转换
		int k  = 5 % int(3.2)			函数风格的强制类型转换(c语言风格的强制类型转换)、
		

		c++强制类型转换分为4种：现在写程序应该使用c++ 风格的强制类型转换。
		这4种强制类型转换，分别用于不同目的，每一个都又一个不同的名字。
		提供四种类的目的：提供丰富的含义和功能，更好的检查类型

		(1)static_cast
		(2)dynamic_cast
		(3)const_cast
		(4)reinterpret_cast
		这四个强制烈性转换都被称呼为"命名的强制类型转换(因为他们每一个都有一个名字并且名字个不相同)"

		通用形式:强制类型转换名<type>(express)
		强制类型转换名，是上边的a,b,c,d四个名字之一。
		type:转换的目标类型
		express：你要转换的值(你要转换的是谁)

		(1.1)static_cast : 静态转换，大家就理解成"正常转换"，编译的时候就会进行类型转换的检查。
						   代码中要保证转换的安全性和正确性。static_cast 含义跟c语言中的强制类型转换这种感觉差不多。
						   c语言风格的强制类型转换，以及，编译器能够进行的隐式类型转换，都可以用static_cast类显式完成。

			 可用于：
			 
			 		(1) 相关类型转换，不如整性型和实型的转换。

						double f = 100.34f;
						int i = (int)f;
						int i2 = static_cast<int>(f);	   

					(2)学习类的时候转成父类类型(继承关系),也能用这个static_cast转。

					(3)void * 与其他类型指针之间的转换, void*:  无类型指针:可以指向任何指针类型(万能指针)

							int i =10;
							int *p = &i;
							void *q = static_cast<void *>(p);    int * 转成 void *
							int *db = static_cast<int *>(q);

			不可用于:

					(1)一般不能用于指针类型之间的转换比如 int * 转 double *,float * 转 double * 等等。

						double f = 100.0f;
						double *pf = &f;
						int *i = static_cast<int *>(pf);  		不可以
						float *fd = static_cast<float *>(pf);  	也不可以  

		(2.2)dynamic_cast:主要应用于 运行时类型识别和检查。主要用来父类型和子类型之间转换
						 (父类型指正指向子类型对象，然后用dynamic_cast把父指针类型往子指针类型转)

			 	后续笔记中详细记载。

		(2.3)const_cast：去除 指针 或者 引用 的const属性。该转换能够将const性质转换掉，编译时就会进行类型转换。


				const int ai = 90;
				int ai2 = const_cast<int>(ai);  		ai不是指针也不是引用不能转。

				const int *pai = &ai;
				int * pai2 = const_cast<int *>(pai);	正确

				*pai2 = 120    这种写值行为，是属于一种未定义行为，不要这么做。

				cout << ai <<endl;
				cout << *pai << endl;

		(2.4)reinterpret_cast:编译的时候就会进行类型转换的检查
			 reinterpret：重新解释。(将操作数内容解释为另一种不同的类型[能把操作数的类型都给转了])
			 处理无关类型的转换。也就是两个转换类型之间没有什么关系。就等于可以乱转，自由转。怎么转都行，很随意。

			 常用于如下两种转换:
			 
			 		(1)将一个整型(地址)转换成指针，一种类型指针转换成另一种类型指针，按照转换后的内容重新解释内存中的内容。
			 		(2)也可以从一个指针类型转换成一个整型。

			 			int i =10;
			 			int *pi = &i;
			 			int *p2 = reinterpret_cast<int *>(&i);
			 			char *pc = reinterpret_cast<char *>(pi);

			 			int i = 10;
			 			int *pi = &i;
			 			void * pvoid = reinterpret_cast<void *>(pi);
			 			int *pi2 = reinterpret_cast<int *>(pvoid);

			 	被认为是危险的类型转换;随便怎么转都行，编译器都不报错。
			 	int ivl = 100；
			 	long long lvl = 8898899400    八字节的   十六进制：2126A6DC8
			 	int *pivl = (int *)ivl;		  c语言风格	  地址0x00000064
				int *piv2 = reinterpret_cast<int *>(ivl)  地址0x00000064
				piv2 = reinterpret_cast<int *>(lvl)		0x126a6dc8   把前面的2丢了，因为piv2是4字节
				long long ne = reinterpret_cast<long long >(piv2);   指针类型转整型 = 308964808    转为十六进制为 = 126A6DC8 
总结：
		(1)强制类型转换，不建议使用。强制类型转换能够抑制编译器报错。
		(2)学习目的：认识这些类型转换符，方便阅读别人代码。
		(3)资料说:reinterpret_cast危险。使用const_cast意味着设计缺陷。
		(4)如果实在需要使用类型转换，不要在使用c语言了，使用c++的const属性。该转换能够将const性质转换掉，编译时就会进行类型转换。
		(5)一般static_cast 和 reinterpret_cast 就能够很好的取代c语言的类型转换。

		reinterpret_cast只要好好用，合符规则的用，不要乱用，其实reinterpret_cast很好用。