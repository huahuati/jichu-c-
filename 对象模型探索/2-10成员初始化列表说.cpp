#include<iostream>
#include<time.h>

using namespace std;
class Base
{
public:
	int ba;
	int bb;
	Base(int tmpa,int tmpb)
	{}
};

class CSub
{
public:
	CSub(int tmpv)
	{

	}
};

class A : public Base
{
public:
	int m_x;
	int m_y;
	int& m_yy;
	CSub cmysub;
	const int m_myc;
	A(int &tmpvalue) :m_x(0), m_y(0),m_yy(tmpvalue),m_myc(tmpvalue),Base(tmpvalue, tmpvalue)
						, cmysub(tmpvalue)
	{
		//m_yy = tmpvalue;    //���ָ��ƽ����Ǵ����
	}
};

class X {
public:
	int m_i;
	X(int value = 0) : m_i(value)  //����ת�����캯��
	{
		printf(" this = %p", this);
		cout << "X(int)���캯��������" << endl;
	}
	X(const X& tmpv)
	{
		printf(" this = %p", this);
		cout << "X�������캯��������" << endl;
	}
	X& operator = (const X& tmp)
	{
		printf(" this = %p", this);
		cout << "X������ֵ�����������" << endl;
		return *this;
	}
	~X()
	{
		printf(" this = %p", this);
		cout << "X��������������" << endl;
	}

};

class B {
public:
	X xobj;  //�����Ͷ���
	int m_test;
	//���캯��
	//B(int tmpvalue) //���ﹹ����xobj,�ķ���һ�ε��ù��캯���Ļ���
	//				//վ�ڱ������Ƕ�
	//					//X xobj;
	//					//xobj.X::X()
	//{
	//	xobj = 1000;//���ﹹ��һ����ʱ���󣬰���ʱ������ÿ�����ֵ����������ݸ���xobj,�ͷŵ���ʱ����
	//						//  X tmpobj;  //����һ����ʱ����
	//						//  tmpobj.X::X(1000);   //��ʱ��������˹��캯��
	//						//	xobj.X::operator=(tmpobj); //���õ���xobj�Ŀ�����ֵ�����
	//						//  tmpobj.X::~X();   //������������������ʱ����

	//	m_test = 500;

	//}

	//�ó�ʼ���б����������ʽ���ѳ�ʼ���б��еĴ��뿴���Ǻ������ڴ����һ���֣� 
	int m_test1;
	int m_test2;
	B(int tmpvalue) :xobj(1000)//,m_test2(100),m_test(m_test1)  //����д���Ǵ���ġ�
		//վ�ڱ������ӽ�
		//X xobj;
		//xobj.X::X(1000)		
	{
		cout << "mtest = " << m_test << endl;
		cout << "mtest1 = " << m_test1 << endl;
		m_test = 500;
	}
};
int main() {
	//(1)��ʱ�����ó�Ա��ʼ���б�
	//a)�����Ա�Ǹ�����
	//int abc = 1;
	//A a(abc);

	//b)����Ǹ�const���ͳ�Ա
	//c)���������Ǽ̳�һ�����࣬���һ������й��캯����������캯����߻��в�����
	//d)�����Ա����������ĳ�������ͣ��������Ĺ��캯��������ʱ��

	//(2)ʹ�ó�ʼ���б������
	//���˱����ó�ʼ���б�ĳ��ϣ������ó�ʼ���б���ʲô����Ŀ��? �У�������߳�������Ч�ʡ�
	//���������ͳ�Ա���� xobj �ŵ���ʼ���б����ܹ��Ƚ����ԵĿ���Ч�ʵ�������
		//��ʱ����Ǹ������͵ĳ�Ա���� ������ int���ͣ����ڳ�ʼ���б���߷��ں�������Ч�ʲ�𲻴�
	//����:��Ա������ʼ���������ڳ�ʼ���б���Ե� �߶ˣ������ϵ���
	//(3)��ʼ���б�ϸ��̽��
	//˵����
		//(3.1)��ʼ���б��еĴ�����Կ����Ǳ���������嵽���캯�����еģ�ֻ����Щ������Щ���⡣
		//(3.2)��Щ���������κ��û��Լ��Ĺ��캯�������֮ǰִ�еġ�
				//����Ҫ���ֹ��캯���е�  �û����� �� ���������� �� ��ʼ�������Ĵ���
		//(3.3)��Щ�б��б����ĳ�ʼ��˳���� ����˳�򣬶������ڳ�ʼ���б��е�˳��
			//�������ڳ�ʼ���б��н���������Ա���ڳ�ʼ���б��г��ֵĳ�Ա֮��ĳ�ʼ��
	B myaobj(1000);
	return 0;
}