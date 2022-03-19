#include<iostream>

using namespace std;

namespace _nmsp1
{
	template<typename T>
	void myfunc(T tmpvalue)
	{
		cout << "myfunc( T tmpvalue)ִ����" << endl;
	}
	
	template<typename T>
	void myfunc(T* tmpvalue)
	{
		cout << "myfunc(T* tmpvalue)ִ����" << endl;
	}

	void myfunc(int tmpvalue)
	{
		cout << " myfunc(int tmpvalue)ִ����" << endl;
	}
}

namespace _nmsp2 {
	template<typename T,typename U>     //T = const char *;  U = int;
	void tfunc(T& tmprv, U& tmprv2)     //tmprv = const char * &,tmprv2 = int &
	{
		cout << "tfunc�����汾" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;

	}

	//ȫ�ػ��汾
	template<>    //ȫ�ػ�<>����Ϊ��
	void tfunc<int, double>(int& tmprv, double& tmprv2)  //<int ,double>����ʡ�ԣ�����ʵ�ε����Ϳ����ƶϳ�T��U������
	{
		cout << "-------------------begin-------------" << endl;
		cout << "tfunc<int,double>�ػ��汾" << endl;
		cout << tmprv << endl;
		cout << tmprv2 << endl;
		cout << "------------------end---------------" << endl;
	}


	//���غ���
	void tfunc(int& tmprv, double& tmprv2)
	{
		cout << "-------------------begin-------------" << endl;
		cout << "��ͨ�����汾" << endl;
		cout << "------------------end---------------" << endl;
	}

	//��ģ����������ϵ�ƫ�ػ�  ����������ƫ�ػ���
	//template<typename U>  //�������������
	//void tfunc<double, U>(double& tmprv, U& tmprv2)
	//{
	//	//.......
	//}
	
	
	template<typename U>
	void tfunc(double& tmprv, U& tmprv2)
	{
		cout << "������tfunc<double,U>ƫ�ػ���tfunc���ذ汾" << endl;
	}

	//��ģ�巶Χ�ϵ�ƫ�ػ�   ��ʵ����Ҳ��������ƫ�ػ���
	template<typename T, typename U>     
	void tfunc(const T& tmprv, U& tmprv2)    
	{
		cout << "tfunc(cosnt T& tmprv,U& tmprv2)���ذ汾" << endl;
	}

}
int main()
{
	//�ģ�����
		//����������ģ�壩������ͬ�����ǲ����������߲��������ϲ�ͬ
		//����ģ��ͺ���Ҳ����ͬʱ����,��ʱ���԰Ѻ���������һ�����أ�����ͨ�����ͺ���ģ�嶼�ȽϺ��ʵ�ʱ�򣬱�����������ѡ����ͨ������ִ��
			//���ѡ������ʣ������⣩�ĺ���ģ��/�������������ڲ��бȽϸ��ӵ�������򡣹���

	_nmsp1::myfunc(12);  //�ƶϳ�����int ����
	char* p = nullptr;
	_nmsp1::myfunc(p);   //�ƶϳ����� char *
	_nmsp1::myfunc(12.1); 


	//�壺�ػ�
		//����(�����汾�������ڻ��ģ�����ġ���������£�д�ĺ���ģ�嶼�Ƿ����ĺ���ģ�塣
		//ʵ����tfunc<const char*, int>
		
		//�ػ����ػ��汾)�����������Ŵӷ����汾�г��������һ���Ӽ���

		//5.1)ȫ�ػ������ǰ�tfunc��������汾�е�����ģ��������þ�������������湹�ɵ�һ������İ汾(ȫ�ػ��汾��
				//ȫ�ػ�ʵ���ϵȼ���ʵ����һ������ģ�壬�����ȼ���һ����������
				//void tfunc<int, double>(int& tmprv, double& tmprv2){}   //ȫ�ػ�������
				//void tfunc(int& tmprv, double& tmprv2)				//�������ص�����
				//���������ǵ�˳������ѡ����ͨ������Ȼ��Żῼ�Ǻ���ģ����ػ��汾�����Żῼ�Ǻ���ģ��ķ����汾��
		
		//5.2)ƫ�ػ����ֲ��ػ�����
			//�����������飺һ����ģ����������ϵ�ƫ�ػ���һ����ģ�������Χ�ϵ�ƫ�ػ�
				//a)ģ����������ϵ�ƫ�ػ����������tfunc����ģ�壬��һ��ģ���������Ϊdouble ,�ڶ������ػ���
					//ʵ���ϣ���ģ���������������������ģ�岻��ƫ�ػ�,����ᵼ�±������
				//b)ģ�������Χ�ϵ�ƫ�ػ�
					//��Χ��: int -> const int, ���ͱ�С��   T -> T*  T -> T&,  T->T&&   ���T���ͣ������ͷ�Χ�϶���С�ˡ�
						//ʵ���ϣ����ں���ģ��������Ҳ������ģ�������Χ�ϵ�ƫ�ػ���������νģ�������Χ�ϵ�ƫ�ػ���ʵ���Ͼ��Ǻ������ء�
				//c) ͨ������ʵ��ģ�� ���������ϵ�ƫ�ػ�

				//�������¼ ������ģ�壬���Ǵ���ģ�������Χ�ϵ�ƫ�ػ��Լ������ϵ�ƫ�ػ���
	cout << "-----------------------------------------" << endl;

	const char* p1 = "I Love China!";
	int i = 12;
	_nmsp2::tfunc(p1, i);   //tfunc<cosnt char* ,int>

	int k = 12;
	double b = 12.2;
	_nmsp2::tfunc(k, b);


	const int k2 = 12;
	_nmsp2::tfunc(k2, b);

	double j = 18.5;
	int ii = 1;
	_nmsp2::tfunc(j, ii);
	return 0;
}