#include<iostream>
using namespace std;

namespace _nmspl  //�����ռ�
{
	//һ��inline�����ع�
	//ʹ��inline֮�󣬱������ڲ�����һ���Ƚϸ��ӵĲ����㷨���������inline�����ĸ��Ӷȣ�
	//���ܻ�ͳ�����inline�����У���ֵ�������ڲ��������ã��麯�����õȴ���  --Ȩ��

	//(1)������д��inlineֻ�ǶԱ�������һ�����飬���������������inline�������Ӷȹ��ߣ����inline����ͱ�����������
	//(2)���inline������������,��ôinline��������չ����Ҫ�ڵ���inline�������Ǹ����Ͻ���
			//��ô���ܴ������������ �����磺������ֵ�����ܲ�����ʱ��������ɺ͹���

	//����inline��չϸ��
	//(2.1)�βα���Ӧʵ��ȡ��
	//(2.2)�ֲ���������(�ֲ������������þ������ã��ܲ��þ�������)
	//(3.3)inlineʧ������
	inline int myfunc(int testc)
	{
		int tempvalue = testc * (5 + 4) * testc;  //�ֲ�����������
		//return testc * (5 + 4) * testc;
		return tempvalue;
	}
	inline int myfunc1(int testc)   //inline���û�ʧ��
	{
		if (testc > 10)
		{
			testc--;
			myfunc1(testc);
		}
		return testc;
	}
	int rtnvalue()
	{
		return 5;
	}
	void func()
	{
	    //int i = myfunc(12+15);   //������������ֵ��Ȼ����ʵ�����滻�β�
		//int a = 80;
		//int i = myfunc(a + 15);  //���������ȼ���a��15�ĺ�ֵ��Ȼ�����滻���β�

		//int i = myfunc(rtnvalue() + 5); //���������ȵ���rtnvalue()�õ�����ֵ������ֵ��15���ӷ���Ȼ�����滻���ͲΡ�
		int i = myfunc(5);
		int ii = myfunc1(11);
		cout << i << endl;
	}
}
int main()
{
	_nmspl::func();

	return 0;
}