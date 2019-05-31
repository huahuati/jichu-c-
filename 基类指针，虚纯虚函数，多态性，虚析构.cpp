	class Human{
				public:
					Human(){
						std::cout << "执行了父类的构造函数" << std::endl;
					}
					Human(int abc){
						std::cout << "执行了一个参数的构造函数" << std::endl;
					}
				public:
					
					int m_Age;
					char m_Name[100];
					void funcpub{
					std::cout<< "执行了public的函数" << std::endl;
				}
				public:
					void samenamefuc(){
						std::cout<< "执行了public::samenamefuc的函数" << std::endl;
					}
					void samenamefuc(int  ){
						std::cout<< "执行了public::samenamefuc(int)的函数" << std::endl;

					}

				protected:

					int m_prol;
					void funcpro(){
						std::<< "执行了protected的函数" << std::end;
					}

				private:
					int m_privl;
					void funcpriv(){}
				public:
					void funchuman(){};
				public:

					声明成虚函数
					virtual void eat(){
						std::cout << "人类吃各种粮食"<< std::endl;
					}
				public:
					virtual ~Human(){
						std::cout << "执行了Human的析构函数" << std::endl;
					}
		};

		class Men :public Human{   
				public:
					Men(){
						std::cout << "执行了子类的构造函数" << std::endl;
						funcpro();
						Human::samenamefuc();  		
						Human::samenamefuc(12); 	
					}
				public:
					void samenamefuc(int){
						std::cout<< "执行了子类public::samenamefuc(int)的函数" << std::endl;
					}
				public:
					using Human::samenamefuc;  
				public:
					void funcmen(){};
				public:
					void eat(){
						std::cout << "男人喜欢吃米饭"<< std::endl;
					}
				~Men(){
					std::cout << "执行了Men的析构函数" << std::endl;
				}
		};

一：基类指针,派生类指针：
	
	Human * phuman = new Human();
	Men *pmen = new Men;

	新玩法：父类指针可以new一个子类对象。父类指针很强大，很牛逼。
	Human *phuman = new Men;   这个是可以的
	Men *pmen = new Human;     这个不可以

	phuman->funchuman();    父类类型指针，可以调用父类的成员函数
	phuman->funcmen();		不可以调用，虽然new子类对象，但是你是父类指针，无法调用子类成员函数。

	既然父类指针没有办法调用子类的成员函数，那么你为什么还让父类指针new一个子类对象呢？ 有什么用处？

二：虚函数：

	class Women : public Human{
			public:
				Women(){
					std::cout << "执行了women的构造函数" <<std::endl;
				}
			public:
				void eat(){
						std::cout << "女人喜欢吃面食"<< std::endl;
					}
			public:
				~Women(){
					std::cout << "执行了Women的析构函数" << std::endl;
				}

	}
	Human *phuman = new Men;
	phuman->eat();   调用的父类的eat函数。因为phuman是父类指针。

	那么如何调用 Men 和 Women 中的eat() 函数

	问题：有没有一个解决方法，使我们只定义一个对象指针，就能够调用父类，以及各个子类的同名函数?
	有：这个对象指针，他的类型必须是父类类型。
	
	如果想通过一个父类指针调用父类，子类中的同名函数的话，对这个函数也是有要求的：
		在父类中，eat函数声明之前必须要加 virtual 声明 eat() 函数成虚函数。子类中加不加无所谓(建议在子类中也加virtual)。
		一旦某个函数(在基类)被声明成了虚函数，那么所有派生类(子类)中他都是虚函数。
	
	Human *phuman = new Men;
	//phuman->eat();  没声明虚函数的时候，调用的是父类的eat()
	phuman->eat();		调用的是Men类的 eat()函数;
	phuman->Human::eat();   这样写是可以调用父类的eat 函数的。
	delete phuman;

	phuman = new Women;	调用的是Women类的 eat()函数;	
	phuman->eat();
	delete phuman;

	phuman = new Human;	调用的是Human类的 eat()函数;	
	phuman->eat();
	delete phuman;

	为了避免你在子类中写错虚函数，在c++11中，你可以在函数声明这里增加一个 override 关键字，这个关键字用在用在 "子类",虚函数专用。
	
	override就是用来说明派生类中的虚函数，你用了这个关键字之后，编译器就会认为你这个eat是覆盖了父类中的同名函数
	(只有虚函数才存在子类可以覆盖父类中同名函数的问题)，那么编译器就会在父类中找同名同参的虚函数，如果没有找到，
	编译器就会报错，这样，如果你不小心在子类中把虚函数写错了名字，写错了参数，编译器就能够帮助你纠错。

			void eat( int acs) override;

	final:final 也是虚函数专用，使用在"父类"，如果我们在父类的函数声明中加了final，那么任何尝试覆盖该函数的操作都将引发错误。

			virtual void eat() final;

	总结：调用虚函数执行的是"动态绑定"。动态：表示的就是在程序运行的时候才能知道调用了哪个子类的 eat() 虚函数。
	动态的绑定到Men上去，帮到Women，取决于 new 的是 Men 还是 Women。

	动态绑定：运行的时候才决定你的 phuman对象绑定到哪个 eat()函数上运行;

三：多态性
	多态性只是针对虚函数来说的。
	随着虚函数的提出，面向对象编程里边有一个概念"多态性"，就浮出水面。

	多态性:体现在具有继承关系的父类和子类之间，子类重新定义(重写)父类的成员函数eat(),同时父类把这个eat()函数声明成了virtual虚函数。
	通过父类的指针，只有到了程序运行时期，找到动态绑定到父类指针的对象，这个对象它有可能是某个子类对象，也可能是父类对象，
	然后系统内部实际上是要查一个虚函数表，找到函数 eat() 的入口地址，从而调用父类或者子类的eat()函数，这就是运行时期的多态性。

四：纯虚函数
	
	纯虚函数是在基类中声明的虚函数，但是他在基类中没有定义，但是要求任何派生类都要定义该虚函数自己的实现方法。
	基类中实现纯虚函数的方法是在原函数原型后面增加 = 0

		virtual void Human::eat2() = 0;
	
	一旦一个类中有纯虚函数了，那么你就不能在生成这个类的对象了。这个类就成为了"抽象类"
	抽象类 不能用来生成对象，主要目的是用来统一管理子类对象。

	Human human; 不合法
	Human *phuman = new Human  不合法

	注意：
	(1)函数纯虚函数的类叫 抽象类，不能用来生成该类对象，主要用于当做基类来生成子类用的。
	(2)子类中必须要实现该基类中定义的纯虚函数。

			virtual void Men::eat2(){
				std::cout << "Men：：eat2" << std::endl;
			}

五：基类的析构函数一般写成虚函数(虚析构函数)

	当 ~Human()析构构函数不是虚函数的时候：

			Human *phuman = new Men;
			delete phuman;    没有执行子类的析构函数。

	结论：用基类指针 new 子类的对象，在 delete 的回收系统不会调用派生类的析构函数。这就有问题了。

	如何解决：
			把父类的析构函数写成虚函数。
	注意：在public继承中，基类对派生类及其对象的操作，只能影响到那些从基类继承下来的成员，如果想要用基类对非继承成员进行操作。
	则要把基类的这个函数定义为虚函数，析构函数也应该如此。

	另外就是基类中析构函数的虚函数的虚属性也会被继承给子类，这样的话子类中的析构函数也就自然而然的成为了虚函数，。

	delete phuman的时候，肯定是要调用父类的析构函数，但在父类析构函数中它要是想调用子类Men的析构函数，那么
	Human 这个类中的析构函数就要声明为 virtual的，也就是说c++中为了获得运行时的多态行为，所调用的成员函数必须得是virtual的。

	结论：

		如果一个类，想要做基类，我们务必要把这个类的析构函数写成virtual析构函数。
		只要基类的析构函数式虚函数，就能够保证我们delete基类指针时能够运行正确的析构函数。

		普通类我们可以不写析构函数，但如果是基类，就必须写一个虚构函数，而且这个析构函数还必须是虚(virtual)析构函数。
		虚函数会增加内存的开销，类里面定义虚函数，编译器就会给这个类增加虚函数表，在这个表里存放虚函数的指针。- 