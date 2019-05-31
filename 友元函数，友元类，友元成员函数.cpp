一：友元函数。	这是个函数
	class Men{   
		private:
			void funcmen() const
			{
				std::cout << "test" << std::endl;
			}

			因为友函数不属于类成员，所以友元函数声明不受 public,protected,private的限制。
			friend void fuc(const Men &tempmen){   声明为友元函数；

			}
					
		};
		void func(const Men &tempmen){
			tempmen.funcmen();
		}
		
		只要让函数func成为类Men的友元函数，那么func这个函数就能够访问类Men的所有成员(成员变量，成员函数)，private,public,protected。
		Men men;
		func(men)

		总结：友元函数 func(){}：是个函数，通过声明为某个类Men的友元函数，它就能访问这个类(Men)的所有成员，包括，private,public,protected。

二：友元类：类可以把其他的类定义成有原类。如果 "你是" "我的" 友元类，那么就可以在"你的"成员函数中访问"我的"所有成员 包括，private,public,protected。
	
	修改类A，让类C成为类A的朋友
	class A{
	private:
		int data;

	friend class C;  这就是友元类的声明，虽然此时类C没有定义，但是系统不会报错
	};

	class C{
	public:
		void callCAF(int  x,A &a){
			A.data = x;   正常情况下这个不行
			std::cout << a.data << std::endl;
		}
		void callCAF(int  x,A &a){
			a.data;
		}
	};

	A a;
	C c;
	c.callCAF(3,a);   返回结果是 3

	注意：每个类都负责控制自己的友元类和友元函数，所以：
	(1)友元福安息不能被继承
	(2)友元关系是单向的，比如上边类C是类A的友元类，但这并不表示类A是类C的友元类。   
	(3)友元关系没有传递性的，比如B是类A 的友元类，类C是类B的友元类，这并不代表类C是类A的友元类。

三：友元成员函数
	写这种友元成员函数，必须要注意代码组织结构，因为这里边有声明和定义这种依赖关系在里边。

	class A{
		friend void C::callCAF(int  x,A &a);  该函数是友元成员函数的声明
	private:
		int data;
	};

	class C{
	public:
		void callCAF(int  x,A &a){		只有public的函数才能成为其他类的友元
			a.data =x;
			std::cout << a.data << std::endl;
		}

	};

	A a;
	C c;
	c.callCAF(3,a);

	总结：friend：
		优点：
			允许在特定情况下某些非成员函数访问类的private,protected成员，从而提出友元这么一个概念，使访问private,protected成员更灵活。

		缺点：这也就破坏了类的封装性，降低了类的可靠性和可维护性。