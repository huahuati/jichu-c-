#include<iostream>
#include<thread>
#include<mutex>
#include<future>
using namespace std;
//class A {
//public:
//	int mythread(int mypar)   //�߳���ں���
//	{
//		cout << mypar << endl;
//		cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
//		std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
//		std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
//		cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
//		return 5;
//	}
//};
//int mythread()   //�߳���ں���
//{
//	cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
//	std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
//	std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
//	cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
//	return 5;
//}
//int mythread(int mypar) 
//{
//		cout << mypar << endl;
//		cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
//		std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
//		std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
//		cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
//		return 5;
//}
void mythread(std::promise<int> &tmpp,int calc)     //ע���һ������
{
	//��һϵ�и��ӵĲ���
	calc++;
	calc *= 10;
	std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
    std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��

	//��������
	int result = calc;    //������
	tmpp.set_value(result);    //����ұ��浽��tmpp��������С�
	return;
}
void mythread2(std::future<int>& tmpf) {

	auto result = tmpf.get();
	cout << "mythread2 result" << result << endl;
	return;
}
int main() {
	//һ��std::async��std::future������̨���񲢷���ֵ
	//ϣ���̷߳���һ�������
	//std::async �Ǹ�����ģ�壬��������һ���첽������������һ���첽����֮�󣬷���һ��std::future����,std::future�Ǹ���ģ��
	//ʲô�С�����һ���첽���񡱣������Զ�����һ���̲߳���ʼִ�ж�Ӧ���߳���ں���������һ��std::future����
	//���std::future������߾ͺ����߳���ں��������صĽ�����̷߳��صĽ����������ͨ������future����ĳ�Ա����get()����ȡ�����
	//"future"����������˼��Ҳ�ƺ�std::future�ṩ��һ�ַ����첽��������Ļ��ƣ�����˵��������û�а취�����õ���
						//���߳�ִ����ϵ�ʱ�򣬾��ܹ��õ�����ˣ���
			//future���ռ���⣺���future(����)��ᱣ��һ��ֵ���ڽ�����ĳ��ʱ���ܹ��õ���

	//���г���ͨ��std::future�����get()��Ա�����ȴ��߳�ִ�н��������ؽ��
	//���get()������ţ�����õ������ķ���ֵ�Ĳ����ݣ����õ�ֵ�͵ȴ���֪���õ�ֵΪֹ��
	//ͨ��������std::async()����һ���������Ĳ�����������std::launch����(ö������),�������һЩ�����Ŀ��;
		//a)std::launch::deferred:��ʾ�߳���ں������ñ��ӳٵ�std::future��wait()����get()��������ʱ��ִ�С�
		//���wait����get()û�б����ã���ô�̻߳�ִ����
				//ʵ�����̸߳�����û�д�����������ִ�У�
		//std::launch::deferred���ӳٵ��ã�����û�д������̣߳��������߳��е��õ��߳���ں���;

		//b)std::launch::async,�ڵ���async������ʱ��Ϳ�ʼ�����̡߳�
					//async()������Ĭ��ʹ�õľ���std::launch::async
	//A a;
	//int temper = 12;

	//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
	////std::future<int> result = std::async(mythread);   //����һ���߳̿�ʼִ�У��󶨹�ϵ;������������
	////std::future<int>result = std::async(std::launch::deferred,&A::mythread, &a, temper);  //��Ա������д�����ڶ��������ĳ�Ա���ã����ܱ�֤�߳����õ���ͬһ������
	//std::future<int>result = std::async(std::launch::async,&A::mythread, &a, temper);
	//cout << "contine....!" << endl;
	//int def;
	//def = 0;
	//cout << result.get() << endl;   //��������ȴ�mythread()ִ����ϣ��õ������
	////cout << result.get() << endl;   //get()ֻ�ܵ���һ��

	////result.wait();  //�ȴ��̷߳��أ��������ؽ����
	//cout << "I LOVE CHINA" << endl;


	//����std::packaged_task:������񣬰������װ����
	
	//�Ǹ���ģ�壬����ģ������Ǹ��ֿε��ö���ͨ��packaged_task���ɸ��ֿɵ��ö����װ���������㽫����Ϊ�߳���ں��������á�
	//packaged_task��װ�����Ŀε��ö��󻹿���ֱ�ӵ��ã����ԣ�������Ƕ�������packaged_task����Ҳ��һ���ɵ��ö���
	
	//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
	//std::packaged_task<int(int)> mypt(mythread);  //�Ѻ���mythreadͨ��packaged_task��װ����
	//						//packaged_task<int(int)>  ��һ��int�Ǻ����������ͣ��ڶ����ǲ�������
	//std::thread t1(std::ref(mypt), 1);   //�߳�ֱ�ӿ�ʼִ�У��ڶ���������Ϊ�߳���ں����Ĳ�����
	//t1.join();     //�ȴ��߳�ִ����ϡ�
	//std::future<int> result = mypt.get_future();
	//				//std::future������������߳���ں����ķ��ؽ��������result����mythread���صĽ����
	//cout << result.get() << endl;
	//cout << "I LOVE CHINA!" << endl;


	//��һ��д��
		//std::packaged_task<int(int)> mypt([](int mypar){
		//cout << mypar << endl;
		//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		//std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
		//std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
		//cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		//return 5;
		//
		//});
		//std::thread t1(std::ref(mypt), 1);   //�߳�ֱ�ӿ�ʼִ�У��ڶ���������Ϊ�߳���ں����Ĳ�����
		//t1.join();     //�ȴ��߳�ִ����ϡ�
		//std::future<int> result = mypt.get_future();
		////std::future������������߳���ں����ķ��ؽ��������result����mythread���صĽ����
		//cout << result.get() << endl;

	
	//����һ��д������Ϊpackaged_task������һ���ɵ��ö���,û�д����µ��߳�
		//std::packaged_task<int(int)> mypt([](int mypar){
		//cout << mypar << endl;
		//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		//std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
		//std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
		//cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		//return 5;
		//});

		//mypt(105);   //ֱ�ӵ��ã��൱�ں�������,û�д����µ��߳�
		//std::future<int> result = mypt.get_future();
		//cout << result.get() << endl;

	//������һ��д������Ϊpackaged_task������һ���ɵ��ö���û�д����µ��߳�
		//cout << "main" << " threadId" << std::this_thread::get_id() << endl;
		//std::packaged_task<int(int)> mypt([](int mypar){
		//cout << mypar << endl;
		//cout << "mythread() start" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		//std::chrono::milliseconds dura(5000);//����һ��5��ʱ��
		//std::this_thread::sleep_for(dura); //��Ϣ��һ��ʱ��
		//cout << "mythread() end" << "threadId = " << std::this_thread::get_id() << endl;//��ӡ���߳�id
		//return 5;
		//});

		//vector <std::packaged_task<int(int)>> mytasks;

		//mytasks.push_back(std::move(mypt));;  //���������������ƶ����壬���ȥ֮��mypt��Ϊ�ա�
		//
		//std::packaged_task<int(int) > mypt2;    //��������mypt
		//auto iter = mytasks.begin();
		//mypt2 = std::move(*iter);   //�ƶ�����
		//mytasks.erase(iter);    //ɾ����һ��Ԫ�أ��������Ѿ�ʧЧ�ˣ����Ժ������벻������ʹ��iter��
		//mypt2(123);
		//std::future<int> result = mypt2.get_future();
		//cout << result.get() << endl;


	//����std::promise,��ģ��
	//�ܹ���ĳ���߳��и�����ֵ��Ȼ������������߳��У������ֵȡ�����ã�
	//�ܽ᣺ͨ��promise����һ��ֵ���ڽ���ĳ��ʱ������ͨ����һ��future�󶨵����promise�����õ�����󶨵�ֵ��
	std::promise<int> myprom;   //����һ��std::promise����myporm�������ֵ����Ϊint;
	std::thread t1(mythread, std::ref(myprom), 180);
	t1.join();
	std::future<int> ful = myprom.get_future();   //promise��future�󶨣����ڻ�ȡ�̷߳���ֵ��
	//auto result = ful.get();    //get()ֻ�ܵ���һ�Σ����ܵ��ö��
	//cout << "result = " << result << endl;

	std::thread t2(mythread2, std::ref(ful));
	t2.join();   //��mythread2�߳�ִ�����

	cout << "I LOVE CHINA" << endl;
	return 0;


	//�ģ�С�᣺������ô�ã�ʲôʱ���ã�
	//ѧϰ��Щ������Ŀ�ģ�������Ҫ�����Ƕ�����զ���Լ���ʵ�ʿ����С�
	//�෴������ܹ������ٵĶ����ܹ�д��һ���ȶ�����Ч�Ķ��̳߳����Ǿ͸�����
	//�Ķ�����д�Ĵ��룬�Ӷ�����ʵ���Լ�����Ļ��ۣ��������д����������
	//ѧϰ��Щ���������ɵĽ��ͣ�Ϊ�����ܹ���������������ʦд�Ĵ������·��
}