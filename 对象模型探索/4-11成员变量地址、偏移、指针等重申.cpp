#include<iostream>
using namespace std;

class MYACLA
{
public:
	int m_i;
	int m_j;
	int m_k;
};

void myfunc(int MYACLA::*mempoint, MYACLA& obj)
{
	obj.*mempoint = 260;  //ע��д��
}
int main() {
	//һ�������Ա�����ڴ��ַ����ָ��
	MYACLA myobj;
	myobj.m_i = myobj.m_j = myobj.m_k = 0;
	printf("myobj.mi = %p\n", &myobj.m_i);   //����ĳ�Ա���������������ڴ��ַ�ģ�
	cout << "�ֽ���------" << endl;

	MYACLA* pmyobj = new MYACLA();
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);
	printf("pmyobj->m_j = %p\n", &pmyobj->m_j);
	printf("pmyobj->m_k = %p\n", &pmyobj->m_k);
	cout << "�ֽ���------" << endl;

	int* p1 = &myobj.m_i;
	int* p2 = &pmyobj->m_j;

	*p1 = 15;
	*p2 = 30;

	cout << "�ֽ���------" << endl;
	printf("p1��ַ=%p,p1ֵ = %d\n", p1,*p1);
	printf("p2��ַ=%p,p2ֵ = %d\n", p2,*p2);

	cout << "�ֽ���------" << endl;
	//������Ա������ƫ��ֵ����ָ��(�;��������û�й�ϵ��)
	cout << "��ӡ��Ա����ƫ��ֵ------------" << endl;
	printf("MYACLA::m_iƫ��ֵ = %d\n", &MYACLA::m_i);   //��ӡƫ��ֵ�������õ�%d
	printf("MYACLA::m_jƫ��ֵ = %d\n", &MYACLA::m_j);
	
	//�ó�Ա����ָ������ӡƫ��ֵҲ���ԣ���Щ��
	//��Ա������߱���� ʵ�����Ǹ�ƫ��ֵ(���Ǹ�ʵ���ڴ��ַ)
	int MYACLA::* mypoint = &MYACLA::m_j;
	printf("MYACLA::* mypointƫ��ֵ = %d\n", mypoint);
	mypoint = &MYACLA::m_i;   //ע�⣬����ʹ����ֱ�������֣�����ʱ����Ҫ��MYACLA
	printf("MYACLA::* mypointƫ��ֵ = %d\n", mypoint);

	//����û��ָ���κ����ݳ�Ա������ָ��
	//ͨ��һ�����������߶���ָ��������Ա����ָ��������ĳ������ĳ�Ա����
	myobj.m_i = 13;
	myobj.*mypoint = 22;
	pmyobj->*mypoint = 19;

	myfunc(mypoint, myobj);
	myfunc(mypoint, *pmyobj);

	cout << "sizeof(mypoint) =" <<sizeof(mypoint) << endl; //Ҳ���ĸ��ֽ�

	int* ptest = 0;
	int MYACLA::* mypoint2 = 0;  //��Ա����ָ��
	//mypoint = 0;//��Ա����ָ��
	//mypoint= NULL; //0xfffffff

	printf("mypoint2 = %d\n", mypoint2);
	//if(mypoint2 == mypoint)  //������
	int MYACLA::* mypint10 = &MYACLA::m_i;
	if (mypoint == mypint10)  //������
	{
		cout << "����" << endl;
	}
	return 0;
}