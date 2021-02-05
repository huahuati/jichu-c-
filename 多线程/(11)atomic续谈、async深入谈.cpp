#include<iostream>
#include<mutex>
#include<thread>
#include<future>

using namespace std;
std::atomic<int> g_mycout = 0;   //���Ǹ�ԭ���������ͱ�����������ʹ�����ͱ���һ��ʹ��
void mythread() {

	for (int i = 0; i < 1000000; i++) {
		g_mycout++;//��Ӧ�Ĳ�������ԭ�Ӳ��������ᱻ��ϡ�
		g_mycout += 1;   //֧��
		//g_mycout = g_mycout + 1;   //�������
	}
	return;
}
int mythread1() {
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);   
	cout << "mythread start " << "threadId = " << std::this_thread::get_id() << endl;
	return 1;
}
int main() {
	//һ��ԭ�Ӳ���std::atomic��̸
	//һ��atomicԭ�Ӳ��������++,--,+=,&=,|=,*=   ��֧�ֵġ�

	//����std::async����̸
	//(2.1)std::async����������async��������һ���첽����

	//thread myobj1(mythread);
	//thread myobj2(mythread);
	//myobj1.join();
	//myobj2.join();
	//cout << "�����̶߳�ִ����ϣ����յ�g_mycout�Ľ����" << g_mycout << endl;
	//cout << "main start " << "threadId = " << std::this_thread::get_id() << endl;
	//std::future<int> result = std::async(std::launch::deferred,mythread1);
	//std::future<int> result = std::async(std::launch::deferred | launch::async,mythread1);
	//std::future<int> result = std::async(mythread1);
	//cout << result.get() << endl;
	
	//�ӳٵ��ò���std::launch::deferred,�Լ�std::launch::asyncǿ�ƴ���һ���߳�
	//std::thread()���ϵ��Դ���ţ���ô���ܴ����߳̾ͻ�ʧ�ܣ���ôִ��std::thread()ʱ����������ܱ�����
	//std::async()һ�㲻�д����߳�(����async�ܹ������߳�)��һ���������һ���첽����
	//std::thread()��std::async()�����ԵĲ�ͬ������async��ʱ�򲢲��������̡߳�
	//a)�����std::launch::deferred������async����ô��?
	//deferred�ӳٵ��ã����Ҳ��������߳�,�ӳٵ�future�������.get()����.wait()��ʱ���ִ��mythread(),���û�е���get����wait,�Ͳ���ִ�С�
	//b)std::launch::async��ǿ������첽���������߳���ִ�У�����ζ��ϵͳ���봴�������߳�������mythread()��
	//c)std::launch::async | std::launch::deferred
	//������� | ����ζ��async����Ϊ�����Ǵ������̲߳�����ִ�л�����û�д������̲߳����ӳٵ�����result.get()�ſ�ʼִ��������ں�����
	
	//d)�����������������async����һ����ں���������ʵ��Ĭ��ֵӦ����std::launch:async | std::launch::deferred;��c��ȫһ��
			//���仰˵��ϵͳ�����о������첽���������̣߳�����ͬ�������������̣߳���ʽ����
	//���о�����ɶ��˼��ϵͳ��ξ������첽(�������߳�)  ����ͬ�������������߳�)��ʽ���С�

	//(2.2)std::async��std::thread������
	//std::thread�����̣߳����ϵͳ��Դ���ţ���ô��������ͻᱨ�쳣
	//int mythread() { return 1;}
	//std::thread mytobj(mythread);
	//mytobj.join();
	//std::thread�����̵߳ķ�ʽ������̷߳���ֵ�����õ����ֵҲ�����ף�

	//std::async�����첽���񣬿��ܴ���Ҳ���ܲ������̣߳�����async���÷����������õ��߳���ں����ķ���ֵ��
	//����ϵͳ��Դ���ƣ�
		//(1)���std::thread�����߳�̫�࣬����ܴ���ʧ�ܣ�ϵͳ�����쳣��������
		//(2)���std::async��һ��Ͳ��ᱼ�������ϵͳ��Դ���ŵ����޷��������̵߳�ʱ��
						//std::async���ֲ��Ӷ�������ĵ��þͲ��ᴴ�����̡߳����Ǻ���˭������result.get()����������
						//��ô����첽����mythread��������ִ������get()������ڵ��߳��ϡ�
		//(3)һ���������߳��������˳���100-100

	//(2.3)std::async��ȷ��������Ľ��
	//���Ӷ��������std::async���ã���ϵͳ���о����Ƿ񴴽����߳�
	//���⽹������  std::future<int> result = std::async(mythread);д��
	//����첽���񵽵���û�б��Ƴ�ִ�У���std::launch::async ���� std::launch::deferred����
	//std::future�����wait_for����

		cout << "main start " << "threadId = " << std::this_thread::get_id() << endl;
		std::future<int> result = std::async(mythread1);
		std::future_status status = result.wait_for(std::chrono::seconds(3));
		if (status == std::future_status::deferred)
		{
			//�̱߳��ӳ�ִ���ˣ�ϵͳ��Դ�����ˣ������Ҳ���std::launch::deferred�����ˣ�
			cout << result.get() << endl;   //���ʱ��Ż�ȡ������mythread������
		}
		else {
			//����û�б��Ƴ٣��Ѿ���ʼ�����˱��̴߳����ˣ�
			if (status == std::future_status::ready) {
				//�̳߳ɹ�����
				cout << "�̳߳ɹ�ִ����ϲ����أ�" << endl;
				cout << result.get() << endl;
			}
			else if (status == std::future_status::timeout) {
				//��ʱ�̻߳�û��ִ����
				cout << "��ʱ�߳�ûִ���꣡" << endl;
				cout << result.get() << endl;
			}
		}
	return 0;
}