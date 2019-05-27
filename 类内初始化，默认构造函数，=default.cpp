一：类相关非成员函数
	普通函数，不是成员函数
	 void Writetime(time &mytime){
	 	std::cout << mytime.hour << endl
	 }
	 函数的声明放在类的后面

二：类内初始化
	
	在c++11里，我们可以为类内成员变量提供一个初始值，那么我们在创建对象的时候，这个初始化值就用来初始化该成员变量。
	class time{
		public:
			int hour;
			int minute;
			int second = {0};   类内初始化值 
		};

三：const成员变量的初始化在构造函数的列表里面初始化，不可以通过赋值来初始化

	class time{
		public:
			int hour;
			int minute;
			int second;
			const int ctestvalue = 80;  定义了一个常量，
		};

四:默认构造函数：没有参数的构造函数，我们就称为默认构造函数。
   没有构造函数，这些类对象如何初始化呢？
   			这叫"默认初始化"，也就是说，这个类通过一个特殊的构造函数来执行默认的初始化过程。
   			那么这个特殊的构造函数就叫做"默认的构造函数",也就是无参数的构造函数。

   	在类定义中，如果没有构造函数的情况下，编译器就会为我们隐式的自动定义一个"默认构造函数"(无参)
   	称为"合成的默认构造函数"。

   	这个"合成的默认构造函数"做了些什么?
   		其实他没有做什么
   	
   	一旦我们自己写了一个构造函数，不管这个构造函数带几个参数，编译器就都不会为我们生成"合成的默认构造函数"了。



			class Time2{
			public:
				explicit Time2(){      不带参数的构造函数
					Hour = 12;
				} 

			public:
				int Hour;
				int Minute
				int Second {0};

			}

			Time2 mytime2;    生成对象时会调用类的无参构造函数。

			class Time3{
			public:
				int Hour;
				int Minute
				int Second {0};

			}

			Time2 mytime3;   会生成合成的默认构造函数

			class Time3{
			public:
				int Hour;
				int Minute
				int Second {0};
				Time3(int tmphour){
					Hour = tmphour;
				}
			}

			Time2 mytime3;   这样写将是错误的，因为有参数的构造函数，将不会生成"合成的默认构造函数"；。
五: =default ,=delete: c++ 11 引入的
			int func() = default;     非特殊函数，不可以使用 = default;

			class Time4{
			public:
				int Hour;
				int Minute
				int Second {0};
				Time4(int tmphour){}    带参数的构造函数，也不可以使用 =default。
				Time4() = default;     编译器能够为这种 =default 的函数自动生成函数体。
			};
			Time4 mytime4;   能够实现。

			=default; 编译器能够为我们自动生成函数体。

			class Time5{
			public:
				int Hour;
				int Minute
				int Second {0};
				Time5(int tmphour){}    带参数的构造函数，也不可以使用 =default。
				Time5() = delete;		让程序员显式的禁用某个函数。

			}

			Time5 mytime5;  实效，没有不带参数的构造函数，所以定义对象失败。