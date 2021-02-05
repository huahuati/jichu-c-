#include<iostream>
#include<vector>
#include<string>

using namespace std;
shared_ptr<int> create0(int value)  
{
	return make_shared<int>(value);   //����һ��shared_ptr
}

void myfunc(int value) {
	shared_ptr<int> ptmp = create0(10);
	return;     //�뿪�������ptmp�ᱻ�Զ��ͷţ�����ָ����ڴ�Ҳ�ᱻ�Զ��ͷ�
}
shared_ptr<int> myfunc1(int value) {
	shared_ptr<int> ptmp = create0(10);
	return ptmp;  //ϵͳ�Ǹ���ptmp����ֲ�����������һ����ʱ��shared_ptr�������ط�
}

void proc(shared_ptr<int> ptr) {
	return;
}
class CT :public enable_shared_from_this<CT> 
{
public:
	shared_ptr<CT> getself() {
		//return shared_ptr<CT>(this);  //����ָ���ʼ���˶��shared_ptr�ĸо�
		return shared_from_this();   //�������enable_shared_from_this���еķ�����Ҫͨ���˷�����������ָ�롣
	}
};
class CB;   //������CB
class CA {
public:
	shared_ptr<CB> m_pbs;
	~CA() {
		int test;
		test = 1;
	}
};
class CB {
public:
	shared_ptr<CA> m_pas;
	//weak_ptr<CA> m_pas;   //�������������þͲ����������
	~CB() {
		int test;
		test = 1;
	}
};
int main() {
	//һ:std::shared_ptrʹ�ó���
	myfunc(12);    //�����鲻�ñ���������myfunc1���صĽ������ô��myfunc���ص�shared_ptr�ͻᱻ���١�
					//����ָ��Ķ���Ҳ�ᱻ����
	auto p11 = myfunc1(12);   //����һ����������myfunc1�ķ���ֵ��
							  //��ômyfunc���ص�shared_ptr�Ͳ��ᱻ���٣�����ָ��Ķ���Ҳ���ᱻ����

	//��:std::shared_ptrʹ���������
		//��2.1��������ָ��
		int* p = new int(100);  //��ָ��
		//proc(p);   //�﷨����int *p ����ת����shared_ptr<int>
		proc(shared_ptr<int>(p));  //�����Ǹ���ʱ��shared_ptr����һ����ָ����ʾ�Ĺ��죻
		*p = 45; //Ǳ�ڵĲ���Ԥ�ϵ����⣻��Ϊpָ����ڴ��Ѿ����ͷ�
//  --------------- �ֽ��� --------------
		shared_ptr<int> p2(p);
		proc(p2);
		*p2 = 45;  //��һ����ָͨ��󶨵���һ��shared_ptr��֮���ڴ��������ξͽ������shared_ptr�ˣ�
					//���ʱ��Ͳ�Ӧ��������ָ��������shared_ptr��ָ����ڴ��ˡ�

//  ---------------- �ֽ��� ------------
		shared_ptr<int> myp(new int(100));
		proc(myp);
		*myp = 45;

	//ע�⣺��������������Ҫ����ָ���ʼ�����shared_ptr
		int* p = new int(100);
		shared_ptr<int> p1(p);
		shared_ptr<int> p2(p);  //p1��p2�޹�����p1��p2ÿ��ǿ���ü�����Ϊ1�ˣ����ᵼ��p1��p2
								//��ָ����ڴ汻�ͷ����Σ����Իᱨ�쳣��
		shared_ptr<int> p1(new int());
		shared_ptr<int> p2(p1);   //����д������ok�ģ�p1��p2ָ��ͬһ���ڴ��ַ�������߶��ǻ�ͨ�ġ�

		//(2.2)����get()���ص�ָ��
		//get()���ܣ���������ָ����ָ���������Ӧ�ĵ���ָ��(��Щ�����ӿ���ֻ��ʹ����ָ��)
		//get���ص�ָ�벻��delete��������쳣
		shared_ptr<int> myp(new int(100));
		int* p = myp.get();
		delete p;   //����ɾ�����ᵼ���쳣

		//���ܽ���������ָ��󶨵�get()���ص�ָ����
		shared_ptr<int> myp(new int(100));
		int* p = myp.get();   //���ָ�벻��ǧ���������ͷţ�����myp��û�취���������ָ����
		//shared_ptr<int> myp2(p);
		{
			shared_ptr<int> myp2(p); //����myp��myp2���ü�����Ϊ1����һ�������������飻
			shared_ptr<int> myp2(p);//����д��û������
		}
		//�뿪�ϱ����myp2�ķ�Χ������mypָ����ڴ汻�ͷ��ˣ�
		*myp = 65;  //���ڴ��Ѿ����ͷţ�������ֵ�ᵼ�²���Ԥ�ϵĺ����
		//���ۣ���Զ��Ҫ��get�õ���ָ������ʼ������һ������ָ����߸�����һ������ָ�븳ֵ��

		//(2.3)��Ҫ�������ָ��(this)��Ϊshared_ptr���أ�����enable_shared_from_this
		shared_ptr<CT> pct1(new CT);
		//shared_ptr<CT> pct2 = pct1;  //��������ǿ����
		shared_ptr<CT> ptc2 = pct1->getself();   //�������(return shared_ptr<CT>(this) �������)
		shared_ptr<CT> ptc2 = pct1->getself();   //������(return shared_from_this() �������)
		//�õ�c++��׼����ߵ���ģ�壺enable_shared_from_this
		//�����洴��CT���������ָ���Լ�ͨ��CT���󷵻ص�this����ָ�붼�ǰ�ȫ�ġ�
		//���enable_shared_from_this����һ����ָ��weak_ptr,�����ָ���ܹ�����this��
		//�����ǵ���shared_from_this()�������ʱ����������ڲ�ʵ�����ǵ��������weak_ptr��lock()������
		//lock()��������shared_ptrָ�������һ��ͬʱ�������shared_ptr��������ǹ���ԭ��

		//(2.4)����ѭ�����ã��ܹ������ڴ�й©
		shared_ptr<CA> pca(new CA);
		shared_ptr<CB> pcb(new CB);
		pca->m_pbs = pcb;  //�ȼ���ָ��CB�����������ǿ����
		pcb->m_pas = pca;  //�ȼ���ָ��CA�����������ǿ����

		//����취��һ��������ǿ���ã�һ��������������

	
	//��������˵��
	//(3.1)shared_ptr�ĳߴ�����ָ���������weak_ptr�ߴ���ָ���2����
		char* p;
		int ilenp = sizeof(p);   //4�ֽ�
		shared_ptr<string> p1;
		int ilensp = sizeof(p1);  //8�ֽڣ�����������ָ���

		//a)��һ����ָ��ָ������������ָ����ָ��Ķ���
		//b)�ڶ�����ָ��ָ��һ���ܴ�����ݽṹ(���ƿ�)��������ƿ������ɶ?
			//b.1)��ָ�����ǿ���ü�����shared_ptr
			//b.2)��ָ����������ü�����weak_ptr
			//b.3)�������ݣ�����ɾ����ָ�룬�ڴ��������
		//������ƿ����ɵ�һ��ָ��ĳ�������shared_ptr������
		
		//���ƿ鴴����ʱ����
		//a)make_shared:���䲢��ʼ��һ�����󣬷���ָ��˶���shared_ptr,����make_shared�����ܹ�����һ�����ƿ飻
		shared_ptr<int> p2 = make_shared<int>(100);

		//b)����ָ�봴��һ��shared_ptr����ʱ
		int* pi = new int();
		shared_ptr<int> pl(pi);
	//(3.2)�ƶ�����
		shared_ptr<int> p1(new int(100));
		shared_ptr<int> p2(std::move(p1));   //�ƶ����壬�ƶ�����һ���µ�����ָ�����p2��
											//p1�Ͳ���ָ��ö���(��ɿ�),���ü���������1��
		shared_ptr<int>p3;
		p3 = std::move(p2);   //�ƶ���ֵ��p2ָ��գ�p3ָ��ö��������������ü�������Ϊ1��
		//�ƶ��϶��ȿ��¿飻����Ҫ�������ü������ƶ�����Ҫ��
		//�ƶ����캯�������ֵ���캯�����ƶ���ֵ��������������ֵ�������

	//�ģ�����˵����ʹ�ý���
		//a)������������ڴ�������⣻(û�н���)
		//shared_ptr<int> p(new int, mydeleter(), mymallocator<int>());

		//b)����ʹ�ã�����÷���Ҫ���׳��ԡ�

		//c)����ʹ��make_shared()�������Լ���һ�Լ���ɾ����
		shared_ptr<string> ps1(new string("i love *"));//���������ڴ�
		auto ps2 = make_shared<string>("I Love China!"); //����1���ڴ�
	return 0;
}