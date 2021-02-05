#include<iostream>
#include<vector>
#include<string>

using namespace std;

shared_ptr<int> myfuction(shared_ptr<int> &ptmp)  //�������Ϊ���ã������ü����������� 
{
	return ptmp;
}
shared_ptr<int> myfuc(shared_ptr<int> ptmp)  //ptmp�����ü���������
{
	return ptmp;
}
class A {
public:
	A() {}
	~A(){}
};

//д������ģ������װshared_ptr����
template<typename T>
shared_ptr<T> make_shared_array(size_t size) {
	return shared_ptr<T>(new T[size], default_delete<T[]>());
}
void myDelete(int* p) {   //���ǵ�ɾ����!ɾ������ָ���õģ�������ָ�����ü���Ϊ0���ͻ��Զ����ø�ɾ������ɾ������
	//дһЩ��־
	delete p;   //��Ȼ�Լ��ṩ��ɾ������ȡ������ָ���ȱʡɾ���������������Լ���ɾ����ָ��Ķ���(���ü���Ϊ0ʱ)
}
int main() {
	//һshared_ptr���ü��������Ӻͼ���
	//����ʽ�����ü�����ÿһ��shared_ptr�Ŀ�����ָ����ͬ���ڴ棨���󣩣�
	//ֻ�����һ��ָ��ö����shared_ptrָ�벻��Ҫָ��ö����ʱ��,���shared_ptr�Ż�������ָ��Ķ���
	//(1.1)���ü���������
	//ÿ��shared_ptr�����¼�ж��ٸ�������shared_ptrָ����ͬ�Ķ���	
	auto p6 = make_shared<int>(100);  //Ŀǰp6��ָ��Ķ���ֻ��p6һ��������;
	auto p7(p6);  //����ָ�붨��ʱ�ĳ�ʼ����p7��p6ָ������ͬ�Ķ��󣬴˶���Ŀǰ�����������ߣ�

	//����������£�����ָ���������shared_ptr���ü�����������һ��
	//a)���ϱ�������������p6����ʼ��p7�������ָ�룻
	//b)������ָ�뵱��ʵ���������ﴫ��(�������õĻ����ü�����������)��
	//myfuction(p7);
	//a)��Ϊ�����ķ���ֵ,��������Ҳ������
	auto p8 = myfuction(p7); //���ü�������3��������Ϊ��p8���������ʱ������ָ�롣
	//myfuction(p7); //û�б������������ʱ������ָ�룬����ʱ����ָ���������ڵ��ˣ����ü�����3�ָ���2��
	
	//(1.2)���ü����ļ���
	//a)��shared_ptr������ֵ���ø�shared_ptrָ��һ���¶���
	p8 = make_shared<int>(200);   //p8ָ���¶��󣬼���Ϊ1��p6��p7�����ָ�Ϊ2
	p7 = make_shared<int>(300);   //p7ָ���¶��󣬼���Ϊ1��p6ָ��Ķ�������ָ�Ϊ1��
	p6 = make_shared<int>(400);   //p6ָ���¶��󣬼���Ϊ1��p6ָ���ԭ�ڴ汻�ͷţ�
	//b)�ֲ���shared_ptr�뿪��������
	auto p6 = make_shared<int>(100);  //Ŀǰp6��ָ��Ķ���ֻ��p6һ��������
	auto p7(p6);  //p7��p6ָ����ͬ�Ķ������ü���Ϊ2��
	myfuc(p7);   //���뺯����myfunc����3�����ü�������myfunc���˳�ʱ���ü����ָ�Ϊ2��
	//c)��һ��shared_ptr���ü�����1���0���������Զ��ͷ��Լ�������(ָ��)�Ķ���
	auto p9 = make_shared<int>(100);   //ֻ��p9ָ���Ǹ��ö���
	auto p10 = make_shared<int>(100);
	p9 = p10;   //��p9��ֵ����p9ָ��p10��ָ��Ķ���
				//p10�������ü������2����ԭ��p9��ָ��Ķ������ü������1�����0���Ӷ����ͷš�

	//����shared_ptrָ�볣�ò���
	//��2.1��use_count�����ض��ٸ�����ָ��ָ��ĳ��������Ҫ���ڵ��ԣ�
		shared_ptr<int> myp(new int(100));
		int icout = myp.use_count();   // 1
		shared_ptr<int> myp2(myp);
		icout = myp.use_count();  //2
		shared_ptr<int> myp3(myp);
		icout = myp.use_count();  // 3
	
	//(2.2)unique():�Ƿ��ֻ��ָ���ռĳ��ָ��Ķ��󣨲���Ϊ�գ���
					//Ҳ������ֻ��һ������ָ��ָ��ĳ��������unique()����true�����򷵻�false
		shared_ptr<int> myp(new int(100));
		if (myp.unique())  //����
		{
			cout << "unique OK" << endl;
		}
		shared_ptr<int> myp2(myp);
		if (myp.unique())  //������
		{
			cout << "unique NO NO NO" << endl;
		}
	//(2.3)reset():�ָ�(��λ/����)����˼
		//a)reset()��������ʱ
		    //��pi��Ψһָ��ö����ָ�룬��ô�ͷ�pi��ָ��Ķ��󣬲���pi�ÿ�
		shared_ptr<int> pi(new int(100));
		pi.reset();
		if (pi == nullptr) {
			cout << "pi���ÿ�" << endl;
		}

		//��pi����Ψһָ��ö����ָ�룬��ô���ͷ�pi��ָ��Ķ��󣬵���ָ��ö�������ü��������1�����ǽ�pi�ÿ�
		shared_ptr<int> pi(new int(100));
		auto pi2(pi);
		pi.reset();

		//b)reset()������(һ����һ��new������ָ��)ʱ
			//��pi��Ψһָ��ö����ָ�룬���ͷ�piָ��Ķ�����piָ���¶���
			//��pi����Ψһָ��ö����ָ�룬���ͷ�pi��ָ��Ķ��󣬵�ָ��ö�������ü��������1��ͬʱ��piָ���¶���
			shared_ptr<int> pi(new int(100));
			pi.reset(new int(1)); //�ͷ�ԭ�ڴ棬ָ�����ڴ�
			auto pi2(pi); //pi2���ü�������2
			pi.reset(new int(1));	
		//c)��ָ��һ����ͨ��reset�����³�ʼ��
			shared_ptr<int> p;
			p.reset(new int(1));//�ͷ�p��ָ��Ķ�����pָ���¶���ӦΪԭ����pΪ�գ�
								//���Ե���ɶ��û���ͷ�ֱ��ָ���¶���
		
	//(2.4)*������
			shared_ptr<int> pother(new int(123456));
			cout << *pother << endl;
	//(2.5) get()  :���ǵ���Щ�����Ĳ�����Ҫ����һ��������ָ�����������ָ�롣
	//p.get():����p�б����ָ�루��ָ�룩��С��ʹ�ã��������ָ���ͷ�����ָ��Ķ�����ô������ص���ָ��Ҳ�ͱ����Ч�ˡ�
			shared_ptr<int>myp(new int(100));
			int* p = myp.get();
			*p = 45;
			//delete p;   ǧ��Ҫ��ô�ɣ���Ȼϵͳ�ᱨ���쳣����������Ԥ�ϵĽ��
	//(2.6)swap() : ������������ָ����ָ��Ķ���
			shared_ptr<string> PS1(new string("I Love China1"));
			shared_ptr<string> PS2(new string("I Love China2"));
			std::swap(PS1, PS2);   //�����������ͬ
			PS1.swap(PS2);

	//(2.7)= nullptr
			//a)����ָ��Ķ������ü�����һ�������ü�����Ϊ�㡢���ͷ�����ָ����ָ��Ķ���
			//b)������ָ���ÿ�
			shared_ptr<string> ps1(new string("I Love China!"));
			ps1 = nullptr;
	//(2.8)����ָ��������Ϊ�ж�����
			shared_ptr<string> ps1(new string("I LOVE CHINA!"));
			if (ps1) {
				cout << "ps1ָ��һ������" << endl;
			}
			else {
				cout << "ps1Ϊ��" << endl;
			}
	//(2.9)ָ��ɾ�����Լ���������
	//a)ָ��ɾ����;
	//һ��ʱ�ڰ�����ɾ����ָ��Ķ���delete����delete�������ΪĬ�ϵ���Դ������ʽ��
	//���ǿ���ָ���Լ���ɾ����ȡ��ϵͳ�ṩ��Ĭ��ɾ������������ָ����Ҫɾ����ָ��Ķ����ǣ�������������Լ���ɾ������ɾ����
	//shared_ptrָ��ɾ���������Ƚϼ򵥡�һ��ֻ��Ҫ�ڲ�������Ӿ����ɾ����ɾ��������
			shared_ptr<int> p(new int(123455),myDelete);
			shared_ptr<int> p2(p);   // �������ü���
			p2.reset();  //ʣ1�����ü�����p2Ϊnullptr
			p.reset();    //��Ϊ��ʱֻ��1�����ü���������Ҫ�ͷ�ָ��Ķ��󣬵������ǵ�ɾ����myDelete��ͬʱp�ÿգ�

			//��һ��д��
			//ɾ����������һ��lambda��ʾʽ��
			shared_ptr<int> ps(new int(123456), [](int* p) { delete p; });

			//��Щ�����Ĭ��ɾ����������(��shared_ptr����̬����)����Ҫ�����ṩ�Լ�ָ����ɾ������
			shared_ptr<int> p(new int[10], [](int* p) {delete[] p; });

			shared_ptr<A> pA(new A[10]);    //�쳣��Ϊϵͳ�ͷ�pA��delete pA��ָ�����ָ�룬������delete [] pA,
											//���������������Ҫд�Լ���ɾ����
			shared_ptr<A> pA(new A[10], [](A* p) {delete[] p; });

			//������default_delete����ɾ����,default_delete�Ǳ�׼�����ģ���ࡣ
			shared_ptr<A> pA(new A[10], std::default_delete<A[]>());

			//�������ֵ�ʱ�������ڼ������м�[]
			shared_ptr<A[]> pA(new A[10]);   //��<>�мӸ�[]������
			shared_ptr<int[]> p(new int[10]);   
			p[0] = 12;
			p[1] = 15;   //��ֱ�ӵ�������ʹ��
			shared_ptr<int> pintArr = make_shared_array<int>(5);
			shared_ptr<A> pintAArr = make_shared_array<A>(5);

	//b)ָ��ɾ��������˵����
			//����������shared_ptrָ���˲�ͬ��ɾ������ֻҪ������ָ��Ķ���������ͬ����ô������shared_ptrҲ����ͬһ������
			auto lambda1 = [](int* p) {
				//��־
				delete p;
			};
			auto lambda2 = [](int* p) {
				//��־
				delete p;
			};
			shared_ptr<int> p1(new int(100), lambda1);
			shared_ptr<int> p2(new int(200), lambda2);
			p2 = p1;  //p2���ȵ���lambda2���Լ���ָ��Ķ����ͷţ�Ȼ��ָ��p1��ָ�Ķ���p1��ָ��Ķ������ü���Ϊ2��
					  //����mianִ����Ϻ󣬻������lambda1���ͷ�p1��p2��ָͬ��Ķ���

			//������ͬ���ʹ�����Էŵ�Ԫ������Ϊ�ö������͵�����������
			vector<shared_ptr<int>> pvec{ p1,p2 };

			//make_shared:���ᳫ�����ɣ�shared_ptr�ķ���������make_shared���ַ�����������û�а취ָ���Լ���ɾ��������
}			