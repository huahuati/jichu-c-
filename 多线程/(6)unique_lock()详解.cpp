#include<iostream>
#include<list>
#include<mutex>
#include<thread>

using namespace std;
class A {
public:
	std::unique_lock<std::mutex> rtn_unique_lock()
	{
		std::unique_lock<std::mutex> tmpguard(my_mutex2);
		return tmpguard;  //�Ӻ�������һ���ֲ���unique_lock�����ǿ��Ե�
						//�������־ֲ�����tmpguard�ᵼ��ϵͳ����unique_lock���󣬲�����unique_lock������ƶ����캯����
	}
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRechQueue()ִ�У�����һ��Ԫ��" << i << endl;
			//my_mutex1.lock();   //Ҫ��lock������������unique_lock��std::adopt_lock����
			//std::unique_lock<std::mutex> sbguard1(my_mutex1,adopt_lock);
			//std::unique_lock<std::mutex> sbguard1(my_mutex1,std::try_to_lock);  //ʹ��ǰ������ǰû��lock
			//if (sbguard1.owns_lock()) {
			//std::unique_lock<std::mutex> sbguard1(my_mutex1, std::defer_lock);  //û�м�����my_mutex1
			std::unique_lock<std::mutex> sbguard1(my_mutex1);
			std::mutex* ptx = sbguard1.release();   //�����������Լ�����my_mutex1;
			msgRecvQueue.push_back(i);
		
			ptx->unlock();   //�����Լ�����unlock();
		}
	}
	bool outMsgLULProc(int& command) 
	{	
		//std::lock_guard<std::mutex> sbguard(my_mutex1);
		std::unique_lock<std::mutex> sbguard1(my_mutex1);

		//std::chrono::milliseconds dura(20000);   //1�� = 1000���� 
		//std::this_thread::sleep_for(dura);   //��Ϣһ����ʱ��

		if (!msgRecvQueue.empty()) {
		    command = msgRecvQueue.front();  //���ص�һ��Ԫ�أ��������Ԫ���Ƿ����
			msgRecvQueue.pop_front();
			return true;
		}
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
private:
	list<int> msgRecvQueue;   //����(��Ϣ����)��ר�����ڴ�����Ҹ����Ƿ��͹���������
	mutex my_mutex1;//����һ��������(һ������������һ����)
	mutex my_mutex2;
};
int main() {
	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);  
	thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myOutMsgObj.join();
	myInMsgObj.join();


	//һ����unique_lockȡ��lock_guard
	//unique_lock�Ǹ���ģ��,�����У�һ��lock_gurad(�Ƽ�ʹ��);lock_guardȡ����mutex��lock��unlock();
	//unique_lock��lock_guard���ܶ�
	//����unique_lock()�ĵڶ�������
		//lock_guard���Դ��ڶ���������std::lock_guard<std::mutex> sbguard(my_mutex,adopt_lock);//adopt_lock�������
	//(2.1)std::adopt_lock:��ʾ�������Ѿ���lock��(����Ҫ�ѻ�������ǰlock�ˣ�����ᱨ�쳣)��
			//std::adopt_lock��ǵ�Ч������ ������÷��߳��Ѿ�ӵ���˻��������Ȩ(�Ѿ�lock()�ɹ���);
			//֪ͨlock_guard()����Ҫ�ڹ��캯����lock����������ˡ�

	//unique_lockҲ���Դ�std::adopt_lock��ǣ�������ͬ�����ǲ�ϣ��unique_lock()�Ĺ��캯����lock���mutex
	//(2.2)std::try_to_lock
	//�᳢����mutex��lock()ȥ�������mutex�������û�������ɹ���Ҳ���������أ���������������
	//��try_to_lockd��ǰ�����Լ�������ȥlock��

	//(2.3)std::defer_lock
	//ʹ��ǰ�᣺������lock(),����ᱨ�쳣��
	//defer_lock����˼���ǣ���û�и�mutex��������ʼ��һ��û�м�����mutex��
	//����defer_lock�Ļ��⣬����һЩunique_lock����Ҫ��Ա����

	//����unique_lock�ĳ�Ա����
	//(3.1)lock()
			///std::unique_lock<std::mutex> sbguard1(my_mutex1, std::defer_lock);  //û�м�����my_mutex1
			///sbguard1.lock();   //�����Լ�unlock()
	//(3.2)unlock();
			//std::unique_lock<std::mutex> sbguard1(my_mutex1, std::defer_lock);  //û�м�����my_mutex1
			//sbguard1.lock();   //�����Լ�unlock()
			//����һЩ�������
			//sbguard1.unlock();
	//try_lock(),���Ը�����������������ò��������򷵻�false,����õ�����������true,�������������
			//if (sbguard1.try_lock() == true)   //����true��ʾ�õ�����
			//{
			//	msgRecvQueue.push_back(i);

			//}
	//(3.4)release(),�������������mutex����ָ�룬���ͷ�����Ȩ��Ҳ�����������unique_lock��mutex�����й�ϵ
				//�ϸ�����unlock()��release()�����𣬲�Ҫ����
				//���ԭ��mutex�����ڼ���״̬���������νӹܹ��������������(release���ص���ԭʼ��mutexָ��)
					//std::unique_lock<std::mutex> sbguard1(my_mutex1);
					//std::mutex* ptx = sbguard1.release();   //�����������Լ�����my_mutex1;
					// ptx->unlock();

	//Ϊʲô��ʱ����Ҫunlock():��Ϊ��lock��ס�Ĵ����Խ�٣�ִ��Խ�죬������������Ч��Խ��
			//����ס����Ķ��٣���Ϊ���� "����" ������һ���ô�ϸ��������
	//a)��ס�Ĵ����٣�������Ƚ�ϸ��ִ��Ч�ʸ�
	//b)��ס�Ĵ���࣬���Ƚд֣�ִ��Ч�ʵ�
	//ѧ�ᾡ��ѡ��������ȵĴ�����б���������̫ϸ������©���������ݵı���������̫�֣�Ӱ��Ч�ʡ�

	//�ģ�unique_lock����Ȩ�Ĵ���
		//std::unique_lock<std::mutex> sbguard1(my_mutex1);   //����Ȩ����
			//sbguard1ӵ��my_mutex1������Ȩ
		//sbguard1���԰��Լ���mutex(my_mutex1)������Ȩת�Ƹ�������unique_lock����
		//���ԣ�unique_lock�������mutex������Ȩ������ "����ת��" ,���ǲ��ܸ���
			//std::unique_lock<std::mutex> sbguard1(my_mutex1)
			//std::unique_lock<std::mutex> sbguard2(sbguard1)   //��������Ȩ�ǷǷ���
			//std::unique_lock<std::mutex> sbguard2(std::move(sbguard1)) ;  //�ƶ����壬
						//�൱��sbguard2��my_mutex1�󶨵�һ���ˣ�����sbguard1ָ��գ�sbguard2ָ����my_mutex1��

	//a)std::move
	//b)return unique_lock<std::mutex>
			//std::unique_lock<std::mutex> rtn_unique_lock()
			//{
			//	std::unique_lock<std::mutex> tmpguard(my_mutex2);
			//	return tmpguard; 
			//			
			//}
	return 0;
}