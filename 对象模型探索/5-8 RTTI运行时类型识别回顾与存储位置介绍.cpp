#include<iostream>
using namespace std;

class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	virtual ~Base() {}

};

class Derive :public Base{
public:
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc() {} //ֻ����Derive�ĺ���
	virtual ~Derive() {}
};
int main()
{
//һ:RTTI(����ʱ����ʶ��)�򵥻ع�
	Base* pb = new Derive();
	pb->g();

	Derive myderive;
	Base& yb = myderive;
	yb.g();

	//c++����ʱ����ʶ��RTTI��Ҫ�����б���������һ���麯�������������û���麯������ô�õ�RTTI�Ͳ�׼ȷ��
	//RTTI�Ϳ�����ִ���ڼ��ѯһ����ָ̬�룬���߶�̬���õ���Ϣ�ˣ�	
	//RTTI������typeid��dynamic_cast����������֣�
	cout << typeid(*pb).name() << endl;
	cout << typeid(yb).name() << endl;

	Derive* pderive = dynamic_cast<Derive*>(pb);
	if (pderive != NULL)
	{
		cout << "pbʵ����һ��Derive����" << endl;
		pderive->myselffunc();   //�����Լ�ר������
	}

//����RTTIʵ��ԭ��
	//typeid���ص���һ�������������ã�����������������һ����type_info(��);
	const std::type_info& tp = typeid(*pb);
	Base* pb2 = new Derive();
	const std::type_info& tp2 = typeid(*pb2);
	if (tp == tp2)
	{
		cout << "������ͬ " << endl;
	}


	//�����÷��� ��̬���ͣ������ڶ�̬����
	cout << typeid(int).name() << endl;
	cout << typeid(Base).name()<< endl;
	cout << typeid(Derive).name() << endl;

	Derive* pa3 = new Derive();
	cout << typeid(pa3).name();

	cout << "�ֽ���------" << endl;
	//��̬����
	Base* pbb = new Derive();
	Derive myderive2;
	Base& ybb = myderive2;
	cout << typeid(*pbb).name() << endl;
	cout << typeid(ybb).name() << endl;
	Base* ppbb = new Derive();
	const std::type_info& tp3 = typeid(*ppbb);

	//RTTI�Ĳ����������������Ƿ�����麯�����й�ϵ�����������û���麯����Ҳ�Ͳ����ڻ�����麯����RTTI���޷��õ���ȷ�����
	cout << "�ֽ���------" << endl;
	Base* pb3 = new Derive();
	const std::type_info& tp4 = typeid(*pb3);
	printf("pt3��ַΪ:%p\n", &tp4);
	long* pvptr = (long*)pb3;
	long* vptr = (long*)(*pvptr);
	printf("�麯�����׵�ַΪ:%p\n", vptr);
	printf("�麯�����׵�ַ,��ַ֮ǰһ����ַΪ:%p\n", vptr-1);  //����� -1 ʵ��������������4���ֽ�

	long* ptrttiinfo = (long*)(*(vptr - 1));
	ptrttiinfo += 3;  //����12�ֽ�
	long* ptypeinfoaddr = (long*)(*ptrttiinfo);
	const std::type_info* ptypeinfoaddrearl = (const std::type_info*)ptypeinfoaddr;
	printf("ptypeinfoaddrearl��ַΪ:%p\n", ptypeinfoaddrearl);

	cout << ptypeinfoaddrearl->name() << endl;

//��:vptr,vtbl,rtti��type_info��Ϣ����ʱ��
	//rtti��type_info��Ϣ::�����ʹ����ˣ�д���˿�ִ���ļ���

	//�ܽ�һ��:
	//RTTI��Ϣȡ��һ�㶼�����麯����֮ǰ(�������ĸ��ֽ�)Ϊͻ�ƿ�

	return 0;
}