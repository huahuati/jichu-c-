#include<iostream>
using namespace std;
class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
};

class Derive :public Base {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc(){} //ֻ����Derive�ĺ���
};
int main() {

	//һ����һ�̳��µ��麯��
	//Derive myderive;
	//Derive* pmyderive = &myderive;
	//pmyderive->f();
	//pmyderive->g();
	//pmyderive->h();
	//pmyderive->i();


	Base* pb = new Derive(); //����ָ��ָ��һ���������
	pb->g();
	//�������ӽ�
	//(*pb->vptr[1](pb));
	Derive myderive;
	Base& yb = myderive;  //��������һ���������
	yb.g();
	//����Ψһ��Ҫ��ִ���ڼ�֪���Ķ�������ͨ���ĸ��麯�����������麯��(����Ļ�������)

	//�����ع˺�һЩСʵ��
	//�麯����ַ:�����ڼ䣬д���˿�ִ���ļ��У��������Ѿ�����������
	//vptr�����ڼ�������������ڹ��캯���в����˸�vptr��ֵ�Ĵ��롣����������ʱ����ΪҪִ�ж���Ĺ��캯������ʱvptr�ͱ���ֵ��

	Derive a1;
	Derive a2;
	Derive* pa3 = new Derive();   //�麯�����ַ��ͬ

	Base b1;
	return 0;
}