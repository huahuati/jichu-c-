#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
void myfun() {
	int i; //��ʱ����
	i = 5;//���������������ڴ�ͻᱻ�ͷ�
	static int j;  //�ֲ���̬����
}
class A {
public:
	A() {
		cout << "A" << endl;
	}
};
int main() {
	//һ��ֱ���ڴ����(new/delete)
	myfun();
	//A a; // �������������Ǵ���a����
	//��   ջ  ����
	//new���䷽ʽ���ǳ�Ϊ��̬����(�����ڶ���) ��ֱ���ڴ����new/delete);
	//��γ�ʼ����
	//int* point_i = new int;   //��ʼδ����
	string* mystr = new string;  //���ַ�����˵��������string��Ĭ�Ϲ��캯����
	int* pointi = new int(100); // ��Բ���Ÿ�һ��int�Ķ�̬�����ֵ
	string* mystr2 = new string(5, 'a');  //����һ���ַ������ַ���������5��"a"
	vector<int>* pointv = new vector<int>{ 1,2,3,4,5 };  //һ���������������5��Ԫ��

	// ���ֵ��ʼ����:��()����ʼ��
	string* mystr3 = new string();  //Ҳ�ǿ��ַ�������mystrûɶ����
	int* pointi2 = new int();   //ֵ��ʼ���ķ�ʽ������pointi2��ֵ����ʼ��Ϊ��;
	//A* pa = new A;
	A* pa2 = new A();  //�Ƿ��ǡ�ֵ��ʼ����Ч��һ�������ǵ���A�Ĺ��캯����
	//new����ʱ���ܹ����С�ֵ��ʼ�����ͽ���һ��Ϊ�ã���ֹ����ֵû�б���ʼ����
	//c++11�У�auto���Ժ�new���ʹ��

	string* mystr2 = new string(5, 'a');
	auto mystr3 = new auto(mystr2);  //ϵͳ�Զ��ƶ�mystr3 = string **
	//string** mystr3 = new string * (mystr2);
	delete mystr2;

	//const����Ҳ���Զ�̬���䣻
	const int* pointci = new const int(200);

	//new �� delete ˵����
	//new �� delete ˵����
		//a�� �ɶ�ʹ�ã�delete�������ǻ���new������ڴ棨�ͷ��ڴ棩������new�������ڴ棬�ǲ�����delete���ͷţ�
		//b�� deleteһ���ڴ棬ֻ��deleteһ�Σ�����delete��Ρ�delete������ڴ�Ͳ���ʹ��
		//c)  ��ָ�����ɾ����Σ���ɾ�����û��ʲô����
			//char* p = nullptr;
			//delete p;
			//delete p;
		//d) ����new�������ڴ棬����delete������ִ�лᱨ���쳣��
			//int i = 12;
			//int* p = &i;
			//delete p;
		//e)  ��ΪP��P2��ָ��ͬһ���ڴ�,delete P2֮��Ͳ���delete P��
			//int* p = new int();
			//int* p2 = p;
			//delete p2;
			//delete p;


	//ע�������һ���ܽ᣺
		//��1��new������ǧ��Ҫ����delete�������ڴ�й©��ʱ��һ�����ܵ���ϵͳ��Դ���ţ����б���
		//��2��delete����ڴ治����ʹ�ã������쳣
				//int* pci = new int(300);
				//*pci = 500;
				//delete pci;
				////*pci = 600
				//pci = nullptr; // ����һ����ϰ�ߣ�������ָ�벻��ָ���κζ����ˣ�
		// (3) ͬһ���ڴ��ͷ����ε����⣬Ҳ�ᱨ�쳣

	//��new��deleteֱ�ӽ����ڴ����Ҫ��С�ġ�
	//c++11��ʼ�����ˡ�����ָ�롱��new������delete������ָ���ܰ�����delete��

	//��:�����¹��̣��۲��ڴ�й©
	return 0;
}