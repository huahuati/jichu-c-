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
	//һ������ṹʱ���������ݷ���
	cout << sizeof(Grand) << endl; 
	cout << sizeof(A1) << endl;     
	cout << sizeof(A2) << endl;     
	cout << sizeof(C1) << endl;  

	C1 c1obj;
	c1obj.m_grand = 2;   //21-24�ֽ�
	c1obj.m_a1 = 5;      //5-8�ֽ�
	c1obj.m_a2 = 6;		//13-16�ֽ�
	c1obj.m_c1 = 8;		//17-20�ֽ�
						//vptr1 1-4�ֽ�
						//vptr2 9-12�ֽ�

	//�������֣�û���õ�vptr2��ֻ�õ�vptr1
	//����������Աʱ���ٶȻ����

	//���������Ϊʲô��ô���
	//Ϊʲô��ô���
	return 0;

}