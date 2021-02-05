#include<iostream>
#include<thread>
#include<mutex>
#include<future>
using namespace std;
int mythread()   //�߳���ں���
{
	cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
	std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
	std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
	cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
	return 5;
} 
int mythread1(int mypar) 
{
		//cout << mypar << endl;
		cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
		std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
		cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		return 5;
}
//void mythread2(std::future<int>& tmpf) {
void mythread2(std::shared_future<int>& tmpf) {

	auto result = tmpf.get();
	//auto result = tmpf.get(); Ϊʲô�ڶ���get future��ĵõ��쳣����Ҫ����Ϊget��������ƣ���һ���ƶ�����
	cout << "mythread2 result = " << result << endl;
	return;
}

std::atomic<int> g_mycout = 0;   //���Ƿ�װ��һ������Ϊint�Ķ���ֵ�������ǿ��������һ��int���ͱ���һ��������g_mycout
std::mutex g_my_mytex;   //���뻥����
void mythread3() {   //�߳���ں���
	for (int i = 0; i < 100000; i++) {
		//g_my_mytex.lock();  //�û������ķ�ʽʱ��Ƚ���
		//g_mycout++;
		//g_my_mytex.unlock();
		g_mycout++;  //��Ӧ�Ĳ���ʱԭ�Ӳ��������ᱻ��ϣ�
	}
	return;
}

std::atomic<bool> g_ifend = false;   //�߳��˳���ǣ�������ԭ�Ӳ�������ֹ����д���ס�
void mythread4() {

	std::chrono::milliseconds dura(1000);  //1 ����
	while (g_ifend == false) {
		//ϵͳûҪ���˳������Ա��߳̿��Ը��Լ���ɵ�����
		cout << "thread id = " << std::this_thread::get_id() << "������..." << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "thread id = " << std::this_thread::get_id() << "���н���..." << endl;
	return;
}
int main() {
	//һ:std::future��������Ա����

	//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;
	//std::future<int> result = std::async(mythread);
	////std::future<int> result = std::async(std::launch::deferred,mythread);

	//cout << "continue....!" << endl;
	////cout << result.get() << endl;    //��������ȴ��߳�ִ����
	//
	////ö������
	//std::future_status status = result.wait_for(std::chrono::seconds(5));    //�ȴ�һ��
	//if (status == std::future_status::timeout) {  // ��ʱ���ȴ����߳�һ���ӣ�ϣ���䷵�أ����û�з��أ���ôstatus= timeout;

	//	//��ʱ����ʾ�̻߳�û��ִ����
	//	cout << "��ʱ�ˣ��̻߳�û��ִ����" << endl;
	//}
	//else if (status == std::future_status::ready) {

	//	//��ʾ�̳߳ɹ�����
	//	cout << "�̳߳ɹ�ִ����ϣ�����" << endl;
	//	cout << result.get() << endl;
	//}
	//else if (status == std::future_status::deferred) {
	//	//�ӳ�async ��std::async(std::launch::deferred,mythread);����������
	//	cout << "�̱߳��ӳ�ִ��" << endl;
	//	cout << result.get() << endl;    //�����߳��б�ִ��
	//}


	//��:std::shared_future  Ҳ�Ǹ���ģ�塣shared_future��get()�����Ǹ�������
			//std::future��������Ա������get()����ʽת������
	//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
	//std::packaged_task<int(int)> mypt(mythread1);  //�Ѻ���mythreadͨ��packaged_task��װ����
	//						//packaged_task<int(int)>  ��һ��int�Ǻ����������ͣ��ڶ����ǲ�������
	//std::thread t1(std::ref(mypt), 1);   //�߳�ֱ�ӿ�ʼִ�У��ڶ���������Ϊ�߳���ں����Ĳ�����
	//t1.join();     //�ȴ��߳�ִ����ϡ�

	////std::future<int> result = mypt.get_future();

	////bool ifcanget = result.valid();   //�ܹ��ж�result�����Ƿ���ֵ
	//////std::shared_future<int> result_s(std::move(result));   //�������ƶ�����,
	////std::shared_future<int> result_s(result.share()); //ͬ��,ִ����Ϻ�result_s����ֵ����result�����
	////ifcanget = result.valid();    //ֵ�Ѿ�Ϊ��
	//std::shared_future<int>result_s(mypt.get_future());   //ͨ��get_future����ֱֵ�ӹ�����һ��shared_future����
	//auto mythread_result = result_s.get();

	////std::thread t2(mythread2, std::ref(result_s));
	//std::thread t2(mythread2, std::ref(result_s));
	//t2.join();

	//����ԭ�Ӳ���std::atomic
	//(3.1)ԭ�Ӳ���������������
	//�����������̱߳���б����������ݣ� ���������������ݣ�����
	//�������̣߳���һ���������в�����һ���̶߳�����ֵ����һ���߳������������дֵ��
	//���߳�A
	//int tmpvalue = atomvalue;  //���atomvalue ������Ƕ���߳�֮��Ҫ����ı���
	//д�߳�B
	//atomvalue = 6;   //�ĳɻ����룬���ж���������ִ�С�

	//��ԭ�Ӳ������ɣ�����Ҫ�õ������������������������Ķ��̲߳�����̷�ʽ
	//ԭ�Ӳ��������ڶ��߳��в��ᱻ��ϵĳ���ִ��Ƭ�Ρ���ԭ�Ӳ������Ȼ�����Ч���ϸ�ʤһ�
	//�������ļ��������һ������Σ����д��룩����ԭ�Ӳ�����Ե�һ����һ��������������һ�������

	//ԭ�Ӳ�����һ��ָ���ɷָ�Ĳ�����Ҳ����˵���ֲ���״̬Ҫô����ɵģ�Ҫô��û��ɵģ������ܳ��ְ����״̬
	//std::atomic������ԭ�Ӳ�����std::atomic�Ǹ���ģ�塣��ʵstd::atomic���������������װĳ�����͵�ֵ

	//(3.2)������std::atomic�÷�����
	/*thread mytobj1(mythread3);
	thread mytobj2(mythread3);
	mytobj1.join();
	mytobj2.join();
	cout << "�����߳�ִ����ϣ����յ�g_mycout�Ľ���ǣ�" << g_mycout << endl;*/
	thread mytobj1(mythread4);
	thread mytobj2(mythread4);
	std::chrono::milliseconds dura(5000);  //5����
	std::this_thread::sleep_for(dura);
	g_ifend = true;  //��ԭ�Ӷ����д������Ȼ�߳��������н���
	mytobj1.join();
	mytobj2.join();
	cout << "����ִ����ϣ��˳�" << endl;
	cout << "I LOVE CHINA" << endl;
	return 0;

	//(3.3)�ĵã�һ������ͳ�ƻ��߼������ۼƷ���ȥ�˶��ٸ����ݰ����ۼƽ��ܵ��˶��ٸ����ݰ���
}