#include<iostream>
using namespace std;

namespace _nmspl
{
	//һ������Ĺ���˳��
	//	A()
	//		B()
	//			C()
	//�����麯���ļ����۲�
	//�麯��ָ��ĸ�ֵ����
	//	vptr = A::vftable
	//		vptr = B::vftable
	//			vptr = C::vftable
	//	�ɴ˿��Եó�������C��vptrָ�����ڲ��ϵر���д�����ֵΪ C::vftable�麯������׵�ַ
	//ǧ��Ҫ�ڹ��캯���У�ʹ������memcpy����ֱ�Ӳ������ֶΣ����޸��麯����ָ���ֵ�����򣬵����麯��ʱ�Ϳ������ϵͳ������	

	//�������캯�����麯���ĵ���
	//ĳ����Ĺ��캯�� �� ����һ���麯������ô�ߵĲ����麯��������ֱ�ӵ���
	class A
	{
	public:
		A()
		{
			printf("A this = %p\n", this);
			cout << "A::A()" << endl;
		}
		virtual ~A() {}
		virtual void myvirtual() {}
		virtual void myvirtua2() {}
	};
	class B : public A
	{
	public:
		B()
		{
			printf("B this = %p\n", this);
			cout << "B::B()" << endl;
		}
		virtual ~B() {}
		virtual void myvirtual() {}
		virtual void myvirtua2() {}
	};
	class C : public B
	{
	public:
		C():m_c(11)
		{
			myvirtual();   //���캯���У�ֱ�ӵ����麯�����������麯����(��̬���÷�ʽ)
			printf("C this = %p\n", this);
			cout << "C::C()" << endl;
		}
		virtual ~C() {}
		virtual void myvirtual() { myvirtua2(); //������麯����
								  }
		virtual void myvirtua2() {}
		int m_c;
	};

	void func()
	{
		C cobj;
		C* myobj = new C();
		myobj->myvirtual();  //����ʵ���ϵĶ�̬��
	}
}

int main()
{
	_nmspl::func();
	return 0;
}