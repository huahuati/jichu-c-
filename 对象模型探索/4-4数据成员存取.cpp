#include<iostream>
using namespace std;

class FAC
{
public:
	int m_fai;
	int m_faj;
};

class MYACLS : public FAC 
{
public:
	int m_i;
	static int m_si;   //�������Ƕ���
	int m_j;

	void myfunc()
	{
		m_i = 5;
		m_j = 6;
	}
};

int MYACLS::m_si = 0;   //����Ƕ���

int main() {

	//һ����̬��Ա�����Ĵ�ȡ
	//��̬��Ա���������Ե���һȫ������������ֻ����Ŀռ��ڿɼ�������ʱ ����::��̬��Ա������
	//��̬��Ա����ֻ��һ��ʵ�壬�����ڿ�ִ���ļ������ݶΡ�

	MYACLS myobj;
	MYACLS* pmyobj = new MYACLS();

	cout << MYACLS::m_si << endl;
	cout << myobj.m_si << endl;
	cout << pmyobj->m_si << endl;

	MYACLS::m_si = 1;
	myobj.m_si = 2;
	pmyobj->m_si = 3;
	

	//��ͨ��Ա����
	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);

	//��̬��Ա�������ڴ��ڿ�ִ���ļ��С�
	printf("MYACLS::m_si = %p\n", &MYACLS::m_si);
	printf("myobj.m_si = %p\n", &myobj.m_si);
	printf("pmyobj->m_si = %p\n", &pmyobj->m_si);

	//�����Ǿ�̬��Ա�����Ĵ�ȡ(��ͨ�ĳ�Ա����)���������Ķ����С���ȡͨ�������(�����ָ��)
	cout << "�ֽ���-------" << endl;
	pmyobj->myfunc();
	//�������Ƕ�:MYACLS::myfunc(pmyobj)
	//MYACLS::myfunc(MYACLS *const this)
	//{
			//this->m_i = 5;
			//this->m-j = 6;
	//}
	//������ͨ��Ա�����ķ��ʣ��������ǰ��������׵�ַ���ϳ�Ա������ƫ��ֵ
	//&myobj + 4 = &myobj.m_j;
	cout << "�ֽ���-------" << endl;
	printf("MYACLS::m_fai = %p\n", &MYACLS::m_fai); //����и��࣬�����еĳ�Ա��ƫ��ֵ���
	printf("MYACLS::m_faj = %p\n", &MYACLS::m_faj);
	printf("MYACLS::m_i = %p\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %p\n", &MYACLS::m_j);

	//�����ķ��ʷ�ʽ��ͬ����������
	return 0;
}