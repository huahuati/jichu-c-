#include<iostream>
#include<string>
using namespace std;

namespace _nmspl {

	//��ģ�嶨��
	template<typename T>   //T ������ģ�����,��ʾmyvector��������������Ԫ������
	class myvector        //myvector���Գ�Ϊ����������ģ�壬myvector<T>���Գ�Ϊ��������myvector������������ţ���ʾ�ľ���һ�����������ˣ�
	{
	public:
		typedef T* myiterator;   //������
	public:
		myvector();   //���캯��
		myvector& operator=(const myvector&);  //��ֵ���������
		//myvector<int>& operator=(const myvector&);  //��ֵ���������  ,ͬ��
		myvector( T tmpt)
		{
			
		}
	public:
		void myfunc()
		{
			cout << "myfunc()������" << endl;
		}


		static void mystaticfunc()
		{
			cout << "mystaticfunc()������" << endl;
		}
	public:
		myiterator mybegin(); //��������ʼλ��
		myiterator myend();   //����������λ��
	};
	

	//��ģ��ʵ��
	template<typename T>
	myvector<T>::myvector()   //���⹹�캯����ʵ��
	{
		
	}
}

namespace _nmsp2
{

	template<typename T>
	struct A
	{
		A(T val1, T val2)
		{
			cout << "A::A(T val1, T val2)ִ����!" << endl;
		}

		A(T val1)
		{
			cout << "A::A(T val1)ִ����!" << endl;
		}
	};
	
	template<typename T>  //�Զ����ƶ�ָ��
	A(T)->A<T>;

}

namespace _nmsp3 {
	template<typename T>
	struct B
	{
		T m_b;
	};

	template<typename T>   //�Զ����ƶ�ָ��
	B(T)->B<T>;
}
namespace _nmsp4 {
	template<typename T>
	struct B
	{
		T m_b;
		T m_b1;
	};

	template<typename T>   //�Զ����ƶ�ָ��
	B(T,T)->B<T>;
}
int main()
{
	//һ������ģ��Ļ����淶��ģ��������ƶ�
		//��ģ�壺�ǲ������ģ�ߣ�ͨ��������ģ����������ɾ�����࣬Ҳ����ʵ����һ���ض�����
		//vecotr<int>,������ģ���Ŀ�ģ����ٴ�������
		//(1.1)��������
			//myvector���Գ�Ϊ����������ģ�壬myvector<T>���Գ�Ϊ��������myvector������������ţ���ʾ�ľ���һ�����������ˣ�
			//��ģ���У�ֻ�б����õĳ�Ա�������������Ż��������Щ������ʵ��������(��̬����Ҳ��)

	_nmspl::myvector<int> tmpvec;        //T���滻��int
	tmpvec.myfunc();					  //������ͨ��Ա����
	_nmspl::myvector<string>::mystaticfunc();

		//(1.2) ģ��������ƶ�
			//c++17�У���ģ�������ģ�����Ҳ���ƶ��ˡ�
			
	_nmspl::myvector tmpvec2(12);    //����ָ��ģ�������
	//_nmspl::myvector<int> tmpvec2(12);   //ͬ��
	tmpvec2.myfunc();

		//(1.3)�ƶ�ָ�ϣ�deduction guide)��Ҫ�˽�
			//c++17�¸����Ҫ�������ƶ���ģ�����ʱ�ṩ�ƶ�ָ��
			//(1.3.1)��ʽ���ƶ�ָ��
					//�����ģ��A��ÿ�����캯��������һ����ʽ��ģ������ƶϻ��ƴ��ڣ�������ƣ�����Ϊ��ʽ���ƶ�ָ��
					//typename<typename T>
					// A(T,T)->A<T>;
					// ������ -> ��ಿ�����ݻ�����ʽʱ�����ƶϳ� -> �Ҳ�����ͣ��Ҳ�����Ҳ����Ϊ��ָ�����͡�
					// -> ��ಿ�֣����ƶ�ָ������Ӧ�Ĺ��캯��(ע�⹹�캯����ֻ���й��캯���ſ���)�ĺ����������������֮���á������ָ�
					// -> �Ҳಿ�֣� ��ģ����������һ�������ţ�����������ģ���������
					// �����ƶ�ָ�ϵĺ��壺���õ��ô����������Ĺ��캯��ͨ����ģ��A������ض���ʱ���������ṩ�Ĺ��캯����ʵ�����ƶ���ģ��A��ģ���������
				//һ�仰���ƶ�ָ�ϵĴ�����������ñ����� �ܹ���ģ������������ƶϳ���
				//����
					//template<typename T>
					//A(T,T) -> A<double>;
					//��ô A obj1(15,16);  ������   �൱��A<double> aobj1(15,16);
			
			//(1.3.2) �Զ�����ƶ�ָ��
				//_nmsp3::B bobj3{15};   �������ԭ��
					//a)��B�Ǿۺ��࣬�ǿ���ͨ��{}��ʼ����
					//b)B bobj3{15}  ������ʽ���þ��൱�ڵ�������ģ��B�Ĵ�һ������{15}�Ĺ��캯����������ģ��B�в����ڹ��캯��
					//c)��Ϊ 	template<typename T> B(T)->B<T>;�ƶ�ָ�ϵĴ��ڣ�������������ģ��B��һ�������Ĺ��캯��ʱ���ƶϳ���������ΪB<T>
								//���ԣ������ƶϳ���������ΪB<int>���͡�
	//(1.3.1)		
	_nmsp2::A aobj1(5, 1);  //�Զ�ʵ������ A<int>

	_nmsp2::A aobj2(12.8);

	//_nmsp2::A* aobj3 = NULL;   //���������ƶ�

	//(1.3.2)
	_nmsp3::B<int> bobj1;			 //��Ҫ��ȷָ��ģ���������
	_nmsp3::B<int> bobj2{ 15 };	 //�����ó�ʼ���б�ķ�ʽ���������bobj2,��Ա����m_b = 15;

	_nmsp3::B bobj3{15};     //��Ϊ�Զ������ƶ�ָ�ϣ����Բ�����ȷָ��ģ���������
	
	_nmsp4::B bobj4{ 15,16 };
	return 0;
}