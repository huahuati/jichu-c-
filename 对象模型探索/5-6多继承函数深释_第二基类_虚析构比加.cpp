#include<iostream>
using namespace std;
class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	virtual ~Base() {}
};

class Base2
{
public:
	virtual void hBase2() {
		{ cout << "Base2::hBase2()" << endl; }
	}
	//~Base2()
	//{
	//	int ab;
	//	ab = 1;
	//}
	virtual ~Base2()
	{
		int ab;
		ab = 1;
	}
};

class Derive :public Base,public Base2 {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc(){} //ֻ����Derive�ĺ���
	virtual ~Derive(){}
};
int main() {
	//һ:��̳��µ��麯��
	//���ؼ̳и��������ں����������ϣ�
	Base2* pb2 = new Derive();
	//�������ӽ�
		//Derive* temp = new Derive();
		//Base2 *pb2 = (Base *)((char *)temp +sizeof(Base));
		//���������Ǵ���ġ�
		//Base2* pb2 = temp + sizeof(Base);  //��ת�Ĳ���sizeof(Base)���ֽڣ�����sizeof(Base) *sizeof(Base2)�ֽ�;
	delete pb2;  //�����Base2�������������������쳣

	//������γɹ�ɾ���õڶ�����ָ��new�����ļ̳ж���
	//a)Ҫɾ����ʵ��������Derive()����
	//b)Ҫ�ܹ���֤Derive()�����������������������
	//c)�����������Base2()���������������ǵ���Derive������������?
	//d)ִ��delete pb2�ǣ�ϵͳ�Ķ�������?
		//d.1)���Base2��û��������������������ֱ��ɾ����pb2��ͷ������ڴ棬һ�����쳣����Ϊ����ڴ�ѹ���Ͳ���new��ʵ���ڴ档
		//d.2)���Base2����һ���������������������������Ǹ���ͨ������������������������,��ô��delete pb2
				//������������ͱ���ϵͳ���ã�����delete���Ծ���pb2��ͷ����ڴ棬����һ�����쳣����Ϊ����ڴ�ѹ���Ͳ���new��ʼ���ڴ�
			//��һ�ֽ��ͣ�����������������麯������������ʵʩ��̬�󶨣���̬����ζ��delete Base2ָ��ʱ��
				//ɾ�����ڴ濪ʼ��ַ����pb2�ĵ�ǰλ�á�
		//d.3)���Base2����һ������������
				//~Derice()
					//~Base2()
						//~Base()
		//d.4)Derive�����û����������������ΪBase2����������������������Ҳ��Ϊ�˸�Derive����������������
				//Ϊ�˵���~base2()��~Base()����������
	//e)��ʽ�漰���̳еģ������඼Ҫ��д���������� ������������������������������������

	Base *pbm = new Base();
	Base2 *pb222 = new Base2();
	Derive* p11212 = new Derive();

	p11212->g();
	p11212->i(); //���麯����

	Derive dddd;
	dddd.i();//ֱ�ӵ����麯��

	//Derive��ĵڶ��麯�����з�����thunk������
	//һ����������ڶ��ؼ̳���(�ӵڶ����麯����ʼ���ܾͻ���);����thisָ����������������ʵ��һ�δ��룬��δ������������
			//(1)����thisָ�룬�����������׵�ַ
			//(2)����Derive��������

	return 0;
}