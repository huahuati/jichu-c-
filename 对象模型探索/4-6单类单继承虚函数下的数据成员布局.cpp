#include<iostream>
using namespace std;

class Base
{
public:
	int m_bi;
	//virtual void mybvirfunc() {}
};

class MYACLS :public Base
{
public:
	int m_i;
	int m_j;
	virtual void myvirfunc() {}  //�麯��
	MYACLS()
	{
		int abc = 1;   //����Ӷϵ�
	}
	~MYACLS()
	{
		int def = 0;  //����Ӷϵ�
	}
};

int main() {
	//һ����������麯�������ݳ�Ա����
	//���������麯�������ж���ĳɱ�����
	//(1)�����ʱ�򣬱�����������麯�����ο��������
	//(2)�����л���� �麯����ָ��vptr,����ָ���麯�����
	//(3)���������ӻ�����չ���캯�������Ӹ��麯����ָ��vptr��ֵ�Ĵ��룬��vptrָ���麯����
	//(4)������ؼ̳У�����̳���2�����࣬ÿ�����඼�����麯����ÿ�����඼����vptr���Ǽ̳�ʱ������ͻ��������vptr���̳й���
				//������໹���Լ�������麯���Ļ����������һ�����๲��һ��vptr
	//(5)����������Ҳ����չ���������麯����ָ��vptr��صĸ�ֵ���룬�о������ֵ�����ƺ��͹��캯���д�����ͬ��


	cout << sizeof(MYACLS) << endl;
	printf("MYACLS::m_bi = %p\n", &MYACLS::m_bi);
	printf("MYACLS::m_i = %p\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %p\n", &MYACLS::m_j);

	MYACLS myobj;
	myobj.m_i = 3;
	myobj.m_j = 6;
	myobj.m_bi = 9;

	//������һ�̳и�����麯�������ݳ�Ա�Ĳ���
	// vptr�ĵ�ַ��ƫ��ֵΪ0��(�ڶ����ڴ����λ)

	//������һ�̳и��಻���麯�������ݳ�Ա�Ĳ���
	//vptr�ĵ�ַ��ƫ��ֵΪ0��(�ڶ����ڴ����λ)���Ͷ�һ��

	return 0;
}