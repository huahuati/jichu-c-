#include<iostream>
using namespace std;

//����
class Base
{
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
};

class Derive :public Base
{
	virtual void g() { cout << "Dervie::g()" << endl; }
	//void f() { cout << "Base::f()" << endl; }
	//void g() { cout << "Base::g()" << endl; }
	//void h() { cout << "Base::h()" << endl; }
};

int main() {
	//�̳й�ϵ�������麯�����ֹ�����

	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << "--------------------------" << endl;
	Derive* d = new Derive();
	Derive* d2 = new Derive();

	//(1)һ����ֻ�а����麯���Ż�����麯����ͬ����һ����Ķ������麯���������и��Ե�vptr(�麯����ָ��)��
			//��Ȼ��ָ���ָ���ַ(�麯�����׵�ַ)��ͬ��

	long* pvptr = (long*)d;
	long* vptr = (long*)(*pvptr);

	long* pvptr2 = (long*)d2;
	long* vptr2 = (long*)(*pvptr2);

	//(2)���������麯���͵������������麯�������仰��˵�����������麯�����������п϶����麯������Ϊ�Ǽ̳и����
				//��������аѸ�����麯����virtualȥ�����ǲ�����Щ�����Ͳ������麯����?
					//ֻҪ�ڸ��������麯������ô�����м��㲻дvirtual��Ҳ�������麯��
		//�����Ǹ��໹�����࣬��ֻ����һ���麯����������Ϊ��������һ���麯����+��������һ���麯����
			//�õ�һ������:�������������麯��������������Ǵ���ģ�

		//�������Ƿ���ܻ��ж���麯������?��������
	//(3)�����������ȫû���µ��麯���������ǿ�����Ϊ������麯����͸�����麯����������ͬ��
		//����������������ͬ�������������ڴ��д��ڲ���λ�ã����仰��˵������������ͬ�����ű�
			//�麯������ÿһ�������һ���麯�����׵�ַ�������������麯������͸�����麯���������ͬһ������
				//���ʾ����û�и��Ǹ�����麯������ñ�����ָ��ĸú����ĵ�ַӦ����ͬ��

	//(4)�����麯���������ݲ���֪

	//(5)��ʼ����ֵʱ�����ÿ������캯��ָ����ͬ���麯����
	Derive derive;
	long* pvptrderive = (long*)(&derive);
	long* vptrderive = (long*)(*pvptrderive);

	Derive derive2;
	long* pvptrderive2 = (long*)(&derive2);
	long* vptrderive2 = (long*)(*pvptrderive2);

	Base base = derive;//ֱ�������������������ֵ�������е����ڸ����ǲ������ݻᱻ�������Զ�����(�и�)����
							//���������˸����������Base base = derive;ʵ���ϸ�����������:
								//��һ������:����һ��Base����
								//�ڶ�������:��derive����ʼ��base����ֵ
							//�������������������һ��ѡ����Ȼderive��ʼ��base��ʼ��base�����ʱ��
								//derive���麯����ָ��ֵ��û�и���base������麯����ָ��ֵ��
	
	long* pvptrbase = (long*)(&base);
	long* vptrbase = (long*)(*pvptrbase);


	//oo(�������) ��OB(���ڶ���)����:
	//c++ͨ�����ָ���������֧�ֶ�̬������һ�ֳ�����Ʒ����������ǳ�˵���������object-oriented model;
	//OB(object-based),Ҳ����ADT��������ģ��[abstract datatype model]����֧�ֶ�̬��ִ���ٶȸ��죬
		//��Ϊ�������õĽ�������Ҫ����ʱ����(û�ж�̬),�����ڱ����ڼ�ͽ�����ɣ��ڴ�ռ���ճ̶��ϸ����գ���Ϊû���麯��

	Base* pbase = new Derive();
	Base& base2 = derive2;
	//������Ȼ��OB���������ԾͲ�
	//c++��֧���������������(�̳У���̬)(oo),Ҳ֧�ֻ��ڶ���(OB)������ơ�
	return 0;
}