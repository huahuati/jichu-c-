#include<iostream>

using namespace std;


class A {
public:
	void func() {};//成员函数
	void func1() {};
	void func2() {};   //类的成员函数不占用类对象的内存空间

	//char ab;  //成员变量，char类型占一个字节内存
	int ab;   //int 类型占4个字节
};
int main() {
	
	A obja; 
	int ilen = sizeof(obja);   //sizeof(A) = 1，//为什么sizeof(空类) = 1 而不等于0？//因为obja有地址，所以有一个字节的地址。
	cout << ilen << endl;

	//两点：
	//(1)成员函数不占用类对象的内存空间
	//(2)一个类对象至少占用一个字节的内存空间

	//obja.ab = 'v';
	//(3)成员变量占用对象的内存空间
	obja.ab = 12;

	//结论:成员变量是包含在每个对象中的，是占用对象字节的。而成员函数虽然也写在类的定义中，但是成员函数不占对象字节数的
	//不占用内存空间
	
	//成员函数，每个类只诞生一个(跟着类走);而不管用这个类产生了多少个该类的对象
	return 0;
}