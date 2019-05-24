一 ： 类使我们自己定义的数据类型(新类型）

		设计类是要考虑的角度:
		(1)站在设计和实现者的角度来考虑
		(2)站在使用者的角度来考虑。
		(3)父类，子类

二：类基础
	
	(1)一个类就是一个用户自己定义的数据类型，我么你可以把类想象成一个命名空间，包着一堆东西(成员函数，成员变量)
	(2)一个类的构成:成员变量，成员函数和许多特殊的成员函数
	(3)我们访问类成员时，如果是类的对象，我们就使用		对象名.成员名  来访问成员。
			如果是指向对象的指针，我们就用    指针名->成员名   来访问成员。

		class student {
		public:
				int number;
				char name[10]; 
		};

		student someone;     定义类的对象
		someone.number = 1000

		student *psoneone = &someone;
		psomeone->number = 1005;

		cout << someone.number << endl;

	(4)

	   public成员提供类的接口，暴露给外界，供外界调用。
	   private成员提供各种实现类功能的细节方法，但是不暴露给使用者，外界无法使用private成员

	(5)struct是成员默认public的class。	struct A{.........}
	(6)class 成员默认是private(私有)。		private A{.........}

		struct A {......} 等价于
		class A {public: ......}

三：成员函数
	
	class time{
	public:
		int hour;
		int minute;
		int second;

		void initTime(int tmphour,int tmpmin, int tmpsec){
			hour = tmphour;		成员函数中，我么可以直接使用成员变量名
								哪个对象调用的该成员函数，这些成员变量就属于哪个对象，
								类成员函数知道哪个对象调用自己
			minute = tmpmin;
			second = tmpsec;
		}
	};

	time = Mytime(11,14,5);
	cout << Mytime.hour << endl;
	cout << Mytime.minute << endl;
	cout << Mytime.second << endl;

四：对象的拷贝
	
	对象本身是可以拷贝的。
	默认情况下，这种类对象的拷贝，是每个成员变量逐个拷贝。
	如果在类time中我们要定义适当的定义  "赋值运算符" 就能控制对象的这种拷贝行为。

	time mytime ;
	mytime.hour = 12;		
	mytime.minute = 15;
	mytime.second = 40;

	time mytime2 = mytime;
	time mytime3(mytime);
	time mytime4{mytime};
	time mytime5 = {mytime};

五：私有成员

	class time{
	private:
		int millisecond
	public:
		int hour;
		int minute;
		int second;
	}

	time mytime;
	mytiem.millisecond    私有的不能直接.私有成员变量名

