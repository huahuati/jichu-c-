#include<iostream>
using namespace std;

namespace _namel
{
	class A
	{
	public:
		int m_i;   //��Ա����
		A(){}
		virtual void func() {}
		~A() {}
	};
	void func()
	{
		//��new ˵��
		//(1.1)new�����ʱ�Ӳ������ŵĲ��
		//(1.1.1)����Ǹ����࣬��ô��������д��ûʲô���������У������ܹ�дһ������
		//(1.1.2)��A���г�Ա������:
				//�����ŵĳ�ʼ�����һЩ�ͳ�Ա�����йص��ڴ���0������������������ڴ�ȫ����0��
						//���麯����ʱ���麯��ָ�벻�ᱻ����
		//(1.1.3)//����A�й��캯������������д���õ��Ľ��һ���ˡ�
		
		//(2.2)new����ɶ
		//new ���Խйؼ���/ ������
		//new������������:һ���ǵ���operator new ��һ���ǵ�������A�Ĺ��캯��
		A* pa = new A();
			//����A* pa = new A();�ķֽ�;
				//operator new ();  //����
					//_malloc();  c�����е�malloc
						//A::A();  //�й��캯���͵���

		delete pa;
			//����delete pa �ķֽ�
		//A::~A()  ��������
			//operator delete() ����
				//free();  c�����е�free()����

		//(2.3)malloc����ɶ
		//�ܸ��ӵģ���������
		A* pa2 = new A;

		int* p3 = new int;   //��ֵ���
		int* p4 = new int(); //��ֵΪ��
		int* p5 = new int(100);	//��ֵ100
		
		//

		int abc;
		abc = 6;

	}
}
int main()
{
	_namel::func();
	return 0;
}