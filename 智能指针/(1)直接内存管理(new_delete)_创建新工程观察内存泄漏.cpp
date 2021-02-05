#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
void myfun() {
	int i; //临时对象
	i = 5;//函数结束，分配内存就会被释放
	static int j;  //局部静态对象；
}
class A {
public:
	A() {
		cout << "A" << endl;
	}
};
int main() {
	//一：直接内存管理(new/delete)
	myfun();
	//A a; // 编译器帮助我们创建a对象
	//堆   栈  概念
	//new分配方式我们称为动态分配(分配在堆上) ：直接内存管理（new/delete);
	//如何初始化：
	//int* point_i = new int;   //初始未定义
	string* mystr = new string;  //空字符串，说明调用了string的默认构造函数；
	int* pointi = new int(100); // 用圆括号个一个int的动态对象初值
	string* mystr2 = new string(5, 'a');  //生成一个字符串，字符串内容是5个"a"
	vector<int>* pointv = new vector<int>{ 1,2,3,4,5 };  //一个容器对象，里边有5个元素

	// 概念“值初始化”:用()来初始化
	string* mystr3 = new string();  //也是空字符串，和mystr没啥区别
	int* pointi2 = new int();   //值初始化的方式，发现pointi2的值被初始化为零;
	//A* pa = new A;
	A* pa2 = new A();  //是否是“值初始化”效果一样，都是调用A的构造函数。
	//new对象时候，能够进行“值初始化”就进行一下为好，防止它的值没有被初始化；
	//c++11中，auto可以和new配合使用

	string* mystr2 = new string(5, 'a');
	auto mystr3 = new auto(mystr2);  //系统自动推断mystr3 = string **
	//string** mystr3 = new string * (mystr2);
	delete mystr2;

	//const对象也可以动态分配；
	const int* pointci = new const int(200);

	//new 和 delete 说明；
	//new 和 delete 说明：
		//a） 成对使用，delete的作用是回收new分配的内存（释放内存）；不是new出来的内存，是不能用delete来释放；
		//b） delete一块内存，只能delete一次，不能delete多次。delete后这块内存就不能使用
		//c)  空指针可以删除多次，但删除多次没有什么意义
			//char* p = nullptr;
			//delete p;
			//delete p;
		//d) 不是new出来的内存，不能delete。否则执行会报告异常；
			//int i = 12;
			//int* p = &i;
			//delete p;
		//e)  因为P和P2都指向同一段内存,delete P2之后就不能delete P；
			//int* p = new int();
			//int* p2 = p;
			//delete p2;
			//delete p;


	//注意事项的一个总结：
		//（1）new出来的千万不要忘记delete；否则内存泄漏，时间一长可能导致系统资源紧张，运行奔溃
		//（2）delete后的内存不能再使用，否则异常
				//int* pci = new int(300);
				//*pci = 500;
				//delete pci;
				////*pci = 600
				//pci = nullptr; // 这是一个好习惯，表明该指针不能指向任何对象了；
		// (3) 同一块内存释放两次的问题，也会报异常

	//用new，delete直接进行内存管理，要很小心。
	//c++11开始出现了“智能指针”，new忘记了delete，智能指针能帮组你delete；

	//二:创建新工程，观察内存泄漏
	return 0;
}