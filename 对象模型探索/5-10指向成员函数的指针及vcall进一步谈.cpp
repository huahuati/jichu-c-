#include<iostream>
using namespace std;

namespace _nmsp1

{
	//һ��ָ���Ա������ָ��
	//��Ա������ַ������ʱ��ȷ���õġ����ǣ����ó�Ա��������Ҫͨ�����������õġ�
	//���ǳ���(�Ǿ�̬)��Ա������Ҫ����ã�����Ҫһ����������������

	class A {

	public:
		void myfunc1(int tempvalue1)
		{
			cout << "tempvalue1 = " << tempvalue1 << endl;
		}
		void myfunc2(int tempvalue2)
		{
			cout << "tempvalue2 = " << tempvalue2 << endl;
		}

		static void mysfunc(int tempvalue)
		{
			cout << "A::mysfunc()��̬��Ա����--tempvalue = " << tempvalue << endl;
		}
	};
	void func()
	{
		A mya;
		void (A:: * pmypoint)(int tempvalue) = &A::myfunc1;   //����һ����Ա����ָ�벢����ֵ��
		pmypoint = &A::myfunc2;   //����Ա����ָ�븳ֵ

		(mya.*pmypoint)(15);    //ͨ����Ա����ָ�������ó�Ա����������ͨ������Ľ�����ܵ���

		A* pmya = new A();
		(pmya->*pmypoint)(20);   //�ö���ָ�������ʹ�ó�Ա����ָ�룬�����ó�Ա����

		//�������ӽ�
		//pmypoint(&mya,15);
		//pmypoint(pmya,15);   //&mya��pmya�Ǵ��ݸ�thisָ��ġ�
		void(* pmyspoint)(int tempvalue) = &A::mysfunc;  //һ����ͨ����ָ�룬�����ǳ�Ա����ָ��
		pmyspoint(80);

		//ͨ����Ա����ָ��Գ���ĳ�Ա�����ĳɱ�����ͨ����ͨ�ĺ���ָ�������þ�̬��Ա�������ɱ��ϲ��

	}
}

namespace _nmsp2
{
	//����ָ�����Ա������ָ�뼰vcall��һ��̸
	//vcall��vcall trunk�� = virtual call : �����
	//������һ��Ҫִ�еĴ���ĵ�ַ����δ���������������ִ����ȷ���麯����
	//��������ֱ�Ӱ�vcall�����麯���������ô�����Ļ�����ôvcall{0}����ľ����麯������ĵ�һ��������
		//vcall{4}�ʹ����麯������ĵڶ����麯��  

	//�������:&A::myvirfunc: ��ӡ��������һ����ַ�������ַ����һ�δ��룬��������м�¼���Ǹ��麯�����е�һ��ƫ��ֵ
		//�������ƫ��ֵ�������˾���Ķ���ָ�룬���ܹ�֪�����õ����ĸ��麯������ߵ��ĸ��麯���ˣ�


	//��Ա����ָ�������Ŀ�����һ��vcall(vcall trunk)��ַ(�麯��),ҪôҲ������һ�������ĳ�Ա������ַ��
	//�����һ��vcall��ַ����vcall���������������ҳ���ȷ���麯�����е��麯����ַ���е��á�


	class A {

	public:
		void myfunc1(int tempvalue1)
		{
			cout << "tempvalue1 = " << tempvalue1 << endl;
		}
		void myfunc2(int tempvalue2)
		{
			cout << "tempvalue2 = " << tempvalue2 << endl;
		}

		static void mysfunc(int tempvalue)
		{
			cout << "A::mysfunc()��̬��Ա����--tempvalue = " << tempvalue << endl;
		}
		virtual void myvirfuncPrev(int tempvalue)
		{
			cout << "A::myvirfuncPrev()���Ա����--tempvalue = " << tempvalue << endl;
		}
		virtual void myvirfunc(int tempvalue)
		{
			cout << "A::myvirfunc()���Ա����--tempvalue = " << tempvalue << endl;
		}

		~A()
		{}
	};


	void func()
	{
		void (A:: * pmyvirfunc)(int tempvalue) = &A::myvirfunc;   //��Ա����ָ��

		A* pvaobj = new A;
		pvaobj->myvirfunc(190);
		(pvaobj->*pmyvirfunc)(190);  //Ҳ��ͨ���麯�������
		printf("%p\n", &A::myvirfunc);
		
		pmyvirfunc = &A::myfunc2;
		(pvaobj->*pmyvirfunc)(33);

		delete pvaobj;

	}
}

namespace _nmsp3
{
	//��:vcall�ڼ̳й�ϵ�е�����
	class A {

	public:
		virtual void myvirfunc(int tempvalue)
		{
			cout << "A::myvirfunc()���Ա����--tempvalue = " << tempvalue << endl;
		}

		~A()
		{}
	};

	class B : public A
	{
	public:
		virtual void myvirfunc(int tempvalue)
		{
			cout << "B::myvirfunc()���Ա����--tempvalue = " << tempvalue << endl;
		}
		virtual ~B(){}
	};
	void func()
	{
		B* pmyb = new B();   //pmy������ָ��
		void (B:: * pmyvirfunc)(int tempvalue) = &A::myvirfunc;  //��Ա����ָ�� //��¼����ƫ��ֵ
		(pmyb->*pmyvirfunc)(190);
	
		printf("%p\n", &A::myvirfunc);  //vcall��ַ ���¸�vcall��ַ��һ��
		printf("%p\n", &B::myvirfunc); 
	}
}
int main()
{
	//_nmsp1::func();
	//_nmsp2::func();
	_nmsp3::func();

	return 0;
}