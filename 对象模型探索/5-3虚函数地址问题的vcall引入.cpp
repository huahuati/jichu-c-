#include<iostream>
using namespace std;

class MYACLS
{
public:
	virtual void myvifunc1() 
	{

	}
	virtual void myvifunc2()
	{

	}
};

int main()
{	
	printf("MYACLS::myvifunc1�麯���ĵ�ַΪ%p\n", &MYACLS::myvifunc1);  //��ӡ����vcall����(����)��ַ�������������麯����ַ
	printf("MYACLS::myvifunc1�麯���ĵ�ַΪ%p\n", &MYACLS::myvifunc2);
	cout << sizeof(MYACLS) << endl;

	MYACLS* pmyobj = new MYACLS();

	//vcall thunk;
	//(1)����this
	//(2)��ת���������麯����ȥ
	return 0;
}