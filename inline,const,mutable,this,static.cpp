一：在类定义中实现成员函数inline：类内的成员函数实现其实也叫类内的成员函数定义
								这种直接在类的定义中实现的成员函数，会被当做 inline 内联函数来处理。

二：成员函数末尾的const
	
	const : 常量，在成员函数屁股后边增加一个 const。不但要在成员函数声明中增加 const ，也要在成员函数定义中增加 const；
	作用：告诉系统，这个成员函数 不会修改对象里任何成员变量的值等等。也就是说，这个成员函数怒不会修改类的任何状态。
	屁股后面加一个const后缀的成员函数 "常量成员函数";

	const time abc;		定义const对象，这种对象有限制。
	abc.initMillTime(1500);			不可以，initMillTime()并不是 const 成员函数，这个initMillTime() 只能被非const对象调用。

	time def;
	def.initMillTime(1500);

	const 成员函数，则不管是 const 对象，还是非 const，都可以 const，都可以调用 const 成员。
	而非const成员函数，不能够被 const 对象调用，只能被给 const 对象调用。


三：mutable(不稳定，容易改变的意思)，const的反义词。mutable 的引入正好是为了突破 const 的限制。
	
	用 mutable 修饰一个成员变量，一个成员变量一旦被 mutable 修饰。就表示，这个成员变量永远都处于可以被修改的状态，
	即便是在 const 结尾的成员函数中，也可以修改。

四：返回自身对象的引用,this。
	class time{
		public:
			int hour;
			int minute;
			int second;

			static int mystatic;    声明静态成员变量，还没有分配内存，所以也不能在这里初始化。
									在另一个.cpp文件中定义 int time::mystatic = 15; 定义是不需要 static.
			static void mstafunc(int testvalue);
									在另一个.cpp文件中定义 void time::mstafunc(int testvalue){}
									static 成员函数不能修改非 static 成员变量，只能修改 static 的成员变量。

			void initTime(int tmphour,int tmpmin, int tmpsec){
				hour = tmphour;
				minute = tmpmin;
				second = tmpsec;
			}
		public:
			time& add_hour(int tmphour){ 		
				hour += tmphour;		this->hour += tmphour
				return *this;	把对象自己给返回去了
			} 
			time& add_minute(int minute){ 		
				this->minute += minute;		
				return *this;
			}   
		};

	time mytime;
	mytime.add_hour(3).add_minute(12);

	如何理解 this ，我们调用成员函数时，编译器负则把这个对象的地址(&mytime)传递给这个成员函数中的一个隐藏的 this 形参。
	在系统角度看来，对类成员的直接访问都看做是通过 this 做隐式调用的。

	编译器内部的做法
		time& add_hour(time *this int tmphour){ 		
				hour += tmphour;    
				return *this;	把对象自己给返回去了
			} 

		time mytime;
		mytime.add_hour(&mytime,3);
  	
  	(1)this指针只能在成员函数中使用，全局函数，静态函数都不能使用 this 指针。
  	(2)在普通成员函数中，this 是指向非 const 对象的 const 指针(类型为time,那么 this 就是 time *const this),表示 this 只能指向对象 time 对象调用。
  	(3)在 const 成员函数中， this 指正是一个指向 const 对象的 const 指针 (类型为time，this就是 const time *const this 类型的指针) 

五：static 成员
	有属于整个类的成员变量，这种成员变量就叫 static 成员变量。

	特点:不属于某个对象，属于整个类，我们一旦在某个对象中修改了这个成员变量的值，在其他对象中直接能够看到修改的结果。
		 这种成员变量只有一个副本，对于这种成员变量的引用，我们用的是     类名::成员变量名
		 成员函数前面也可以加 static 构成，静态成员函数。属于整个类的成员函数。调用时      类名::成员函数名

	如何定义成员变量(分配内存)？
		我们一般会在某一个.cpp源文件的开头来定义这个静态成员变量。这样就能够保证在调用任何函数之前这个静态成员变量已经被成功初始化。
	
	void func(){
		static int abc = 5;    局部静态变量
	}
	static int g_abc = 15;    也保存在静态存储区。限制该全局量只能够用在本文件中。

引用静态成员变量
	cout << time::mystatic << endl;

	time mytime1;
	mytime1.mystatic = 40;
	time mytime2;

	cout << time::mystatic <<endl;
	cout << mytime1.mystatic << endl;
	cout << mytime2.mystatic << endl;		值都为40


	time::mystatic(12);
	mytime1.mstafunc(15);
	mytime2.mstafunc(78);