#include<iostream>
using namespace std;

class Grand //үү��
{
public:
	int m_grand;
};

class A1 :virtual public Grand
{
public:
	int m_a1;
};
class A2 :virtual public Grand
{
public:
	int m_a2;
};
class C1 :public A1, public A2
{
public:
	int m_c1;
};
int main()
{
	//һ�������(��̳�/������)��������
	//��ͳ��̳���ɵģ��ռ����⣬Ч�����⣬���������⣻
	cout << sizeof(Grand) << endl;  //���ֽ�
	cout << sizeof(A1) << endl;     //���ֽ�
	cout << sizeof(A2) << endl;     //���ֽ�
	cout << sizeof(C1) << endl;     //���ֽ�

	//C1 c1; //Grant���̳�������
	////c1.m_grand = 12;   //�ж����ԣ����ʲ���ȷ�����ֳ�ͻ
	////c1.A1::m_grand = 12;
	////c1.A2::m_grand = 13;

	////�����ǣ�������̳е�ʱ��

	////����࣬��Grand��ֻ���̳�һ��
	//c1.m_grand = 12;   //���������֮�󣬾Ͳ�����ַ��ʲ���ȷ������
	//c1.A1::m_grand = 12;
	//c1.A2::m_grand = 13;

	cout << "���ϴ���Grand::m_grand���ڲ�������" << endl;

	//����������̽Grand
	//�������
		//(1)������ vbtable(virtual base table.)
		//(2)������ָ�� vbptr(virtual base talbe pointer)
	//����sizeof(Grand) == 1�����
	//virtual��̳�֮��A1,A2��ͻᱻ����������һ��������ָ�룬���ָ�룬�е������ڳ�Ա�����ĸо�
	//A1��A2����Ϊ����������ָ�룬���ռ����4���ֽ�

	A1 a1;
	A2 a2;
	//������ָ�룬����ָ��������(��������)��


	return 0;
}