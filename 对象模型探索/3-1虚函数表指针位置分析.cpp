#include<iostream>

using namespace std;


class A {
public:
	int i; //4�ֽ�
	virtual void testfunc(){}//�麯��
};
int main() {
	//�麯����ָ��λ�÷���
	//��:���麯�������������һ���麯���ࡣ
	//�������һ��ָ�룬ָ��(vptr)��ָ������麯����Ŀ�ʼ��ַ

	A aobj;
	int ilen = sizeof(aobj);
	cout << ilen << endl;  //8�ֽ�

	char* p1 = reinterpret_cast<char*>(&aobj);  //����ת����Ӳת &aobj���Ƕ���aobj���׵�ַ��
	char* p2 = reinterpret_cast<char*>(&aobj.i);
	if (p1 == p2)  //˵��aobj.i �� aobj��λ����ͬ��˵��i�ڶ���aobj�ڴ沼�ֵ��ϱߡ��麯����ָ��vptr���±�
							//ʵ�����麯��ָ�������ϱ�
	{
		cout << "�麯����ָ��λ�ڶ����ڴ��ĩβ" << endl;
	}
	else
	{
		cout << "�麯����ָ��λ�ڶ����ڴ�Ŀ�ͷ" << endl;
	}

	return 0;
}