#include<iostream>
using namespace std;

class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	virtual ~Base() {}

};

class Derive :public Base{
public:
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc() {} //只属于Derive的函数
	virtual ~Derive() {}
};
int main()
{
//一:RTTI(运行时类型识别)简单回顾
	Base* pb = new Derive();
	pb->g();

	Derive myderive;
	Base& yb = myderive;
	yb.g();

	//c++运行时类型识别RTTI，要求父类中必须至少有一个虚函数；如果父类中没有虚函数，那么得到RTTI就不准确。
	//RTTI就可以在执行期间查询一个多态指针，或者多态引用的信息了；	
	//RTTI能力靠typeid和dynamic_cast运算符来体现；
	cout << typeid(*pb).name() << endl;
	cout << typeid(yb).name() << endl;

	Derive* pderive = dynamic_cast<Derive*>(pb);
	if (pderive != NULL)
	{
		cout << "pb实际是一个Derive类型" << endl;
		pderive->myselffunc();   //调用自己专属函数
	}

//二：RTTI实现原理
	//typeid返回的是一个常量对象引用，这个常量对象的类型一般是type_info(类);
	const std::type_info& tp = typeid(*pb);
	Base* pb2 = new Derive();
	const std::type_info& tp2 = typeid(*pb2);
	if (tp == tp2)
	{
		cout << "类型相同 " << endl;
	}


	//其他用法， 静态类型，不属于多态类型
	cout << typeid(int).name() << endl;
	cout << typeid(Base).name()<< endl;
	cout << typeid(Derive).name() << endl;

	Derive* pa3 = new Derive();
	cout << typeid(pa3).name();

	cout << "分界线------" << endl;
	//动态类型
	Base* pbb = new Derive();
	Derive myderive2;
	Base& ybb = myderive2;
	cout << typeid(*pbb).name() << endl;
	cout << typeid(ybb).name() << endl;
	Base* ppbb = new Derive();
	const std::type_info& tp3 = typeid(*ppbb);

	//RTTI的测试能力跟基类中是否存在虚函数表有关系，如果基类中没有虚函数，也就不存在基类的虚函数，RTTI就无法得到正确结果。
	cout << "分界线------" << endl;
	Base* pb3 = new Derive();
	const std::type_info& tp4 = typeid(*pb3);
	printf("pt3地址为:%p\n", &tp4);
	long* pvptr = (long*)pb3;
	long* vptr = (long*)(*pvptr);
	printf("虚函数表首地址为:%p\n", vptr);
	printf("虚函数表首地址,地址之前一个地址为:%p\n", vptr-1);  //这里的 -1 实际上是网上走了4个字节

	long* ptrttiinfo = (long*)(*(vptr - 1));
	ptrttiinfo += 3;  //跳过12字节
	long* ptypeinfoaddr = (long*)(*ptrttiinfo);
	const std::type_info* ptypeinfoaddrearl = (const std::type_info*)ptypeinfoaddr;
	printf("ptypeinfoaddrearl地址为:%p\n", ptypeinfoaddrearl);

	cout << ptypeinfoaddrearl->name() << endl;

//三:vptr,vtbl,rtti的type_info信息构造时机
	//rtti的type_info信息::编译后就存在了；写到了可执行文件中

	//总结一下:
	//RTTI信息取得一般都是与虚函数表之前(往上走四个字节)为突破口

	return 0;
}