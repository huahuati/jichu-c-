#include<iostream>
#include<string>
#include<thread>
using namespace std;

class A {
public:
	mutable int m_i;
	//����ת�����캯�������԰�һ��intת������a����
	A(int a) :m_i(a) { 
		cout << "A::A(int a) ���캯��ִ��" << this << "threadid = " << std::this_thread::get_id << endl; 
	}
	A(const A &a):m_i(a.m_i)
	{ 
		cout << "A::A(const A &a) �������캯��ִ��" << this << "threadid = " << std::this_thread::get_id << endl; 
	}
	~A() { cout << "A::~A()��������ִ��" << this << "threadid = " << std::this_thread::get_id << endl; }

	void thread_work(int num) {
		cout <<"���߳�thrad_workִ��" <<this << "threadid = " << std::this_thread::get_id << endl;

	}
};

//void myprint(const int&i, char* pmybuf) {
//	cout << i << endl;   //detach��ʱ��i������mvar�����ã�ʵ����ֵ���ݣ���ô������Ϊ��
//						//�������߳�detach�����̣߳���ô���߳�����iֵ��Ȼ�ǰ�ȫ�ġ�
//	cout << pmybuf << endl;  //detach���߳�ʱ��ʹ��ָ��һ����������
//	return;
//}

//void myprint(const int& i, const string &pmybuf) {
//	cout << i << endl;
//	cout << pmybuf.c_str() << endl;  
//	return;
//}
//void myprint(const int& i, const A& pmybuf){
//	cout << &pmybuf << endl;   //�����ӡ����pmybuf����ĵ�ַ
//	return ;
//
//}

//void myprint2(const A& pmybuf) {
//	pmybuf.m_i = 199;   //�����޸ĸ�ֵ����Ӱ�쵽main����
//	cout << "���߳�myprint2�Ĳ�����ַ��" << &pmybuf << "threadid = " << std::this_thread::get_id << endl;
//}
//
//void myprint2( A& pmybuf) {   //ʹ��std::red�����ü�const
//	pmybuf.m_i = 199;   //�����޸ĸ�ֵ����Ӱ�쵽main����
//	cout << "���߳�myprint2�Ĳ�����ַ��" << &pmybuf << "threadid = " << std::this_thread::get_id << endl;
//}

//void myprint2(unique_ptr<int> pzn) {   //����ֻ��ָ���߳�ʱ��ʹ��unique_ptr,��ʹ����move����ʱ������ʹ��detach()
//
//}
int main() {
	//һ��������ʱ������Ϊ�̲߳���
	//(1.1)Ҫ���������(����1)
		//�����̺߳����е� char * �ĳ�  const string &
	//(1.2)Ҫ���������(����2)
	//��ʵһ��ֻҪ����ʱ�����A�������Ϊ�������ݸ��̣߳���ô��һ���ܹ������߳�ִ�����ǰ��
	//���̺߳����ĵڶ������������������Ӷ�ȷ������detach()���߳�Ҳ��ȫ����
	//(1.3)�ܽ�
	//a)������int���ּ����Ͳ��������鶼��ֵ���ݣ���Ҫ�����á���ֹ������֦��
	//b)�����������󣬱�����ʽ����ת����ȫ�����ڴ����߳����һ�й�������ʱ��������Ȼ���ں������������������ӣ�
			//����ϵͳ����๹��һ�ζ���,����ṹ�����ζ���
	//�ռ����ۣ�
	//c)���鲻ʹ��detach()��ֻʹ��join()�������Ͳ����ھֲ�����ʵЧ�����̶߳��ڴ�ķǷ��������⡣

	//������ʱ������Ϊ�̲߳���������
	//(2.1)�߳�ID���id�Ǹ����֣�ÿ���߳�(���������̻߳������߳�)ʵ���϶���Ӧ��һ�����֣�����ÿ���̶߳�Ӧ�����ֶ���ͬ��
				//Ҳ����˵����ͬ���̣߳������߳�id�����֣���Ȼ�ǲ�ͬ�ġ�
	//�߳�id������c++��׼����ĺ�������ȡ��std::this_thread::get_id()����ȡ
	//(2.2)��ʱ������ʵ��ץ��

	//�������������ֻ��ָ����Ϊ�̲߳���
	//std::red ����

	//�ģ��ó�Ա����ָ�����̺߳���   operator()
	//int mvar = 1;
	//int& mvary = mvar;
	//char mybuf[] = "this is a test!";
	////thread myobj(myprint, mvar, mybuf);  //mybuf����ʲôʱ��ת����string�ģ�
	//						//��ʵ�ϴ��ڣ�mybuf��������(main����ִ������)��ϵͳ����mybufȥתstring�Ŀ����ԡ�
	//thread myobj(myprint, mvar, string(mybuf)); // ���ֱ�ӽ�mybufת����string�������һ�����Ա�֤���߳����ÿ϶���Ч�Ķ���
	////myobj.join();



	//int mvar = 1;
	//int mysecondpar = 12;
	////thread myobj(myprint, mvar, mysecondpar);   //û����ʱ�������߳��еľֲ�������ܱ��ͷ�
	//thread myobj(myprint, mvar, A(mysecondpar));//ϣ��mysecondparת��A���Ͷ��󴫵ݸ�myprint�ĵڶ�������
	//							//��detachʱ���ڴ����̵߳�ͬʱ������ʱ����ķ������ݲ����ǿ��еġ�
	//
	////myobj.join();




	//cout << "���߳�id��" << std::this_thread::get_id << endl;
	//int mvar = 1;
	//std::thread myobj(myprint2, A(mvar));
	////myobj.join();
	//myobj.detach();



	//A myobj(10);   //����һ�������
	//thread  mytobj(myprint2, myobj);  //myobj���������Ϊ�̲߳���
	//mytobj.join();
	//mytobj.detach();
	//cout << "I LOVE CHINA" << endl;


	//A myobj(10);   //����һ�������
	//thread  mytobj(myprint2, std::ref(myobj));  //myobj���������Ϊ�̲߳���
	/*unique_ptr<int> myp(new int(100));
	std::thread mytobj(myprint2, std::move(myp));*/

	A myobj(10);
	thread mytobj(&A::thread_work, myobj, 15);  //��һ�������ǳ�Ա�����ĵ�ַ���ڶ��������������
												//�������ǳ�Ա�����Ĳ���
	mytobj.join();
	//mytobj.detach();
	cout << "I LOVE CHINA" << endl;
	return 0;
}