#include<iostream>

using namespace std;

class A {
public:
	int a;
	A() {
		cout << "A::A()��thisָ����" << this << endl;
	}

	void funA() {
		cout << "A::funA()��thisָ����" << this << endl;
	}
};

class B {
public:
	int b;
	B() {
		cout << "B::B()��thisָ����" << this << endl;
	}
	void funB() {
		cout << "B::funcB()��thisָ����" << this << endl;
	}
};

class C : public A, public B
{
public:
	int c;
	C() {
		cout << "C::C()��thisָ����" << this << endl;
	}
	void funC() {
		cout << "C::funcC()��thisָ����" << this << endl;
	}
};
int main() {

	//thisָ�����:���ؼ̳�
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;

	C myc;
	myc.funA();
	myc.funB();
	myc.funC();

	//�����������������Ӷ���ġ�
	//���������ֻ��һ������̳еĻ�����ô������������ĵ�ַ�ͻ������ĵ�ַ��ͬ
	//������������ͬʱ�̳ж�����࣬��ô��
		//��һ�������Ӷ���Ŀ�ʼ��ַ�����������Ŀ�ʼ��ַ��ͬ
		//������Щ�����Ӷ���Ŀ�ʼ��ַ�����������Ŀ�ʼ��ַ��������?�Ǿ͵İ�ǰ����Щ���������ռ�õ��ڴ�ռ�ɵ���

	//�ܽ�:�����Ǹ�����ĳ�Ա���������thisָ��ͻᱻ�������Զ������������ڴ沼���У���Ӧ������������ʼ��ַ����ȥ��
	return 0;
}