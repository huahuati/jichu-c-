#include<iostream>
#include<thread>
#include<list>
#include<vector>
#include<mutex>
using namespace std;
class A {
public:
	//���յ�����Ϣ(�������)�뵽һ�����е��߳���
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRechQueue()ִ�У�����һ��Ԫ��" << i << endl;
			
			//my_mutex2.lock();  //�����������������������˳��һ��
			//my_mutex1.lock();  //ʵ�ʹ����в�һ�����ţ�������Ҫ������ͬ�����ݿ�
			//my_mutex2.lock();
			//std::lock_guard<std::mutex> sbguard1(my_mutex1);
			//std::lock_guard<std::mutex> sbguard2(my_mutex2);   
			std::lock(my_mutex1, my_mutex2);   //�൱��ÿ����������������.lock()
			std::lock_guard<std::mutex> sbguard1(my_mutex1,std::adopt_lock);
			std::lock_guard<std::mutex> sbguard2(my_mutex2, std::adopt_lock);
			msgRecvQueue.push_back(i);  //�����������i�����յ���������ֱ��Ū����Ϣ��������
			//my_mutex2.unlock();
			//my_mutex1.unlock();
		}
	}
	bool outMsgLULProc(int& command) 
	{	
		//std::lock_guard<std::mutex> sbguard(my_mutex1);   //sbguard�Ƕ�����
															//lock_guard���캯����ִ����mutex::lock();
															//lock_guard����������ִ����mutex::unlock();
		//my_mutex2.lock();
		//my_mutex1.lock();
		std::lock(my_mutex1, my_mutex2);
		if (!msgRecvQueue.empty()) {
			//��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();  //���ص�һ��Ԫ�أ��������Ԫ���Ƿ����
			msgRecvQueue.pop_front();   //�Ƴ���һ��Ԫ�أ���������
			my_mutex1.unlock();
			my_mutex2.unlock();

			return true;
		}
		my_mutex1.unlock();
		my_mutex2.unlock();

		return false;
	}

	//�����ݴ���Ϣ������ȡ�����̣߳�
	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 100000; ++i) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				command += 1;
				cout << "outMsgLULProc()ִ�У�ȥ��һ��Ԫ��" << command << endl;
			}
			else {
				//��Ϣ����Ϊ��
				cout << " outMsgRecvQueue()ִ�У���Ŀǰ��Ϣ������Ϊ��" << i << endl;
			}
		}
		cout << "end" << endl;
	}
private:
	list<int> msgRecvQueue;   //����(��Ϣ����)��ר�����ڴ�����Ҹ����Ƿ��͹���������
	mutex my_mutex1;//����һ��������(һ������������һ����)
	mutex my_mutex2;
};

int main() {

	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);  //�ڶ������������ã����ܱ�֤�߳����õ���ͬһ������
	thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myOutMsgObj.join();
	myInMsgObj.join();

	//�����������ݣ�����ʱ��ĳ���ô���ѹ���������ס���������ݣ�������
		//�����߳���������������̱߳���ȴ�����������ס���������ݣ�������
	//һ����������mutex���Ļ�������
	//�������Ǹ����������һ����������̳߳�����lock()��Ա������������ֻ��һ���߳��ܹ������ɹ���
			//�ɹ��ı�־��lock()�������أ����û���ɹ�����ô���̻Ῠ��lock()������ϵĳ���ȥ����
	//������ʹ��ҪС�ģ��������ݲ���Ҳ���٣����ˣ�û�ﵽ����Ч�������ˣ�Ӱ��Ч��

	//�������������÷�
	//(2.1)lock(),unlock()
	//���裺��lock(),�����������ݣ�Ȼ��unlock()
	//lock()��unlock()Ҫ�ɶ�ʹ��,��lock()��ȻҪ��unlock,û����һ��lock(),��ȻӦ�õ���һ��unlock();
	//��Ӧ��Ҳ���������1��lock()ȴ������2��unlock��Ҳ���������2��lockȴֻ����1��unlock(),�����ϱ���Գơ�

	//��lock()������unlock()����������Ų�
	//Ϊ�˷�ֹ����unlock(),������һ����std::lock_guard����ģ��:����unlock��Ҫ����lock_guard���Զ�unlock��
	//(2.2)std::lock_guardģ�� ������ֱ��ȡ��lock()��unlock(),����lock_guard�Ͳ�����ʹ��lock()��unlock().

	//��:����
	//��������������������������� ��������������ͷ��Ҳ�����������������ܲ�����;������JinLock��,����(YinLock)
	//�����߳�A��B
	//��1���߳�Aִ�е�ʱ������߳������������ѽ���lock()�ɹ���Ȼ������Ҫȥȥlock()������
	//�����������л�
	//��2���߳�Bִ���ˣ�����߳�����������������lock()�ɹ����߳�B��Ҫȥlock()����;
	//��ʱ�˿̣������Ͳ����ˣ�
	//��3���߳�A��Ϊ�ò��������������߲���ȥ�����к�ߴ����н�������ͷ�ĵ��������߲���ȥ�����Խ���ͷ�ⲻ����
	//��4���߳�A��Ϊ�ò��������������߲���ȥ�����к�ߴ����н�������ͷ�ĵ��������߲���ȥ����������ͷ�ⲻ����

	//(3.1)������ʾ
		//my_mutex1.lock();
		//my_mutex2.lock();

		//my_mutex2.lock();
		//my_mutex1.lock();
	//(3.2)�����������
		//ֻҪ��֤������������˳��һ�¾Ͳ����������
		//my_mutex1.lock();
		//my_mutex2.lock();

		//my_mutex1.lock();
		//my_mutex2.lock();

	//(3.3)std::lock()����ģ��::������������������ʱ��ų���
		//������һ����ס���������������ϵĻ�����(�������������˲��ޣ�1������)
		//���������ڶ���߳��� ��Ϊ����˳�����⵼�������ķ������⣻
	//std::lock()���������������һ��û��ס������������ȴ��������л���������ס�������������ߡ�
	//Ҫô��������������ס��Ҫô������������û��ס�����ֻ����һ��������һ��û���ɹ������������������ĸ�����
				//std::lock(my_mutex1, my_mutex2);
				//my_mutex1.unlock();
				//my_mutex2.unlock();
	//(3.4)std::lock_guard��std::adopt_lock����
	//std::adopt_lock����ʾ�������Ѿ�lock(),����Ҫ��std::lock_guard<sdt::mutex>����Զ����ٴν���lock()�ˡ�
			//std::lock(my_mutex1, my_mutex2);   //�൱��ÿ����������������.lock()
			//std::lock_guard<std::mutex> sbguard1(my_mutex1, std::adopt_lock);
			//std::lock_guard<std::mutex> sbguard2(my_mutex2, std::adopt_lock);

	//�ս᣺std::lock()��һ���������������������ʹ�ã�����һ��һ����)
	return 0;
}