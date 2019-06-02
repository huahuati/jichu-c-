
	(1)派生类对象模型简述

		Men mymen;    子类(派生类对象)，包含多个组成部分(也就是多个子对象);
		(1)一个是含有派生类自己定义的成员变量，成员函数的子对象。
		(2)一个是该派生类所继承的基类的子对象，这个子对象中包含的是基类中定义的成员变量，成员函数(派生类对象含有基类对应的组成部分)

		Human *phuman = new Men;   基类指针可以new派生类对象，因为派生类对象含有基类部分， 所以我们是可以把派生类当成基类对象用的。
								   换句话说我们可以用基类指针new一个派生类对象。   
								   编译器帮组我们做了隐式的这种派生类到基类的转换。
								   这种转换的好处就是有些要写基类引用的地方可以用这个派生类对象的引用来代替，如果有些需要基类指针的地方，也可以用派生类的指针来代替

	class A{
	public:
		A(int i):m_valuea(i){};		初始化列表

	private:
		int m_valuea;
	};
	class B:public A:
	{
		public:
			B(int i,int j,int k):A(i),m_valueB(k){		通过子类的初始化列表给父类的构造函数传递参数
			}
		public:
			int m_valueB
	};
	(2)：派生类构造函数：
		Men mymen;   即调用基类构造函数，也调用派生类构造函数。
		派生类实际是使用基类的构造函数初始化它的基类部分。基类控制你基类部分的成员初始化，派生类控派生类部分成员的初始化，大家各司其职。

		传递参数给基类构造函数问题：通过派生类的构造函数初始化列表。

		B b(10,20,50);	先执行基类的构造函数，再执行派生类的构造函数
						先执行派生类的析构函数，再执行基类的析构函数



	(3)即当父类又当子类

		class gra{...};
		class fa:public gra{...}		gra是fa的直接基类
		class son:public fa{...}		gra是son的间接基类(爷爷类)
		继承关系一直传递，构成了一种继承链，最总结果是派生类son会包含它的直接基类的成员以及每个间接基类的成员。

	(4)不想当基类的类
		c++11 标准：final，加在类名后面，有这个关键字就不能做基类了。

	(5)静态类型与动态类型
	Human *phuman = new Men()    基类指针指向一个派生类对象
	Human &q = *phuman;   		 基类引用绑定到派生类对象上。

	静态类型：变量声明的时候的类型。静态类型编译的时候是已知的。
	动态类型：指的是这个指针/引用所代表的(所表达的)内存中的对象的类型。这里是Men类型。
			动态类型是在运行的时候才能知道。
	动态类型，静态类型这种概念，只有基类指针/引用才存在这种静态类型和动态类型不一致的情况。
	如果不是基类的指针/引用，那么静态类型和动态永远都应该是一致的

	(6)：派生类向基类的隐式类型转换
		Human *phuman = new Men();    基类指针指向一个派生类对象
		Human &q = *phuman;			  基类引用绑定到派生类对象上

		编译器隐式的帮我们执行哪个了派生类到基类的转换。

		※※※※※※※
		这种转换之所以能够成功，是因为每个派生类对象都包含一个基类对象部分，所以基类的引用或者指针是可以绑到派生类对象这部分
		※※※※※※※

		并不存在从基类到派生类的自动转换

		Men *pmen = new Human();   非法

		Human human;
		Men &my = human;		非法，不能将基类转成派生类(派生类的引用不能绑定到基类对象上去)
		Men *pmy = &human;		非法，不能将基类转成派生类(派生类指针不能指向基类地址)

		Men men;
		Human *phuman = &men;   可以
		Men *pmen = phuman      不可以，编译器通过静态类型推断转换合法性。发现基类不能转成派生类
		如果基类有虚函数的话，可以通过  dynamic_cast 可以转换

		Men *pmen = dynamic_cast<Men *>(phuman);

	(7)：父类子类之间的拷贝与赋值
	Men men;
	Human human(men);   用派生类对象来定义初始化基类对象。这个会导致基类的拷贝构造函数的执行。

	Men men;
	Human human;
	human = men;   调用赋值运算符

	结论：
	用派生类对象为一个基类对象或者赋值时，只有派生类对象的基类部分会被拷贝或者赋值，派生类部分将被忽略掉。
	也就是：基类只干基类自己的事，多余的部分不会去操心。
