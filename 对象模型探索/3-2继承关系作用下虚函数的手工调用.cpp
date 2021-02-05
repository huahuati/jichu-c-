#include<iostream>
using namespace std;

//����
class Base
{
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
};

class Derive :public Base
{
	virtual void g() { cout << "Dervie::g()" << endl; }
};

int main() {
	//�̳й�ϵ�������麯�����ֹ�����
	
	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << "--------------------------" << endl;
	Derive* d = new Derive();   //������ָ��
	long* pvptr = (long*)d;    //ָ������ָ��dת����long *���͡�
	long* vptr = (long*)(*pvptr);   //(*pvptr)��ʾpvptrָ��Ķ���Ҳ����Derive����Derive������4�ֽڵġ���������麯����ָ���ַ��

	for (int i = 0; i <= 4; i++)   //ѭ��5��
		printf("vptr[%d] = 0x:%p\n", i, vptr[i]);

	cout << "--------------------------" << endl;
	typedef void(*Func)(void);   //����һ������ָ������
	Func f = (Func)vptr[0];   //f���Ǻ���ָ�������vptr[0]��ָ���һ���麯���ġ�
	Func g = (Func)vptr[1];
	Func h = (Func)vptr[2]; 
	Func i = (Func)vptr[3]; 
	Func j = (Func)vptr[4]; 

	f();
	g();
	h();
	//i(), j();//�ᱨ�쳣
	cout << "--------------------------" << endl;
	Base* dpar = new Base();
	long* pvptrpar = (long*)dpar;
	long* vptrpar = (long*)(*pvptrpar);

	for (int i = 0; i <= 4; i++)  //ѭ��5�Σ�
		printf("vptr[%d] = 0x:%p\n", i, vptr[i]);

	Func fpar = (Func)vptrpar[0];   //f���Ǻ���ָ�������vptr[0]��ָ���һ���麯���ġ�
	Func gpar = (Func)vptrpar[1];
	Func hpar = (Func)vptrpar[2];

	cout << "--------------------------" << endl;
	fpar();
	gpar();
	hpar();
	return 0;
}