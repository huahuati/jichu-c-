#include<iostream>
#include<thread>
#include<list>
#include<vector>
using namespace std;
//vector<int> g_v = { 1,2,3 };  //��������,ֻ��
//�߳���ں���
//void myprint(int inum) {
//	cout << "myprint�߳̿�ʼִ���ˣ��̱߳�� = " << inum << endl;
//	//  ... �ɸ�������
//	cout << "myprint�߳�ִ�н����ˣ��̱߳�� = " << inum << endl;
//	return;
//
//}
//void myprint1(int inum) {
//cout << "idΪ" << std::this_thread::get_id() << "���߳� ��ӡg_v��ֵ" << g_v[0] << g_v[1]<< g_v[2]<<endl;
//
//}

class A {
public:
	//���յ�����Ϣ(�������)�뵽һ�����е��߳���
	void  inMagRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			cout << "inMsgRechQueue()ִ�У�����һ��Ԫ��" << i << endl;
			msgRecvQueue.push_back(i);  //�����������i�����յ���������ֱ��Ū����Ϣ��������
		}
	}
	//�����ݴ���Ϣ������ȡ�����̣߳�
	void outMsgRecvQueue() {
		for (int i = 0; i < 100000; ++i) {
			if (!msgRecvQueue.empty()) {
				//��Ϣ���в�Ϊ��
				int command = msgRecvQueue.front();  //���ص�һ��Ԫ�أ��������Ԫ���Ƿ����
				msgRecvQueue.pop_front();   //�Ƴ���һ��Ԫ�أ���������
				//����Ϳ��Ǵ�������
			}
			else {
				//��Ϣ����Ϊ��
				cout << " outMsgRecvQueue()ִ�У���Ŀǰ��Ϣ������Ϊ��" << i <<endl;
			}
		}
		cout << "end" << endl;
	}
private:
	list<int> msgRecvQueue;   //����(��Ϣ����)��ר�����ڴ�����Ҹ����Ƿ��͹���������
};

int main() {

	//һ�������͵ȴ�����߳�
	//vector<thread> mythreads;
	////����10���̣߳��߳���ں���ͳһʹ��myprint��
	////a)����߳�ִ��˳�����ҵģ�������ϵͳ�ڲ����̵߳����е��Ȼ����й�
	////b)���̵߳ȴ��������߳�ִ�н�����������߳̽������Ƽ�ʹ��join��д����������д���ȶ��ĳ���
	////c��thread������뵽��������������������thread�������飬�������һ�δ����������̲߳��Դ����߳̽��й���ܷ��㡣

	//for (int i = 0; i < 10; i++) {
	//	mythreads.push_back(thread(myprint, i));   //����10���̣߳�ͬʱ��10���߳��Ѿ���ʼִ��
	//}
	//for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter) {
	//	iter->join();   //�ȴ�10���̶߳�����
	//}

	//��:���ݹ����������
	//(2.1)ֻ�������ݣ��ǰ�ȫ�ȶ��ģ�����Ҫ�ر�Ĵ����ֶΡ�ֱ�Ӷ��Ϳ��ԡ�
	//(2.2)�ж���д��2���߳�д��8���̶߳����������û���ر�Ĵ�����ô����϶�����
	//��򵥵Ĳ�������������ʱ����д��д��ʱ���ܶ���2���̲߳���ͬʱд��8���̲߳���ͬʱ����
	//����д�Ķ�����10С�������������л������¸��ֹ������鷢��������ܵĹ������黹�Ǳ�����
	//(2.3)��������
	//���ݹ���
	//����--��֤  �� T123  ��10����Ʊ������Ʊ     1,2����      ͬʱ��Ҫ��     99��
	//vector<thread> mythreads;
	//for (int i = 0; i < 10; i++) {
	//	mythreads.push_back(thread(myprint1, i));   //����10���̣߳�ͬʱ��10���߳��Ѿ���ʼִ��
	//}
	//for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter) {
	//	iter->join();   //�ȴ�10���̶߳�����
	//}

	//�����������ݵı�����������
	//������Ϸ�������������Լ��������̣߳�һ���߳��ռ���������һ�����ִ�����ҷ����������������������д��һ�������С�
	//����һ���̴߳Ӷ�����ȡ����ҷ����������������Ȼ��ִ�������Ҫ�Ķ���

	//׼���ó�Ա������Ϊ�̺߳����ķ�����д�̣߳�

	//���뻯������⣺����һ��c++������̱߳���������������ĵ�һ������������� ***������***
	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);  //�ڶ������������ã����ܱ�֤�߳����õ���ͬһ������
	thread myInMsgObj(&A::inMagRecvQueue, &myobja);
	myOutMsgObj.join();
	myInMsgObj.join();

	cout << "I LOVE CHINA! " << endl;   //���ִ��
	return 0;
}