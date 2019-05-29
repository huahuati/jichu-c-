一：派生类概念

	类之间有一种层次关系，有父类，有孩子类。

	车这个类，当成父类(也叫基类，超类)，派生出 卡车，轿车，他们属于孩子类(子类/派生类)
	继承：有父亲类，有孩子类，构成了层次关系。继承这种概念，是面向对象程序设计的核心思想之一。
	这种继承，就是我们要先定义一个父类。父类中定义一些公用的成员变量，成员函数。
	我们通过继承父类来构建新的类：子类。所以写代码时，只需写和子类相关的一些内容即可。
	子类一般会比父类更加庞大

	定义基类：

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
		};类定义/类声明一定要加; 

	定义Human的子类：

		class Men :public Human{   表示Men 是 Human的子类
				public:
					Men(){
						std::cout << "执行了子类的构造函数" << std::endl;
						funcpro();
						Human::samenamefuc();  		调用父类无参的构造函数
						Human::samenamefuc(12); 	调用父类有参的构造函数
					}
				public:
					void samenamefuc(int){
						std::cout<< "执行了子类public::samenamefuc(int)的函数" << std::endl;
					}
				public:
					using Human::samenamefuc;  
		};

	class Men :public Human。
	class 子类名 ： 继承方式，父类名
	继承方式(访问等级/访问权限): public/protected/private;


二:派生类对象定义时调用构造函数的顺序

	Men men;

	当定义子类对象时，调用父类和子类的构造函数，且 父类的构造函数体先执行，子类的构造函数体后执行。

三：public ,protected,private

	总结一下：三种访问权限

		public：可以被任意实体所访问。
		protected:只允许本类或者子类的成员函数来访问。
		private：只允许本类的成员函数访问。

	三种继承访问：
		
		public 继承
		protected 继承
		private 继承

	基类中的访问权限							子类继承基类的继承方式					子类得到的访问权限

	public  							public 							public 
	protected 							public 							protected 
	private 							public 							子类无权访问

	public 								protected 						protected 
	protected 							protected 						protected 
	private 							protected 						子类无权访问

	public 								private 						private 
	protected 							private 						private 
	private 							private 						子类无权访问

		总结： 
		(1)子类public继承父类不改变父类的访问权限
		(2)protected继承将父类中public成员变为子类的protected成员
		(3)private继承使得父类所有成员在子类中的访问权限变为private
		(4)父类中的private成员不受继承方式的影响，子类永远无权访问。
		(5)对于父类来讲，尤其是父类的成员函数，如果你不想让外边访问，就设置为private； 
		   如果你想让自己的子类能够访问，就设置为protected，如果你想公开，就设置为public。


函数遮蔽
	
	子类中如果有一个同名函数，那么父类中，不管有几个同名函数，子类中都无法访问到。
	如果我们确实想调用父类中的同名函数怎么办？
		(1)在子类的成员函数中，用父类 "父类::函数名"强制调用父类函数。
		(2)using : using namespace 
			在 using c++11 中让父类同名函数在子类中可见。
			通过 using 这个关键字，让父类的同名函数在子类中可见(让父类同名函数在子类中一重载的方式来使用)
			说明：
				(1)using Human::samenamefuc;  只能指定函数名，则凡是基类中 public，protected的 samenamefuc。在子类中都可见。
				   无法让一部分可见(函数重载全部可见)
				(2)using 引入的主要目的是用来实现在子类中调用父类的重载版本。该函数在父类中的参数和类型不同。
	Men men;
	men.samenamefuc(12);   执行结果：执行了子类public::samenamefuc(int)的函数
	men.samenamefuc();		
