#include<iostream>
using namespace std;

class Base
{
public:
	int m_bi;
	virtual void mybvirfunc() {}
	Base()
	{
		printf("Base::Base()��thisָ����:%p!\n", this);
	}
};

class Base2
{
public:
	int m_b2i;
	virtual void mybvirfunc2() {}
	Base2()
	{
		printf("Base2::Base2()��thisָ����:%p!\n", this);
	}
};
class MYACLS :public Base,public Base2
{
public:
	int m_i;
	int m_j;
	virtual void myvirfunc() {}  //�麯��
	MYACLS()
	{
		int abc = 1;   //����Ӷϵ�
		printf("MYACLS::MYACLS()��thisָ����:%p!\n", this);
	}
	~MYACLS()
	{
		int def = 0;  //����Ӷϵ�
	}
};

int main() {
	//һ����һ�̳����ݳ�Ա����thisָ��ƫ��֪ʶ����
	//�������ڣ�thisָ�����
		//����������麯�����������麯�������thisָ��������thisָ�����˸��ֽڣ�
		//����������඼���麯�������thisָ��������thisָ����ͬ��
	cout << sizeof(MYACLS) << endl;
	printf("MYACLS::m_bi = %p\n", &MYACLS::m_bi);
	printf("MYACLS::m_b2i = %p\n", &MYACLS::m_b2i);
	printf("MYACLS::m_i = %p\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %p\n", &MYACLS::m_j);

	MYACLS myobj;
	myobj.m_i = 3;
	myobj.m_j = 6;
	myobj.m_bi = 9;
	myobj.m_b2i = 12;

	//�������ؼ̳��Ҹ��඼���麯�������ݳ�Ա����
	//(1)ͨ��thisָ��Ĵ�ӡ�����ǿ�������Base1��Ա������������Base2��ԱҪthisָ��Ҫƫ�ƣ�������8�ֽ�
	//(2)�۲쵽��ƫ��ֵ��m_bi��m_b2iƫ�ƶ���4
	//(3)thisָ�룬����ƫ��ֵ���ܹ����ʶ�Ӧ�ĳ�Ա����������m_b2i = thisָ�� +ƫ��ֵ

	//Ҫ����һ��������г�Ա����Ա��Ķ�λ��ͨ����thisָ��(���������Զ�����)�Լ��ó�Ա��ƫ��ֵ�����������������壻
		//����thisָ��ƫ�Ƶĵ�������Ҫ�������������������

	Base2* pbase2 = &myobj;  //thisָ���������pbase2ʵ������ǰ��8���ֽڵ��ڴ�λ�õ�
								//&myobj = 0x0093fad0 �������������� , pbase2 = 0x0093fad8
	//վ�ڱ������ӽǣ����ϱ������������˵���
	//Base2 *pbase2 = (Base2 *) (  ((char *) &myobj) + sizeof(Base1)  )

	Base* pbase = &myobj;

	Base2* pbase22 = new MYACLS();     //����ָ��new�����������new��������24�ֽ�
	MYACLS* psubobj = (MYACLS*)pbase2; //���ϱߵ�ַ����8�ֽ�(ƫ��)
	//delete pbase22;   //���쳣��������Ϊpbase22��߷��صĵ�ַ���Ƿ�����׵�ַ������ƫ�ƺ��ַ��
						//������������׵�ַӦ������psubobj��ߵ������ַ��
	delete psubobj;z`
	
	return 0;

}