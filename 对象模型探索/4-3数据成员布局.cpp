#include<iostream>
using namespace std;
#define GET(A,m)(int)(&((A*)0)->m)  //�����Ҳ���Եõ�ƫ��ֵ
//����һ����
#pragma pack(1)  //���뷽ʽ����Ϊ1�ֽڶ���(������)
class MYACLA
{
public:
	int m_i;
	static int m_si;  //�������Ƕ���
	int m_j;
	static int m_sj;
	int m_k;
	static int m_sk;

	char m_c;   //1�ֽ�
	int m_n;    //4�ֽ�
private:
	int m_pria;
	int m_prib;

public:
	void printMenPoint()
	{
		cout << "��ӡ��Ա����ƫ��ֵ-------" << endl;
		printf("MYACLA::m_i = %d\n", &MYACLA::m_i);
		printf("MYACLA::m_j = %d\n", &MYACLA::m_j);
		printf("MYACLA::m_k = %d\n", &MYACLA::m_k);
		printf("MYACLA::m_c = %d\n", &MYACLA::m_c);
		printf("MYACLA::m_n = %d\n", &MYACLA::m_n);
		printf("MYACLA::m_pria = %d\n", &MYACLA::m_pria);
		printf("MYACLA::m_prib = %d\n", &MYACLA::m_prib);
	}
	virtual void func(){}  //�麯����������ڴ����λ��
};
#pragma pack()  //ȡ��ָ�����룬�ָ�ȱʡ����;
int MYACLA::m_sj = 0;   //����Ƕ���

int main() {

	//һ���۲��Ա������ַ����
	MYACLA myobj;
	cout << sizeof(myobj) << endl;

	//��ͨ��Ա�����Ĵ洢˳���ǰ��������ж���˳����ϵ������ģ�
	//�Ƚ�����ֵĳ�Ա�������ڴ����и��ߵĵ�ַ
	//�ඨ����public,private,protected����������Ӱ��������sizeof
	myobj.m_i = 2;
	myobj.m_k = 8;
	myobj.m_j = 5;

	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("myobj.m_j = %p\n", &myobj.m_j);
	printf("myobj.m_k = %p\n", &myobj.m_k);

	cout << "�ֽ���---------------�ֽ���" << endl;

	MYACLA* pmyobj = new MYACLA();
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);
	printf("pmyobj->m_j = %p\n", &pmyobj->m_j);
	printf("pmyobj->m_k = %p\n", &pmyobj->m_k);


	//�����߽�������ֽڶ���
	//ĳЩ�����ᵼ�³�Ա����֮�����в����������Ǳ߽����(�ֽڶ���),������Ŀ�������Ч�ʣ��������Զ�������
				//����:����Ա֮���һЩ�ֽڣ�ʹ��������sizeof�ֽ����ճ�һ��4����������8����������
	//��Ϊͳһ�ֽڶ������⣬����һ�������һ�ֽڶ���(������)
			//#pragma pack(1)
			//#pragma pack()
	//���麯��ʱ�����������������������vptr�麯����ָ�룺�ڲ������ݳ�Ա

	cout << "�ֽ���---------------�ֽ���" << endl;
	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("myobj.m_j = %p\n", &myobj.m_j);
	printf("myobj.m_k = %p\n", &myobj.m_k);
	printf("myobj.m_c = %p\n", &myobj.m_c);
	printf("myobj.m_n = %p\n", &myobj.m_n);

	//������Ա����ƫ��ֵ�Ĵ�ӡ
	//��Ա����ƫ��ֵ�����������Ա�����ĵ�ַ��������׵�ַƫ���Ƕ��١�
	pmyobj->printMenPoint();

	cout << "��ӡ��Ա����ƫ��ֵ--------" << endl;
	cout << GET(MYACLA, m_j) << endl;

	//��Ա����ָ��
	int MYACLA::* mypoint = &MYACLA::m_n;
	printf("mypoint->m_nƫ��ֵ = %d\n", mypoint);
	return 0;
}