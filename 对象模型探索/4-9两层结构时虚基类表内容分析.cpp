#include<iostream>
using namespace std;

class Grand //үү��
{
public:
	int m_grand;
};
class Grand2 //үү��
{
public:
	int m_grand2;
};

class Test :virtual public Grand, virtual public Grand2
{
public:
	int test_test;
};

class A1 :virtual public Grand,public Grand2
{
public:
	int m_a1;
};
class A2 :public Grand2 ,virtual public Grand
{
public:
	int m_a2;
};
class C1 :public A1, public A2
{
public:
	int m_c1;
};

int main() {
	//һ������������֮5-8�ֽ����ݷ���
	//������һ����8���ֽڣ��ĸ��ֽ�Ϊһ����λ��û��һ������࣬����಩������4���ֽ�
	//��Ϊ������࣬���������A1��A2������Ĭ�ϵĹ��캯��������Ĭ�Ϲ��캯����ᱻ���������ӽ�ȥһЩ����
		//��vbptr������ָ�븳ֵ
	cout << sizeof(Grand) << endl; 
	cout << sizeof(A1) << endl;     
	cout << sizeof(A2) << endl;     
	cout << sizeof(C1) << endl;     

	A1 a1obj;     
	a1obj.m_grand = 2;
	a1obj.m_a1 = 5;

	//��������ָ�롱��Ա�������׵�ַ + һ��ƫ�����͵���������Ա��m_grand�����׵�ַ���������ƫ��ֵ�����ܹ����ʵ���������
	
	//���������۲������ɫ�ļ̳�
	cout << "�ֽ���-----------" << endl;
	A1 a1obj1;    //ʮ���ֽ�     ||  class A1 :virtual public Grand,public Grand2
	a1obj1.m_grand = 2;  //13-16�ֽ�
	a1obj1.m_grand2 = 2; //1-4�ֽ�
	a1obj1.m_a1 = 5; //9-12�ֽ�
					//5-8�ֽڣ��麯����ָ��
	 
	A2 a2obj;  //ʮ���ֽ�      ||    class A2 :public Grand2 ,virtual public Grand
	a2obj.m_grand = 2;  //1-4���ֽ�
	a2obj.m_grand2 = 2; //13-16�ֽ�
	a2obj.m_a2 = 5; //9-12�ֽ�
					//5-8�ֽڣ��麯����ָ��

	Test test;  //ʮ���ֽ�      ||    class Test :virtual public Grand, virtual public Grand2
	test.m_grand = 2;      //9-12�ֽ�
	test.m_grand2 = 2;		//13-16�ֽ�
	test.test_test = 5;		//5-8�ֽ�
					//������ָ��  1-4�ֽ�
	//Test �����ڴ�����ܽ᣺
	//a)����������������3�+4��+8�������г�Ա����ͨ��ȡ���������е�ƫ��ֵ����ֵ�ġ�
	//b)�������е�ƫ�����ǰ��ռ̳�˳������ŵġ�
	//c)������Ӷ���һֱ�������±�

	//��������������֮1-4�ֽ����ݷ���
	//������ָ���Ա�������׵�ַ���ͱ�����A1�׵�ַ֮���ƫ���� Ҳ���ǣ�������ָ����׵�ַ -A1������׵�ַ

	//���ۣ�ֻ�ж�������Ա���д�����縳ֵ��ʱ�򣬲Ż��õ�������ȡ���е�ƫ�ƣ������ַ�ļ��㣻
	return 0;

}