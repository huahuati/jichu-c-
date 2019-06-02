一：RTTI是什么(Run Time Type Identification):运行时类型识别。
	通过运行时类型识别，程序能够使用基类的指针或者引用来检查这些指针或者引用所指的对象的实际派生类型。

	Human *phuamn = new Men;
	Human &q = *phuman;			*phuman表示指针phuman所指向的对象。		

	RTTI我们可以把这种称呼看成是一种系统提供给我们的一种能力，或者一种功能。这种功能或者能力是通过2个运算符来体现: 
		(1)dynamic_cast运算符：能够将基类的指针或者引用安全的转换为派生类的指针或者引用；
		(2)typeid运算符：返回指针或者引用所指对象的实际类型。

	补充：要想让RTTI的两个运算符能够正常工作，那么基类中必须至少要有一个虚函数，不然这两个运算符工作的结果就可能跟我们预测的结果不一样。
	因为只有虚函数的存在，这两个运算符才会使用指针所绑定的对象的动态类型(你new的类型)

二：dynamic_cast运算符：如果该运算符能够转换成功，说明这个指针实际上是要转换到的那个类型。这个运算符能帮我们做安全检查。
	class Human{
				public:
					Human(){
						std::cout << "执行了父类的构造函数" << std::endl;
					}
				public:
					virtual void eat(){
						std::cout << "人类吃各种粮食"<< std::endl;
		};
	class Men :public Human{   
		public:
			void testfunc(){

				std::cout << "testfunc" << std::endl;
			}		
		};


	Human *phuamn = new Men;
	Men *p = (Men *)(phuamn);		用c语言风格的强制类型转换，硬把指针转换成 Men*;
	p->testfunc();					能够正常的调用Men类的成员函数testfunc();

	Human *phuman = new Men;
	Men *pmen = dynamic_cast<Men *>(phuman);		
	if(pmen != nullptr){
		cout << "phuman实际上是一个Men类型" << endl;
		在这里操作类Men里边的成员函数，成员变量都能够操作并且安全的操作
	}
	else{
		转换失败
		cout << "phuman不是一个Men类型" << endl;

	}

	对于引用，如果用dynamic_cast转换失败，则系统会抛出一个std::bad_cast异常。

	Human *phuamn = new Men;  
	Human &q = *phuman;			这就是引用
	try{
		Men &menbm = dynamic_cast<Men &>(q);		转换不成功，则流程直接进入到catch里边去，如果转换成功，流程继续往下走。
		cout << "phman实际上是一个Men类型" << endl;
		在这里调用类Men的成员函数都是安全的。
		menbm.testfunc();
	}
	catch(std::bad_cast){
		cout <<"phuman实际不是一个Men类型" << endl;
	}

三：typeid运算符
	typeid(类型[指针/引用])；也可能typeid(表达式)
	拿到对象类型信息。typeid就会返回一个常量对象的引用这个常量对象，是一个标准库 type_info(类/类型)。
	Human *phuman = new Men;
	Human &q = *phuman;
	cout << typeid(*phuman).name() << endl;    
	cout << typeid(q).name << endl;			结果为  class Men

	char a[10] = {5,1};
	int b = 120;
	cout << typeid(a).name() << endl;			char [10]
	cout << typeid(b).name() << endl;			int
	cout << typeid(19.6).name() << endl;		double
	cout << typeid("asd").name() << endl;		char const[4]

	typeid主要是为了比较两个指正是否指向同一种类型的对象。
	(1)两个指针定义的类型相同(Human),不管它们new的是什么,typeid都相等。
	该例不太符合我们的期盼和要求。

	Human *phuamn = new Men;
	Human *phuman2 = new Women;
	if(typeid(phuman) == typeid(phuman2)){
		cout << "phuamn和phuman2使用一种类型[看指针定义]" << endl;
	}

	比较对象时，看的是new出来的是哪个对象或者该指针指向的是哪个对象，和定义该指针时定义的类型没有关系。
	Human *phuamn = new Men;;
	Men *phuamn2 = new Men;
	Human *phuman3 = phuman2;
	if(typeid(*phuman) == typeid(*phuamn2)){
		cout << "phuman和phuman2指向的对象类型相同"
	}
	if(typeid(*phuman2) == typeid(*phuamn3)){
		cout << "phuamn2和phuman3指向的对象类型相同" << endl;
	}

	Human *phuman = new Men;		成立
	if(typeid(*phuamn) == typeid(Men)){
		cout << "phuamn指向Men" << endl;
	}

	注意：基类必须要有虚函数，否则上边的条件不成立。
	切记：只有当基类有虚函数是，编译器才会对typeid()中的表达式求值，否则如果某个类型不含有虚函数，
	则typeid()返回的是表达式的今天类型(定义时的类型)，既然是定义的类型，编译器就不需要对表达式求值也能知道静态类型的值。

四：type_info类
	typeid就会返回一个 常量对象的引用，这个常量对象是一个标准库类型 type_info(类/类类型)
	(1) .name :名字:返回一个c风格字符串
			Human *phuamn = new Men;
			const std:type_info &tp = typeid(*phuman);
			cout << tp.name() << endl;  class Men

	(2)== ,!= 

			Human *phuamn2= new Men;
			const std:type_info &tp2 = typeid(*phuman);

			if(tp == tp2){
				cout << "类型相同"  << endl;
			}
			Human *phuamn3= new Women;
			const std:type_info &tp3 = typeid(*phuman3);
			if(tp != tp3){
				cout << "类型不相同" << endl;
			}

		注意：必须要有虚函数

五：RTTI与虚函数表

	c++如果类里含有虚函数。编译器就会对该类产生一个虚函数表。
	虚函数表里有很多项，每一项都是一个指针。每个指针指向的是这个类里的各个虚函数的入口地址。
	虚函数表项里，第一个表象很特殊，它指向的不是虚函数的入口地址，他指向实际上是我们这个类所关联的type_info对象。

	Human *phuamn = new Men;
	const type_info &tp = typeid(*phuman);

	phuman对象里有一个我们看不见的指针，这个指针指向的是这个对象所在的类，Men里的虚函数表