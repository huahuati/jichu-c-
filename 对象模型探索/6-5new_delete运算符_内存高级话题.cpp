#include<iostream>
using namespace std;

namespace _nmspl
{
	//����malloc������0���ֽ�
	//���ֳ���Ա�����ֳ���Ա��������:���ֳ���Ա���ڲ������û�����׵Ķ������Բ�ȥ�ã�����һ�㲻���ô�
		//���ֳ���Ա�����෴������ϵͳû�б�ʲô�쳣�;�������ȷ�ģ�
	//����malloc(0)���ص���һ����Ч���ڴ��ַ��Ҳ��Ҫȥ������ڴ棬��Ҫ�޸����ݣ�Ҳ��Ҫȥ�������Բ�Ҫд���ִ���
	void func()
	{
		void* p = malloc(0);   //new���õ�Ҳ��malloc
		//char* p = new char[0];
		char* q = (char*)p;
		strcpy_s(q, 100, "������һ������");   //100��ʾ�����ڴ�
												//���е��³�����ְ���������
		free(p);   //�����쳣

		int abc;
		abc = 1;
	}

}

int main()
{
	_nmspl::func();
	return 0;
}