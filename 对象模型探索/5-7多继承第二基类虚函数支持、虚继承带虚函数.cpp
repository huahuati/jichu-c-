#include<iostream>
using namespace std;
class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	virtual ~Base() {}
	virtual Base* clone() const
	{
		return new Base();
	}
};

class Base2
{
public:
	virtual void hBase2() {
		{ cout << "Base2::hBase2()" << endl; }
	}
	virtual ~Base2()
	{}
	virtual Base2* clone() const
	{
		return new Base2();
	}
};


class Derive :public Base,public Base2 {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc(){} //ֻ����Derive�ĺ���
	virtual ~Derive(){}
	virtual Derive* clone() const
	{
		return new Derive();
	}
};

class BASE
{
public:
	virtual void f() {}
	virtual ~BASE() {}
	int M_BASEi;
};

class DERIVE : public virtual BASE
{
public:
	virtual ~DERIVE() {}
	int M_DERIVEI;
};
int main() {
	//һ�����ؼ̳еڶ�������麯��֧�ֵ�Ӱ��(thisָ���������)
	//����̳м������࣬������м����麯����

	//���ؼ̳��£��м���������ڶ������ߺ����Ļ������麯����֧�ֲ���Ӱ��
	//thisָ�������������Ŀ���Ǹ�ʲô?
	//thisָ�������Ŀ�ľ����ö���ָ����ȷ��ָ������׵�ַ���Ӷ�����ȷ�ĵ��ö���ĳ�Ա��������˵��ȷ�����ݳ�Ա�洢λ��

	//a)ͨ��ָ��ڶ��������ָ����ü̳�����麯����
	Base2* pb2 = new Derive();
	delete pb2;   //���ü̳��������������

	//b)һ��ָ���������ָ�룬���õڶ��������е��麯��
	Derive* pd3 = new Derive;
	pd3->hBase2();

	//c)�����麯���ķ���ֵ���������仯
	Base2* pb1 = new Derive();  //pb1ָ�����Base2�ֶ�����׵�ַ
	Base2* pb2 = pb1->clone(); //Derive::clone();
					//ִ��cloneʱ��pb1���Ȼ��������ָ��Derive������׵�ַ���������õ���Derive�汾��clone()
		
	//������̳��µ��麯��
	cout << sizeof(DERIVE) << endl;  //16�ֽ�
	DERIVE dobj;			//1-4������ָ��
	dobj.M_BASEi = 2;	   //13-16�ֽ�
	dobj.M_DERIVEI = 5;		//5-8�ֽ�

	DERIVE* pdobj = new DERIVE();
	pdobj->f();			//9-12�ֽ��麯����ָ��

	DERIVE* pderive = new DERIVE();
	BASE* pbase2 = (BASE*)pderive;
	pbase2->M_BASEi = 7;
	return 0;
}