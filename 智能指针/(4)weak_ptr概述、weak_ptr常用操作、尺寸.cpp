#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
	//һ��weak_ptr: weak_ptr����shared_ptr���й�����
	//weak������,�����"ǿ"��
	//ǿָ�ľ���shared_ptr,��ָ�ľ���weak_ptr;
	//weak_ptr :Ҳ�Ǹ���ģ�壬Ҳ��һ������ָ�롣�������ָ��ָ��һ����shared_ptr����Ķ��󡣵���weak_ptr����ָ����ָ��Ķ���λ�������ڡ�
	//���仰��˵����weak_ptr�󶨵�shared_ptr�ϲ�����ı�shared_ptr�����ü���(��ȷ�е�˵,weak_ptr�Ĺ���������������ӻ��߼�����ָ���������ü�����
	//��shared_ptr��Ҫ�ͷ���ָ�������ʱ���ճ��ͷţ������Ƿ���weak_ptrָ��ö���weak�����˼"��".
	//��������������/�����ã�����������shared_ptr��ָ��Ķ��󣩣����Ʋ�����ָ�����������ڡ�

	//���������(weak_ptr)�����ã��������ɣ�����shared_ptr(ǿ����)�����������õġ���һ�ֶ�shared_ptr�����䡣
	//weak_ptr����һ�ֶ���������ָ�룬��������������ָ�����Դ������������������һ��shared_ptr�����֡�
	//weak_ptr�ܹ���������ָ��Ķ����Ƿ���ڡ�
	
	//weak_ptr�Ĵ���
	//����weak_ptr��ʱ��һ����һ��shared_ptr����ʼ��;
	auto pi = make_shared<int>(100);   //shared_ptr
	weak_ptr<int> piw(pi);   //piw������pi��pi���ü�����ǿ���ü�������ı䣩���䣬���������ü�����ı�(�����ü������0���1)
	//ǿ���ü������ܾ�������������ڣ������ü������Զ���������û��Ӱ�졣
	weak_ptr<int> piw2;
	piw2 = piw; //��weak_ptr��������һ��weak_ptr������pi��һ��ǿ���ã�piw��piw2������������

	//lock();���ܾ��Ǽ��weak_ptr��ָ��Ķ����Ƿ���ڣ�	
			//������ڣ���ô���lock�����ܹ�����һ��ָ��ö����shared_ptr����ָ���ǿ���ü����ͻ��һ��
			//�������ָ��Ķ��󲻴��ڣ�lock�᷵��һ���յ�shared_ptr;
	pi.reset();   //��Ϊpi��Ψһָ��ö����ǿ��������ָ�룬����reset()���ͷ�pi��ָ��Ķ���ͬʱ��pi�ÿա�
	auto pi2 = piw.lock();  //pi2��һ��shared_ptr
	if (pi2 != nullptr)   //Ҳ����д�� if(pi2)
	{
		//��ָ��Ķ������
		*pi2 = 12;
	}
	else {
		cout << "���ź�,lockʧ��" << endl;
	}
	//�ܽ��ϱ���δ��룺weak_ptr�ܹ��ж���ָ��Ķ����Ƿ���ڣ���������

	//����weak_ptr���ò���
		//(2.1)use_count():��ȡ�����ָ�빲����������shared_ptr������������˵��õ�ǰ���۲���Դ��ǿ���ü�����
	auto pi = make_shared<int>(100);
	auto pi2(pi);   //�Ǹ�һshared_ptr
	weak_ptr<int> piw(pi);
	int isc = piw.use_count();
	cout << isc << endl; // 2

		//��2.2��expired():�Ƿ���ڵ���˼����ָ���use_count()Ϊ�㣨��ʾ����������ָ��Ķ����ѽ��������ˣ���
						//�򷵻�true�����򷵻�false�����仰˵��������������ж����۲����Դ�Ƿ��Ѿ����ͷš�
	pi.reset();
	pi2.reset();
	if (piw.expired()) {
		cout << "�����Ѿ�����" << endl;
	}
	
		//(2.3)reset():����������ָ������Ϊ�գ���Ӱ��ָ������ǿ������������ָ������������������1��
	piw.reset();

		//(2.4)lock()
	auto p1 = make_shared<int>(42);
	weak_ptr<int> pw;
	pw = p1;   // ������shared_ptr��weak_ptr��ֵ��
	if (!pw.expired()) {
		auto p2 = pw.lock();   //����һ��shared_ptr,���Ҵ�ʱǿ���ü���Ϊ2;
		if (p2 != nullptr) {
			//��һЩ����
			int test;
			test = 1;
			//�뿪�����Χ��ǿ���ü�����ָ�Ϊ1
		}
	}
	//�ߵ���һ��ǿ���ü������Ϊһ

	//�����ߴ�����
	weak_ptr<int> pw; 
	//weak_ptr�ĳߴ��shared_ptr�ߴ�һ��������ָ���2����
	int* p;
	int ilen1 = sizeof(p);  //4���ֽڣ��Ǹ���ָ��
	int ilen2 = sizeof(pw); //8���ֽڣ�������ָ��

	auto pi = make_shared<int>(100);
	weak_ptr<int> piw(pi);
	//��һ����ָ��ָ��������ֻ��ָ��ָ��Ķ���
	//�ڶ�����ָ��ָ��һ���ܴ�����ݽṹ(���ƿ�),������ƿ�����
		//���ƿ��������:
			//(1):��ָ������ǿ���ü���
			//(2):��ָ��������ü���
			//(3):��������

	return 0;
}			