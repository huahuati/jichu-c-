一:重载运算符

	==,>,>=,<,<=,!=,++,--,+=,-=,+,-;cout,cin,<<,>>,=等运算符。

	两个对象那个可以进行比较吗？
		是可以比较的，我们需要 "重载 == 运算符"，
		重载：写一个成员函数，这个成员函数名为 "operator==",这个成员函数体里边，我们就要写一些比较逻辑。

		例：
			if(mytime1.hour == mytime2){
				return true;
			}

		总结：

			重载运算符，本质上是一个函数。整个函数的正式名字: operator 关键字 接 运算符
			既然重载运算符本质上是一个函数，那么会有返回类型和参数列表。
			有一些运算符，如果我们不自己写运算符的重载，那么系统会自动给我们生成一个。比如赋值运算符的重载。

			time mytime;
			time mytime2;
			mytime2 = mytime;


二：拷贝赋值运算符

			time mytime;				调用了默认构造函数
			time mytime2 = mytime;		调用了拷贝构造函数
			time mytime5 = {mytime};	调用了拷贝构造函数

			time mytime6;		调用了默认构造函数
			mytime6 = mytime5;	这个是赋值运算符，既没有调用构造函数，也没有调用拷贝构造函数。系统会调用一个，拷贝赋值运算符。

	我们可以自己重载赋值运算符，如果我们自己不重载，编译器也会为我们生成一个(编译器格外喜欢赋值运算符)。
	编译器生成的赋值运算符重载比较粗糙。一般就是将非 static 成员赋值给赋值运算符左侧的对象的对应成员中去。
	如果成员是个类对象的话，可能还会调用这个类的拷贝赋值运算符。

	为了精确控制 time类的赋值动作，我们往往会自己来重载赋值运算符。
	重载赋值运算符：有返回类型和参数列表，这里的参数就表示运算符的运算对象。比如 mytime5就是运算对象

	赋值运算符重载：

		time & operator=(const time & tmp){   tmp 就是 mytime5。
			
			hour = tmp.hour;
			minute = tmp.minute;
			second = tmp.second;

			cout << "调用了赋值运算符重载" << endl;
			return *this;	把对象自身(mytime6)返回去
		}

		time mytime6;
		mytime6 = mytime5;		输出：调用了赋值运算符重载
		mytime6就是 this 对象   mytime5就是operator=里边的参数。

三：析构函数：析构函数相反与构造函数。对象在销毁的时候，会自动调用析构函数。

	如果我们自己不写自己的析构函数，编译器也会生成一个默认的析构函数。默认析构函数的函数体为空{},表示默认析构函数没干什么有意义的是。
	
	构造函数里 new,delete。
	
	析构函数一个类的成员函数，它的名字是由	~接类名构成，没有返回值，不接受任何参数，不能重载，一个类只有唯一的一个析构函数。

	函数重载：系统允许函数名字相同，但是这些函数的参数个数或者参数类型不同，系统允许这些同名函数同时存在。系统可以判断应该调用那个函数。

	~ time(){
		std::cout << "调用了析构函数" << std::endl;
	}

	构造函数的成员初始化：干了两个事，函数体之前和函数体之中。
	构造函数的成员销毁:干了两个事，函数体之前和函数体之后。
	成员变量的初始化和销毁时机：先定义的变量先有值。先定义后销毁。

	new 对象和 delete 对象。	new 对象的时候，系统调用了time类的构造函数
	time *pmytime5  = new time ;   调用不带参数的构造函数
	time *pmytime6  = new time();  调用不带参数的构造函数

	注意：我们 new 出来的对象，必须要自己释放，否则就会造成内存泄漏。
	在程序停止运行之前的某个时刻，一定要用 delete 把对象占中的内存释放掉。

	delete pmytime5;
	delete pmytime6; 

	什么时候 delete ，系统就会在什么时候去调用类 time 的析构函数。


四：new 和 delete 对析构函数的影响。
	
		class shape
		{
		public:
			shape()
			{
				cout << "ctor" ;
			}
			~shape()
			{
				cout << "Dtor";
			}
		};
		int main()
		{
			shape a;//ctor,Dtor。
			shape* b = new shape;//ctor,无Dtor,若后面添加一条语句delete b;，则有ctor,Dtor。
			//delete b;
			return 0;
		}

		注释 delete b 的运行结果：ctorctorDtor
		添加 delete b 后运行结果：ctorctorDtorDtor