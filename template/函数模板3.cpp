#include<iostream>
#include<string>

using namespace std;


namespace _nmsp1
{
	int mf(int tmp1, int tmp2)
	{

		return 1;
	}
	int mf2(int tmp1, int tmp2)
	{

		return 10;
	}
	typedef int(*FunType)(int, int);   //����ָ�����Ͷ���
	template	<typename T, typename F = FunType>
	void testfunc(T i, T j, F funcpoint = mf)
	{
		cout << funcpoint(i, j) << endl;
	}

	template<typename T = int, typename U>
	void testfunc(U m)
	{
		T tmpvalue = m;
		cout << tmpvalue << endl;
	}
}

namespace _nmsp2
{
	//template<typename T, typename U,auto val = 100>
	template<typename T, typename U, int val = 100>  //ͬ�ϣ�������visual studio 2019�г��ִ��󣡣���
	auto Add(T tv1, U tv2)
	{
		return tv1 + tv2 + val;
	}

	template<double* p>
	void mft()
	{
		cout << "mft()ִ����" << endl;
	}
	double g_d = 1.3;   //ȫ����

	//-------------------
	//template<typename T,int value>
	template<typename, int>     //ͬ�ϣ�û���õ��Ļ����Ϳ���ʡ��
	auto Add2()
	{
		return 100;
	}

	template<class  T, typename int value>   //��typename int value)typename �������ǻ������� ��������class������
	auto Add3()
	{
		return 100;
	}
}
int main(void)
{

	//����ȱʡ����
	_nmsp1::testfunc(15, 16);
	_nmsp1::testfunc(15, 16,_nmsp1::mf2);

	_nmsp1::testfunc(12);

	cout << "�ֽ���-----" << endl;
	//�ߣ�������ģ�����
		//7.1)��������, �����漰����ģ��������� ������ģ�������������typename(class)������
			//ģ������������ǡ�������ģ���������ͨ�Ĳ���)��
			//c++17��ʼ��֧�ַ�����ģ�����Ϊauto���͡�
			//ָ��������ģ�������ֵʱ��һ������ǳ�������Ϊ�������ڱ����ʱ���Ҫ�ܹ�ȷ��������ģ�������ֵ
			//�������κ����͵Ĳ�����������Ϊ������ģ�������int ���Ϳ��� ����double float����������string�ȵȿ��ܾͲ����ԣ����� double * ����ָ�����;Ϳ��ԣ�
			//һ��������������ģ��������������£����ܲ�������
				//a)���λ���ö�����ͣ�
				//b)ָ�����ͣ�
				//c)��ֵ �������ͣ�
				//d)auto ����decltype(auto)
		//7.2)�Ƚ���ֵ��﷨
			//a)�������ͻ��Ƿ�����ģ����������������û���õ��������������ʡ��
			//b)����ǰ���������һ��typename��������ȷ��ʾһ�����ͣ�һ���ģ���йص��������ǲ���Ҫ���ε�
	cout << _nmsp2::Add<float,float>(23.3f, 11.8f) << endl;
	cout << _nmsp2::Add<float,float,800>(23.3f, 11.8f) << endl;

	_nmsp2::mft<&_nmsp2::g_d>();

	cout << _nmsp2::Add2<int, 45>() << endl;

	cout << _nmsp2::Add3<int, 45>() << endl;
	return 0;
}