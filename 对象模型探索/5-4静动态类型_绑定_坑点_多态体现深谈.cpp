#include<iostream>
using namespace std;

class Base
{
public:
	void myfunc()  //��ͨ����
	{
		cout << "Base::myfunc()" << endl;
	}
	virtual void myvirfunc(int value = 1)
	{

		cout << "Base::myvirfunc(),value = " <<  value << endl;
	}
};
class Derive :public Base
{
public:
	void myfunc() //��ͨ��Ա����
	{
		cout << "Derive::myfunc()" << endl;
	}
	virtual void myvirfunc(int value = 2)
	{
		cout << "Derive::myvirfunc(),value = " << value << endl;
	}
};
class Derive2 :public Base {
public:
};

class A
{
public :
	virtual void myvirfunc()
	{

	}
};
int main() {
	//һ����̬���ͺͶ�̬����
	//��̬���ͣ�������ʱ�����ͣ������ڼ��ȷ���õĶ���
	//Base base;  //base�ľ�̫������Base;
	//Derive derive;   //derive�ľ�̬������Derive��û�ж�̬���ͣ���Ϊ�Ȳ���ָ��Ҳ��������
	//Base* pbase;   //pbase�ľ�̬����������Base *  ������Ŀǰû�ж�̬���ͣ���Ϊ��û��ָ���κζ���
	//Base* pbase2 = new Derive();  //pbase2�ľ�̬����������Base * ����̬������Derive
	//Base* pbase3 = new Derive2();  //pbase3�ľ�̬����������Base * , ��̬������Derive2

	//��̬���ͣ�����Ŀǰ��ָ�������(���е�ʱ��ž���������)��һ��ֻ��ָ��������ò��ж�̬���͵�˵����
			//����һ�㶼�Ǹ����ָ���������
	//���⣬��̬������ִ�й����п��Ըı䣺����
	//pbase = pbase2;   //pbase�Ķ�̬����Derive
	//pbase = pbase3;  //pbase�Ķ�̬���͸ı�ΪDerive2;

	//������̬�󶨺Ͷ�̬��
	//��̬�󶨣��󶨵��Ǿ�̬���ͣ�����Ӧ�ĺ����������������ڶ���ľ�̬���ͣ������ڱ����ڼ�
	//��̬�󶨣��󶨵��Ƕ�̬���ͣ�������ĺ����������������ڶ���Ķ�̬���ͣ������������ڣ�
	//a)��ͨ��Ա����ʽ��̬�󶨣����麯���Ƕ�̬��
	//b)ȱʡ����һ���Ǿ�̬��
	
	//�����̳еķ��麯����
	Derive derive;
	Derive* pderive = &derive;
	pderive->myfunc();

	Base* pbase = &derive;
	pbase->myfunc();
	//�ɽ���ó�����:��ͨ��Ա�����Ǿ�̬�󶨣����仰˵,myfunc()����ͨ��Ա���������ﵽ�׵��ø����myfunc���������myfuncȡ���ڵ����ߵľ�̬����
	//��Ϊ����pbase�ľ�̬������Base�����Ե��õ���Base���myfunc();pderive�ľ�̬������Derive *,���Ե��õ���Derive��myfunc();

	//���ۣ���Ӧ�������������¶���һ�̳����ķ��麯����

	//�ģ��麯���Ķ�̬��
	cout << "�ֽ���-------" << endl;
	Base base;
	pderive->myvirfunc();  //ִ��Derive��myvirtual()------>Derive::myvirfunc();
	pbase->myvirfunc();   //pbase��̬������Derive�����麯���Ƕ�̬�󶨣����յ������Ķ�̬���ͣ�   --- Derive::myvirfunc()
							//ȱʡvalue������ӡ�����ľ�Ȼ��1��
						 //pderive�Ķ�̬������Derive,���Ե��õ���Derive��myvirtual();"Derive::myvirfunc(),value = " value = 1
						//���ʼ�ں�������ȱʡֵ�ľ�̬��,����ȱʡ�����󶨵��˸��ຯ����ȱʡ������ȥ��
	pbase = &base;
	pbase->myvirfunc();  //-----Base::myvirfunc();
	//�麯���Ƕ�̬��;���仰˵��myvirtual()���麯�������ﵽ��ִ���Ǹ�myvirtual()ȡ���ڵ����ߵĶ�̬���͡�
			//����pbase�Ķ�̬�ֱ�Derive��Base�����Ե��õ�Ҳ�ֱ���Derive��Base��myvirtual(),
				//pderive�Ķ�̬������Derive,���Ե��õ���Derive��myvirtual();

	//��:���¶����麯����ȱʡ������
	//��Ҫ���¶����麯����ȱʡ����ֵ

	//��:c++�еĶ�̬�Ե�����
	//c++ �С���̬�ԡ�
	//��̬����������������̸:
	//a)�Ӵ���ʵ����
	//b)�ӱ�����ʽ��
	//��һ���۵��ǿ϶���:�ж�̬�������Ǵ����麯����û���麯������û�ж�̬�����麯�����Ҳ�����á�

	//(1)�Ӵ���ʵ����
	//�����ǵ���һ���麯���ǣ�ͨ���ߵ��ǲ���ͨ����ѯ�麯�������ҵ��麯����ڵ�ַ��ȥִ���麯��������ߵ������;������ô���Ƕ�̬
			//����������;�������Ͳ��Ƕ�̬

	A* pa = new A();
	pa->myvirfunc();   //�Ƕ�̬

	A a;
	a.myvirfunc();  //���Ƕ�̬

	A* pa = &a;
	pa->myvirfunc();    //���Ҳ�Ƕ�̬

	//b)�ӱ�����ʽ��(ͨ������������)
	//(1)�м̳й�ϵ���и��������࣬�����б������麯��(����ζ��������һ�������麯��)��������д������麯����
	//(2)����ָ���������ָ���������
	//(3)���Ը���ָ����� ���õ�����������д�˵��麯��ʱ�����Ǿ��ܿ�������̬�ı����ˣ���Ϊ���õ���������麯����
	Base& yinbase = derive;
	yinbase.myvirfunc(); //"Derive::myvirfunc(),value = " 1
	return 0;
}