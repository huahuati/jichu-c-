#include<iostream>
using namespace std;

class FAC //����
{
public:
	int m_fai;
	int m_faj;
};

class MYACLS : public FAC //����
{
public:
	int m_i;
	int m_j;
};

class Base   //sizeof = ���ֽ�
{
public:
	int m_il;
	char m_c1;
	char m_c2;
	char m_c3;
};

class Base1 {
public:
	int m_li;
	char m_c1;
};
class Base2 :public Base1
{
public:
	char m_c2;
};

class Base3 :public Base2
{
public:
	char m_c3;
};

int main() {
	//�����  ��һ�̳��µ����ݳ�Ա����
	printf("FAC::m_fai = %p\n", &FAC::m_fai);
	printf("FAC::m_faj = %p\n", &FAC::m_faj);

	cout << "�ֽ���----------" << endl;

	printf("MYACLS::m_faj = %p\n", &MYACLS::m_faj);
	printf("MYACLS::m_faj = %p\n", &MYACLS::m_faj);

	cout << "�ֽ���----------" << endl;

	printf("MYACLS::m_i = %p\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %p\n", &MYACLS::m_j);

	//(1)һ��������������������ݣ������Լ��ĳ�Ա������������ĳ�Ա���ܺ�
	//(2)��ƫ��ֵ���������Ա�ȳ��֣�Ȼ����Ǻ������Ա��

	FAC myobj;
	MYACLS mycalobj;   //��������а��������Ӷ���

	cout << "�ֽ���------Base" << endl;
	cout << sizeof(Base) << endl;   //�˸��ֽ�
	printf("Base::m_il = %p\n", &Base::m_il);
	printf("Base::m_c1 = %p\n", &Base::m_c1);
	printf("Base::m_c2 = %p\n", &Base::m_c2);
	printf("Base::m_c3 = %p\n", &Base::m_c3);

	cout << "�ֽ���------Base1" << endl;
	cout << sizeof(Base1) << endl;  //���ֽ�

	cout << "�ֽ���------Base2" << endl;
	cout << sizeof(Base2) << endl;//ʮ���ֽ�

	cout << "�ֽ���------Base3" << endl;
	cout << sizeof(Base3) << endl;//ʮ���ֽ�
	printf("Base3::m_il = %p\n", &Base3::m_li);
	printf("Base3::m_c1 = %p\n", &Base3::m_c1);
	printf("Base3::m_c2 = %p\n", &Base3::m_c2);
	printf("Base3::m_c3 = %p\n", &Base3::m_c3);

	//liunx��windows�����ݲ��ֲ�һ����˵����
	//a)�������ڲ��ϵĽ��������Ż���
	//b)��ͬ���̱�������ʵ��ϸ��Ҳ��һ����
	//c)�ڴ濽����Ҫ����

	//�Ͳ�����memcpy�ڴ濽����base2�ڴ��ֽ���base3���濽������������linux����
	return 0;
}