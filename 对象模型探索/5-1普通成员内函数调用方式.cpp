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

	//�������ӽ�
	//void myfunc(MYACLS *const this,int abc)  //����������ⰲ��һ��thisָ�룬һ����ӵ������Ŀ�ͷ
	//{
	//	this -> m_i + abc;
	//}
};
void gmyfunc(MYACLS* ptmp, int abc)
{
	ptmp->m_i += abc;
}
int main() {

	//��һ�� ��ͨ��Ա�������÷�ʽ

	MYACLS myacls;
	myacls.myfunc(18);   //���ó�Ա����
	gmyfunc(&myacls, 18);   //����ȫ�ֺ���

	//c++������Ƶ�ʱ����һ��Ҫ��Ҫ���������ͨ��Ա�����ĵ��ò�Ӧ�ñ�ȫ������Ч�ʲ
	//�����������Ҫ�󣬱������ڲ�ʵ�����ǽ��Գ�Ա����myfunc()�ĵ���ת�����˶�ȫ�ֺ����ĵ��ã�

	//��Ա�����ж������ڴ��ַ���Ǹ������ߵģ����ҳ�Ա�����ĵ�ַ ���ڱ����ʱ���ȷ���õģ�

	//a)����������������һ����this���βΣ��Ǹ�ָ�룬ָ��ľ������ɵĶ���
	//b)�����Ա�����Ĵ�ȡ����ͨ��this�β������У���������this->m_i + abc;
	printf("MYACLS::myfunc�ĵ�ַ=%p\n", &MYACLS::myfunc);
	return 0;
}