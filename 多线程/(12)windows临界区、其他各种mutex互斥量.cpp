#include<iostream>
#include<mutex>
#include<thread>
#include<future>
#include<list>

#include<windows.h>


using namespace std;

//#define __WINDOWSJQ_    //����һ������,WINDOWS����
//���������Զ��ͷ�windows�µ��ٽ�������֮����LeaveCriticalSection()������������ķ���
class CWinLock {     //��RAII�ࣨResourse Acquisition is initialization�� ���ġ���Դ��ȡ����ʼ����
				//������ֻ��ָ�������࣬������RAII��
public:
	CWinLock(CRITICAL_SECTION* pCripem) {   //���캯��
		m_pCritical = pCripem;
		EnterCriticalSection(m_pCritical);
	}
	~CWinLock() {   //��������
		LeaveCriticalSection(m_pCritical);
	}
private:
	CRITICAL_SECTION *m_pCritical;
};
class A {
public:
	//���յ�����Ϣ(�������)�뵽һ�����е��߳���
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRechQueue()ִ�У�����һ��Ԫ��" << i << endl;
#ifdef __WINDOWSJQ_ 
			//EnterCriticalSection(&my_winsec);  //�����ٽ���(����)
			//EnterCriticalSection(&my_winsec);  //���ν����ٽ���(����)
			CWinLock wlock(&my_winsec);     //wlock��wlock2������RAII��
			//CWinLock wlock2(&my_winsec);     //��������Ҳû����     
			msgRecvQueue.push_back(i);
			//LeaveCriticalSection(&my_winsec);	//�뿪�ٽ���(����)
			//LeaveCriticalSection(&my_winsec);	//���ν�����������뿪��û����
#else
			std::lock_guard<std::mutex> sbguard(my_mutex);
			//std::lock_guard<std::recursive_mutex> sbguard(my_mutex);

			//testfun1();    //���������������쳣(ֻҪlock����1�ξͱ��쳣)

			//std::chrono::milliseconds timeout(100);  //100����
			//if (my_mutex.try_lock_for(timeout)) {   //�ȴ�һ�ٺ��볢�Ի�ȡ��ͷ
			//	//����100����֮���õ�����
			//	msgRecvQueue.push_back(i);
			//	my_mutex.unlock();   //������Ҫ������
			//}
			//else {
			//	//���û�õ���ͷ
			//	std::chrono::microseconds sleeptime(100);
			//	std::this_thread::sleep_for(sleeptime);
			//}
			msgRecvQueue.push_back(i);  
#endif
		}
	}
	bool outMsgLULProc(int& command) 
	{	
#ifdef __WINDOWSJQ_ 
		EnterCriticalSection(&my_winsec);
		if (!msgRecvQueue.empty()) {
			int command = msgRecvQueue.front();  //���ص�һ��Ԫ�أ��������Ԫ���Ƿ����
			msgRecvQueue.pop_front();   //�Ƴ���һ��Ԫ�أ���������
			LeaveCriticalSection(&my_winsec);

			return true;
		}
		LeaveCriticalSection(&my_winsec);

#else
		my_mutex.lock();
		if (!msgRecvQueue.empty()) {
			//��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();  //���ص�һ��Ԫ�أ��������Ԫ���Ƿ����
			msgRecvQueue.pop_front();   //�Ƴ���һ��Ԫ�أ���������
			my_mutex.unlock();

			return true;
		}
		my_mutex.unlock();
#endif
		return false;
	}

	//�����ݴ���Ϣ������ȡ�����̣߳�
	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 100000; ++i) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "outMsgLULProc()ִ�У�ȥ��һ��Ԫ��" << command << endl;
			}
			else {
				//��Ϣ����Ϊ��
				cout << " outMsgRecvQueue()ִ�У���Ŀǰ��Ϣ������Ϊ��" << i << endl;
			}
		}
		cout << "end" << endl;
	}
	A() {
#ifdef __WINDOWSJQ_ 
		InitializeCriticalSection(&my_winsec);   //���ٽ���֮ǰҪ�ȳ�ʼ��
#endif
	}
	//void testfun1() {
	//	std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
	//	//��һЩ����
	//	testfun2();    //����
	//}
	//void testfun2(){
	//	std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
	//	//����һЩ����
	//}
private:
	list<int> msgRecvQueue;   //����(��Ϣ����)��ר�����ڴ�����Ҹ����Ƿ��͹���������
	mutex my_mutex;//����һ��������(һ������������һ����)
	//std::recursive_mutex my_mutex;  //�ݹ�ʽ�Ķ�ռ������
	//std::timed_mutex my_mutex;   //����ʱ���ܵĶ�ռ��������

#ifdef __WINDOWSJQ_     //�⿪����
	CRITICAL_SECTION my_winsec;    //windwos�е��ٽ������ǳ�������c++��mutex
#endif 
};
int main() {
	//һ��windows�ٽ���
	//���´���ʵ��
		//#define __WINDOWSJQ_    //����һ������,WINDOWS����
		//#ifdef __WINDOWSJQ_     //�⿪����
		//	CRITICAL_SECTION my_winsec;    //windwos�е��ٽ������ǳ�������c++��mutex
		//#endif 
		//
		//#ifdef __WINDOWSJQ_ 
		//	EnterCriticalSection(&my_winsec);   //�����ٽ���
		//	msgRecvQueue.push_back(i);
		//	LeaveCriticalSection(&my_winsec);   //�˳��ٽ���
		//#else

	//������ν����ٽ���ʵ��
		//#ifdef __WINDOWSJQ_ 
		//	EnterCriticalSection(&my_winsec);  //�����ٽ���(����)
		//	EnterCriticalSection(&my_winsec);  //���ν����ٽ���(����)
		//	msgRecvQueue.push_back(i);
		//	LeaveCriticalSection(&my_winsec);	//�뿪�ٽ���(����)
		//	LeaveCriticalSection(&my_winsec);	//���ν�����������뿪
		//#endif
				//��ͬһ�߳���(��ͬ�߳̾ͻῨס�ȴ�)�У�windows�еġ���ͬ�ٽ���������������ٽ����Ľ���EnterCriticalSection()��
						//���Ա���ε��ã�����EnterCriticalSection()���͵ü���LeaveCriticalSection();

		//my_mutex.lock();
		//my_mutex.lock();  //���쳣����windows������
		//msgRecvQueue.push_back(i);     
		//my_mutex.unlock();
		//my_mutex.unlock();
				//��c++11�м��������ͻᱨ��������ͬһ���߳���lockͬһ����������Σ������쳣��
	//�����Զ���������
		//std::lock_guard<std::mutex>
			//std::lock_guard<std::mutex> sbguard(my_mutex);
			//std::lock_guard<std::mutex> sbguard1(my_mutex);
						//lock_guardҲ���ܵ�������

			//class CWinLock {  //���������Զ��ͷ�windows�µ��ٽ�������֮����LeaveCriticalSection()������������ķ���
			//public:
			//	CWinLock(CRITICAL_SECTION* pCripem) {   //���캯��
			//		m_pCritical = pCripem;
			//		EnterCriticalSection(m_pCritical);
			//	}
			//	~CWinLock() {   //��������
			//		LeaveCriticalSection(m_pCritical);
			//	}
			//private:
			//	CRITICAL_SECTION* m_pCritical;
			//};

			//�����class CWinLock   ������std::lock_guard<std::mutex> sbguard(my_mutex);
				//����windows���ٽ��������������ε��ø���

	//�ģ�recursive_mutex�ݹ�Ķ�ռ������
	//std::mutex:��ռ���������Լ��õ�lockʱ�����˾�lock����
	//recursive_mutex:�ݹ�Ķ�ռ������������ͬһ���̣߳�ͬһ����������α�lock()��Ч���ϱ�mutexҪ��һЩ
		//std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
		//testfun1();

		//�������recursive_mutex����Ҫ���Ǵ����Ч���ǲ��������⣬����ܲ�ʹ��
		//�ݹ���������ƣ��ݹ�̫����ܱ��쳣


	//�壺����ʱ�Ļ�����std::time_mutex��std::recursive_timed_mutex
	//std::timed_mutex :�Ǵ���ʱ���ܵĶ�ռ������

			//try_lock_for():�����ǵȴ�һ��ʱ�䡣������õ����������ߵȴ�����ʱ��û�õ���ͷ������������
			//std::chrono::milliseconds timeout(100);  //100����
			//if (my_mutex.try_lock_for(timeout)) {   //�ȴ�һ�ٺ��볢�Ի�ȡ��ͷ
			//	//����100����֮���õ�����
			//	msgRecvQueue.push_back(i);
			//	my_mutex.unlock();   //������Ҫ������
			//}
			//else {
			//	//���û�õ���ͷ
			//	std::chrono::microseconds sleeptime(100);
			//	std::this_thread::sleep_for(sleeptime);
			//}

			//try_lock_unti()��������һ��δ����ʱ��㣬�����δ��ʱ��û����ʱ����ڡ�����õ���������ô��������
								//���ʱ�䵽�ˣ�û�õ�������������Ҳ��������
									//std::chrono::milliseconds timeout(100);
									//my_mytex.try_lock_unti(chrono::steady_clock::now() + timeout);
					
	//std::recursive_timed_mutex:����ʱ���ܵĵݹ黥����
	A myobja;
	std::thread muOutnMsgObj(&A::outMsgRecvQueue, &myobja);
	std::thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myInMsgObj.join();
	muOutnMsgObj.join();
	return 0;
}