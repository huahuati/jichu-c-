一：构造函数：在类中，有一种特殊的成员函数，他的名字和类名相同，我们咋其创建类的对象的时候。
			 这个特殊的成员函数就会被系统自动调用。这个成员函数，就叫"构造函数"。
			 因为构造函数会被系统个自动调用，所以我们可以简单的理解成：构造函数的目的就是初始化类对象的数据成员。

	class time{
	public:
		int hour;
		int minute;
		int second;
	public:
		time(int tmphour,int tmpmin, int tmpsec){
			hour = tmphour;		
			minute = tmpmin;
			second = tmpsec;
			cout << "调用了三个参数的构造函数" << endl;
		}
	public:	time(){
			hour = 12;
			minute = 13;
			second = 52;
			cout << "调用了空的构造函数" << endl;
		}
	public:	time(int number){
			hour = number ;
			minute = 13;
			second = 52;
			cout << "调用了单参数的构造函数" << endl;
	}
	public:
		time(int tmphour,int tmpmin, int tmpsec=52){
			hour = tmphour;		
			minute = tmpmin;
			second = tmpsec;
	};

	(1)构造函数没有返回值，这也是构造函数的特殊之处。
	(2)不可以手工调用构造函数，否则编译就会出错。
	(3)正常情况下，构造函数应改被声明为public ，因为我们创建一个对象时，系统要替我们调用构造函数，这说明构造函数它是一个public函数,
	才能被系统(外界)调用。因为类缺省的成员是私有成员，所以我们必须说明构造函数是一个public函数，否则无法直接创建该类的对象
	(4)构造函数中如果有多个参数，则我们创建对象的时候也要带上这些参数。

	time mytime = time(12,13,52);    创建类对象
	time mytime2(12,13,52);
	time mytime3 = time{12,13,52};
	time mytime4{12,13,52};
	time mytime5 = {12,13,52};

二：多个构造函数：一个类中可以有多个构造函数，就可以为类对象的创建提供多种初始化方法。参数的个数和参数的类型不一样即可。
	time mytime = time();    创建类对象
	time mytime2;
	time mytime3 = time{};
	time mytime4{};
	time mytime5 = {};


	对象拷贝
	time mytime6;可以调用构造函数

	如下四个对象并没有调用传统意义上的构造函数，后续笔记记载，他们调用的实际上是拷贝构造函数。
	time mytime7 = mytime6;
	time mytime8(mytime6);
	time mytime9{mytime6};
	time mytime10 ={mytime6};

三：函数默认参数
	
	(1)默认值只能放在函数声明中，除非该函数没有函数声明。
	(2)在具有多个参数的函数中指定默认值时，默认参数都必须出现在不默认参数的右边，
		一旦某个参数开始指定默认值，它右边的所有参数必须指定默认值。

		time mytime11 = time(12,13);    创建类对象
		time mytime12(12,13);
		time mytime13 = time{12,13};
		time mytime14{12,13};
		time mytime15 = {12,13};

四：隐式转换和explicit

	编译系统，在私下干了很多我们所不知道和不了解的事。
	time mytime40 = 14  			 编译系统肯定有一个行为，把14这个数字 转换成立一个 time类型，调用了单参数的构造函数。
	time mytime = (12,13,14,15,16);	 调用了单参数的构造函数。

	time mytime16 = {16}；    这个写法我们认为正常，带一个参数16，可以让系统明确的知道调用了哪个构造函数,隐式类型转换。
	time mytime17 = 16;       含糊不清的写法，就存在临时对象的隐式转换。

	是否可以强制系统，明确要求构造函数不能做隐式类型转换呢？
		可以，如果构造函数声明中带有explicit,则这个构造函数只能用于初始化和显示类型转换。

		class time1{
			public:
				int hour;
				int minute;
				int second;
			public:
				explicit time(int tmphour,int tmpmin, int tmpsec){
					hour = tmphour;		
					minute = tmpmin;
					second = tmpsec;
					cout << "调用了三个参数的构造函数" << endl;
				}
			};

			time1 mytime = time1(12,13,52);    
			time1 mytime2(12,13,52);
			time1 mytime3 = time1{12,13,52};
			time1 mytime4{12,13,52};
			time1 mytime5 = {12,13,52};    隐式类型转换。这个出现问题。

	(1)对于单参数的构造函数，一般都声明为 explicit ,除非你有特别原因。


五：构造函数初始化列表
	
	class time2{
			public:
				int hour;
				int minute;
				int second;
			public:
				 time(int tmphour,int tmpmin, int tmpsec)
				 :hour(tmphour),minute(tmpmin),second(tmpsec)
				{
					cout << "调用了三个参数的构造函数" << endl;
				}
			};

	(1)显得专业，高大上。
	(2)效率上更高。