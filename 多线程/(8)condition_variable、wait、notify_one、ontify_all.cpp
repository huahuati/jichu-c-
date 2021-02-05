#include<iostream>
#include<thread>
#include<mutex>
#include<list>

using namespace std;
class A {
public:
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			std::unique_lock<std::mutex> sbguard1(my_mutex1);
			cout << "inMsgRechQueue()ִ�У�����һ��Ԫ��" << i << endl;
			msgRecvQueue.push_back(i);
			//����outMsgRecvQueue()���ڴ���һ��ʧ����Ҫһ��ʱ�䣬������������wait()�ȴ�����ô��ʱ���notify_one()������ܾ�û��Ч����
			my_cond.notify_one();   //���ǳ��԰�wait()���̻߳��ѣ�ִ�����֣���ôoutMsgRecvQueue()��ߵ�wait()�ͻᱻ���ѡ�
									//����֮�����������о���

			//my_cond.notify_one();  ���Ի��������̣߳�����ʵ����ֻ�ܻ���һ������Ϊ����ͬʱ�������߳��õ�����
		}	
		return;
	}

	void outMsgRecvQueue() {
		int command = 0;
		while (true) {
			std::unique_lock<std::mutex> sbguard1(my_mutex1);

			//wait������һ������
			//����ڶ�������lambda���ʽ����ֵ��true,��ôwait()ֱ�ӷ��ء�
			//����ڶ�������lambda���ʽ����ֵ��false����ôwait()�������������������������С�
					//��ô�µ�ʲôʱ��Ϊֹ��?����������ĳ���̵߳���notify_one()��Ա����Ϊֹ��
			//���wait()û�еڶ���������my_cond.wait(sbguard1��,��ô�͸��ڶ�������lambda���ʽ����falseЧ��һ����
					//��ôwait()�������������������������С�����������ĳ���̵߳���notify_one()��Ա����Ϊֹ��
			//�������߳���notify_one��������wait(ԭ����˯��/����)��״̬���Ѻ�wait�Ϳ�ʼִ���ˣ�waitִ����ʲô?
					//a)wait()���ϵĳ������»�ȡ���������������ȡ��������ô���̾Ϳ���wait()����ȴ���ȡ��
								//���wait()��ȡ��������������������ô�ͼ���ִ�С�
					//b)����(ʵ���ϻ�ȡ�����˾͵���������)
							//b.1)���wait�еڶ�������(lambda)�����ж����lambda���ʽ��
										//���lambda���ʽΪfalse,��wait�ֶԻ�����������Ȼ�������ߣ��ȴ�����
							//b.2)���lambda���ʽΪtrue����wait���أ�����������(��ʱ������������)��
							//b.3)���waitû�еڶ�����������wait���أ�������������
			my_cond.wait(sbguard1, [this] {    //һ��lambda����һ���ε��ö���(����)��Ҳ�������κ�һ���ɵ��ö���
				if (!msgRecvQueue.empty())
					return true;
				return false;
				});
			//����ֻҪ���ߵ������������������һ�������ŵġ�ͬʱmsgRecvQueue��������һ�����ݵ�
			command = msgRecvQueue.front();  //���ص�һ��Ԫ�أ��������Ԫ���Ƿ����
			msgRecvQueue.pop_front();
			cout << "outMsgRecvQueue()ִ�У�ȥ��һ��Ԫ��" << command <<"threadId = " <<std::this_thread::get_id() << endl;
			sbguard1.unlock();  //��Ϊunique_lock������ԣ����ǿ�����ʱ��unlock������������ס̫��ʱ��
			
		
			//ִ��һЩ���嶯��
			///...
			//ִ��100����
			//...
			//����outMsgRecvQueue
		}
	}
private:
	list<int> msgRecvQueue;   //����(��Ϣ����)��ר�����ڴ�����Ҹ����Ƿ��͹���������
	mutex my_mutex1;//����һ��������(һ������������һ����)
	std::condition_variable my_cond;   //����һ��������������
};
int main() {
	//һ����������std::condition_variable��wait()��notify_one()
	//�߳�A���ȴ�һ����������
	//�߳�B��ר������Ϣ����������Ϣ(����)
	//condition_variableʵ������һ���࣬��һ����������ص�һ���࣬˵���˾��ǵȴ�������ɡ�
	//���������Ҫ�ͻ���������Ϲ������õ�ʱ������Ҫ���������Ķ���
	//notify_one()ֻ�ܻ���һ���̣߳�

	//�����������������˼��


	//����notify_all()
	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);  
	//thread myOutMsgObj2(&A::outMsgRecvQueue, &myobja);     //notify_all()
	thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myOutMsgObj.join();
	//myOutMsgObj2.join();//notify_all()
	myInMsgObj.join();
	return 0;
}