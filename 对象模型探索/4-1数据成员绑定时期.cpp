#include<iostream>
#include<string>
using namespace std;

string myvar = "I love china";  // ȫ�������ַ�����

typedef string mytype;

class A
{
public:
	//void myfunc(mytype tmpvalue)  //mytype = string
	//{
	//	m_value = tmpvalue;   //�����ǰ�һ��string���͸�һ������
	//}
	void myfunc(mytype tmpvalue);  //mytype = string
private:
	typedef int mytype;
	mytype m_value;   //mytype = int
};

void A::myfunc(mytype tmpvalue)   //mytype = int   ��������ᱨ��
{
	m_value = tmpvalue;
}

void myfunc(mytype tmpvalue)
{
	string mvalue = tmpvalue;
}

class B {
public:
	int myfunc();
	//{
	//	return myvar;  
	//}
	int myvar;  //ͬȫ�ֱ�������ͬ�������Ͳ�ͬ��
};

int B::myfunc() //��Ա����
{
	cout << myvar << endl; //myvar�����ڶ����
	cout << ::myvar.c_str() << endl;  //myvar��ȫ�ֵ�
	return myvar;  //���ﻹ��A::myvar
}

string myfunc()
{
	return myvar;  //�����myvar��ȫ�ֵģ���string���ͣ��������ﱨ��
}
int main() {

	//�������ǶԳ�Ա����myfunc�Ľ�����������A�ඨ����Ϻ�ſ�ʼ�ġ�
	//���ԣ������myvar�Ľ����İ󶨣���������ඨ����ɺ����ġ�

	//�ܽ�:
	//�������Գ�Ա����myfunc�Ľ�����������A�ඨ����Ϻ�ſ�ʼ����Ϊֻ��������A������Ϻ�
	//���������ܿ�����A�е�myvar�����ܸ���ʵ�ʵ���Ҫ�ѳ���myvar�ĳ������������ʵ��Ľ���(��Ա�����н���������myvar��ȫ�ֺ����н�����ȫ�ֵ�myvar)

	B bobj;
	bobj.myvar = 15;
	bobj.myfunc();


	//���ڳ�Ա��������:���ڱ�������һ��������������mytype��ʱ�򱻾����ģ�����void myfunc(mytype tmpvalue);�е�mytype
	//��һ��������ʱ�򣬱�����ֻ������typedef string mytype,û�п������е�typedef in mytype;
	
	//����:Ϊ�������о���Ŀ�������mytype�������������Ͷ������typedef,һ��ҪŲ������ͷ���塣
		//�Ǻ�ߵĳ�Ա������һ�������������mytype��ʱ�����ͱ���������������͵�ԭ����Ӧ��������������͡�
}