#include<iostream>

using namespace std;
//����1
class Base1
{
public:
	virtual void f()
	{
		cout << "base1::f()" << endl;
	}
	virtual void g()
	{
		cout << "base1::g()" << endl;
	}
};
//����2
class Base2
{
public:
	virtual void h()
	{
		cout << "base2::h()" << endl;
	}
	virtual void i()
	{
		cout << "base2::i()" << endl;
	}
};

//����
class Derived : public Base1, public Base2
{
public:
	virtual void f()  //���Ǹ���1���麯��
	{
		cout << "derived::f()" << endl;
	}
	virtual void i() //���Ǹ���2���麯��
	{
		cout << "derived::i()" << endl;
	}
	//����д�����Լ����麯��
	virtual void mh()
	{
		cout << "derived::mh()" << endl;
	}
	virtual void mi()
	{
		cout << "derived::mi()" << endl;
	}
	virtual void mj()
	{
		cout << "derived::mj()" << endl;
	}
};
int main()
{
	//���Ľ�  ���ؼ̳��麯�������
	//���ؼ̳�
	cout << sizeof(Base1) << endl;
	cout << sizeof(Base2) << endl;
	cout << sizeof(Derived) << endl;   //8�ֽڣ��������麯����ָ��
	cout << "--------------" << endl;
	Derived ins;
	Base1& b1 = ins;   //��̬
	Base2& b2 = ins;   //��̬
	Derived& d = ins;

	typedef void(*Func)(void);
	long* pderived1 = (long*)(&ins);
	long* vptr1 = (long*)(*pderived1);  //ȡ��һ���麯����ָ��

	long* pderived2 = pderived1 +1;  //����4�ֽ�
	long* vptr2 = (long*)(*pderived2);  //ȡ�ڶ����麯����ָ��

	Func f1 = (Func)vptr1[0];//f1 = 0x00a11221 {wangyi.exe!Derived::f(void)}
	Func f2 = (Func)vptr1[1];//f2 = 0x00a113ac {wangyi.exe!Base1::g(void)}
	Func f3 = (Func)vptr1[2];//f3 = 0x00a1116d {wangyi.exe!Derived::mh(void)}
	Func f4 = (Func)vptr1[3];//f4 = 0x00a1143d {wangyi.exe!Derived::mi(void)}
	Func f5 = (Func)vptr1[4];//f5 = 0x00a1132a {wangyi.exe!Derived::mj(void)}
	Func f6 = (Func)vptr1[5];//������
	Func f7 = (Func)vptr1[6];
	Func f8 = (Func)vptr1[7];

	Func f11 = (Func)vptr2[0];//f11 = 0x00a110d2 {wangyi.exe!Base2::h(void)}
	Func f22 = (Func)vptr2[1];//f22 = 0x00a1112c {wangyi.exe!Derived::i(void)}
	Func f33 = (Func)vptr2[2];//������
	Func f44 = (Func)vptr2[3];

	b1.f();
	b2.i();
	d.f();
	d.i();
	d.mh();

	cout << "--------------" << endl;
	f1();
	f2();
	f3();
	f4();
	f5();

	cout << "--------------" << endl;
	f11();
	f22();

	//˵��
	//(1)һ����������������ж���������ж���麯����ָ��(ע���������麯����ָ�룬�����������麯����)
	//�ڶ�̳��У���Ӧ���������vptr���̳�˳�����η���������ڴ�ռ��У����������һ�����๲��һ��vptr(�ڶ����������Լ���vptr)

	//(2)�������ins�������麯����ָ�룬vptr1,vptr2
	//(3)��Derived�������麯������Ϊ���̳�����������
	//(4)����͵�һ�����๲��һ��vptr(��Ϊvptrָ��һ���麯��������Ҳ����˵����͵�һ�����๲��һ���麯����vtbl)
			//��Ϊ����ע�⵽����Derived���麯����1�����5����������g()������base1��ߵĺ���
	//(5)�����е��麯�������˸����е�ͬ���麯��������derived::f(),derived::i();
	return 0;

}