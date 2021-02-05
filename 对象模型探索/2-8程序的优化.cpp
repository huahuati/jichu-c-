#include<iostream>
#include<time.h>
using namespace std;

class CTemValue {
public:
	int val1;
	int val2;
public:
	CTemValue(int vl = 0, int v2 = 0) :val1(vl), val2(v2) //构造函数
	{
		cout << "调用了构造函数！" << endl;
		cout << "val1 = " << val1 << endl;
		cout << "val2 = " << val2 << endl;
	}
	CTemValue(const CTemValue& t) :val1(t.val1), val2(t.val2)//拷贝构造函数
	{
		cout << "调用了拷贝构造函数!" << endl;
	}
	virtual ~CTemValue() {
		cout << "'调用了析构函数" << endl;
	}
};

//函数(开发者视角)
CTemValue Double(CTemValue& ts)
{
//	/*
//	CTemValue tmpm;		 //消耗一个构造函数，一个析构函数。
//	tmpm.val1 = ts.val1 * 2;
//	tmpm.val2 = ts.val2 * 2;
//	return tmpm;   //生成一个临时对象，然后调用拷贝构造函数把tmpm的内容拷贝构造到这个临时对象中去，然后返回临时对象
//						//这个临时对象也消耗了一个拷贝构造函数，消耗了一个析构函数
//						*/
	return CTemValue(ts.val1 * 2, ts.val2 * 2);  //生成一个临时对象。
}

//函数(编译器视角)
//void Double(CTemValue& tmpobj, CTemValue& ts) //编译器会插入第一个参数
//{
//	tmpobj.CTemValue::CTemValue(ts.val1 * 2, ts.val2 * 2);
//	return;
//}

int main(){
	//第八节   程序的优化
	//从开发者层面
	//从编译器层面

	//(1)开发者层面的优化(开发者视角)
	//CTemValue ts1(10, 20);
	//Double(ts1);
	////CTemValue ts2 =  Double(ts1);

	//(2)编译器视角
	//CTemValue ts1;
	//ts1.CTemValue::CTemValue(10, 20);
	//CTemValue tmpobj;
	//Double(tmpobj, ts1);

	//(2)从编译器层面的优化
	//linux编译器，针对与返回临时对象在何种情况。NRV优化(Named Return Value)
					//RVO（Retuen Value Optimization）
	//g++ -fno-elide-constructors -o  
	CTemValue ts1(10, 20);  //测试时间记得把构造函数的中打印语句注释掉。
	clock_t start, end;
	start = clock();   //程序开始到本行执行时所用的毫秒数
	cout << "start = " << start << endl;
	for (int i=0; i < 1000000; i++)
	{
		Double(ts1);

	}
	end = clock();
	cout << "end = " << end << endl;
	cout << end - start << endl;


	//优化说明:
	//(1)编译器是否真的优化，不好说，要做各种测试才知道；
	//(2)如果代码很复杂，编译器可能放弃不优化。
	//(3)不要过度优化；
	//(4)优化可能使你犯错误。
	return 0;
}