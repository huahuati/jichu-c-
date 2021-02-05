#include<iostream>
#include<vector>
using namespace std;

class MYACLS
{
public:
	int m_i;
	void myfunc(int abc) {
		m_i += abc;
	}
	virtual void myvirfunc()
	{
		printf("myvirfunc()������,this = %p\n", this);
		//myvirfunc2();  //	myacls.myvirfunc();myvirfunc2()��Ȼ�����麯�������
		MYACLS::myvirfunc2();   //ֱ�ӵ����麯����Ч�ʸ��ߡ�����д��ѹ����������ƣ�����ͨ����ѯ�麯���������á�
								//����������::�麯����()��ȷ�����麯���ķ�ʽ�ȼ���ֱ�ӵ���һ����ͨ����
	}
	virtual void myvirfunc2()
	{
		printf("myvirfunc2()������,this = %p\n", this);
	}

	//��̬��Ա����
	static void mystfunc()   //����Ҫthis����
	{
		printf("mystfunc()������\n");
	}
};

int main() {

	//һ�����Ա����(�麯��)���÷�ʽ

	MYACLS myacls;
	myacls.myvirfunc();  //�ö�������麯�������������ͨ��Ա����һ�����������ڣ�����ҪҪͨ���麯����

	MYACLS* pmyacls = new MYACLS();
	pmyacls->myvirfunc();   //Ҫͨ���麯����ָ������麯����ͨ���麯�����ҵ��麯������ڵ�ַ����ɶ��麯���ĵ��á�
	delete pmyacls;
	//�������ӽ�
	//(*pmyacls->vptr[0])(pmyacls)
	//a) vptr,���������������ɵ��麯����ָ�룬ָ���麯����
	//b) [0] �麯�����е�һ�����myvirfunc()��ַ
	//c) ����һ��������ȥ������this��Ҳ�Ǳ��������ӵġ�
	//d) *�͵õ����麯���ĵ�ַ��
	printf("MYACLS::myvirfunc2�麯���ĵ�ַΪ%p", &MYACLS::myvirfunc2);

	cout << "�ֽ���-------" << endl;
	//��̬��Ա�����ĵ��÷�ʽ
		//��̬��Ա������û��thisָ��
	myacls.mystfunc();
	pmyacls->mystfunc();
	MYACLS::mystfunc();
	//�������д������κ�����

	((MYACLS*)0)->mystfunc;  //�ܹ��������þ�̬��Ա���������ܵ��÷��û��Ǿ�̬��Ա����(��Ȼ��ͨ������)
	((MYACLS*)0)->myfunc;   //��Щ��Ա����ϣ��֧�ֶ����ڶ���֮��Ĵ�ȡ����----�����ֲ�����Ϊstatic

	//��̬��Ա��Ա��������
	//a)��̬��Ա����û��thisָ�룬�������Ҫ
	//b)�޷�ֱ�Ӵ�ȡ������ͨ�ķǾ�̬��Ա����
	//c)��̬��Ա����������ƨ�ɺ���ʹ��const��Ҳ��������Ϊvirtual
	//d)�������������ã������ǵ�һ��Ҫ����������
	//e)��̬��Ա������ͬ�ڷǳ�Ա����,�е���Ҫ�ṩ�ص����������ֳ��ϣ����Խ���̬��Ա������Ϊ�ص�������
	printf("MYACLS::mystfunc()��ַ = %p\n", MYACLS::mystfunc);
	return 0;
}