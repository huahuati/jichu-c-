#include<iostream>
#include<string>
#include<thread>
#include<list>
#include<mutex>
using namespace std;
std::mutex resource_mutex;
std::once_flag g_flag;  //���Ǹ�ϵͳ����ı��
class MyCAS  //����һ��������
{
	static void CreateInstace()  //ֻ������1�εĺ���
	{
		m_instance = new MyCAS();
		static CGarhuishou c1;
	}
private:
	MyCAS() {}  //˽�л��Ĺ��캯��

private:
	static MyCAS* m_instance;  //��̬��Ա����
public :
	static MyCAS* GetInstance() {
		//���Ч�ʡ�
		//a)���if (m_instance != NULL),������������϶���ʾm_instance�Ѿ���new����
		//b)���if(m_instance == NULL),������m_instance һ��û��new����

		if (m_instance == NULL) {//˫������(˫�ؼ��)

			std::unique_lock<std::mutex> mymutex(resource_mutex);   //�Զ�����
			if (m_instance == NULL)
			{
				m_instance = new MyCAS();
				static CGarhuishou cl;  //����delete m_instance
			}
		}
		//std::call_once(g_flag, CreateInstace);    //�����߳�ͬʱִ�е��������һ���߳�Ҫ������һ���߳�CreateInstace��ִ����ϡ�
		return m_instance;
	}

	class  CGarhuishou//�������࣬�����ͷŶ���
	{
	public:
		~CGarhuishou()  //�������������
		{
			if (MyCAS::m_instance) {
				delete MyCAS::m_instance;
				MyCAS::m_instance = NULL;
			}
		}
	};

	void func() {
		cout << "����" << endl;
	}
};
MyCAS* MyCAS::m_instance = NULL;
//�߳���ں���
void mythread() {
	cout << "�ҵ��̴߳��뿪ʼִ����" << endl;
	MyCAS *p_a = MyCAS::GetInstance();    //������ܾͻ������⡣
	cout << "�ҵ��߳�ִ�������" << endl;
	return;
}
int main() {
	//һ�����ģʽ���̸
	//"���ģʽ":�����һЩд��(��Щд���ֳ���д������ôһ��):������ά���������ܷ��㣬���Ǳ��˽ӹܣ��Ķ����붼���ʹ�ࡣ
	//��"���ģʽ"  ����д�����Ĵ���ܻ�ɬ����head first��
	//Ӧ���ر�����Ŀ��ʱ�� ����Ŀ�Ŀ������顢ģ�黮�־��飬�ܽ���������ģʽ(���п������󣬺������ۺ��ܽ�)
	//�й�ʽ���ģʽ����̫һ��������һ������(��Ŀ)�����ģʽ���ף�һ��СС����Ŀ���ǵ�ʹ�����ģʽ����ĩ���á�
	//���ģʽ�϶��ж��ص��ŵ㣬Ҫ��ѧ���ã���Ҫ�������У�����Ӳ�ס�

	//�����������ģʽ
	//�������ģʽʹ��Ƶ�ʱȽϸߡ�
	//������������Ŀ�У���ĳ������ĳЩ������࣬���ڸ���Ķ���ֻ�ܴ���1�������˴������ˡ�
	//������(������)
	MyCAS* p_a = MyCAS::GetInstance();  //����һ�����󣬷��ظ��ࣨMyCAS�������ָ��
	//MyCAS* p_b = MyCAS::GetInstance();  //p_b��p_aָ��Ķ�����ͬ
	p_a->func();
	MyCAS::GetInstance()->func(); //��װ�ص�����װ��

	//�����������ģʽ��������������������
	//���ٵ����⣺��Ҫ�������Լ��������̣߳����������̣߳���������MyCAS���������Ķ��������߳̿��ܲ�ֹһ����������������
	//���ܻ�����GetInstance()���г�Ա����Ҫ���⡣
	
	//��Ȼ�������̶߳���ͬһ����ں�������ǧ���ס�����������̣߳�������������������̣�����ͨ·��ͬʱ��ʼִ��mythread���������

	std::thread mytobj1(mythread);
	std::thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();

	//�ģ�std::call_one();  c++ 11 ����ĺ���,�ú����ĵڶ���������һ��������a()��
	//call_once�������ܹ���֤����a()ֻ�ܱ�����һ�Ρ�
	//call_once�߱���������������������Ч���ϣ��Ȼ��������ĵ���Դ���٣���
	//call_once()��Ҫ��һ����ǽ��ʹ�ã������� std::once_flag;   once_flag��һ���ṹ
	//call_once()����ͨ����������������Ӧ�ĺ���a()�Ƿ�ִ�У�����call_once()�ɹ���call_one�����Ͱ�����������Ϊ�ѵ��õ�״̬��
	//����ٴε���call_one(),ֻҪonce_flag������Ϊ��"�ѵ���"״̬����ô��Ӧ�ĺ���a()�Ͳ����ٴ�ִ���ˡ�
	
	//�ܽ᣺���������߳��оͰ�MyCAS::GetInstance()����ĳ�ʼ������ȫ�����ã�Ȼ�����߳�ֻ�Ǹ���ʹ�á�
	return 0;
}