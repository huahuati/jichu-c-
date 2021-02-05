#include<iostream>
#include<time.h>
using namespace std;

class CTemValue {
public:
	int val1;
	int val2;
public:
	CTemValue(int vl = 0, int v2 = 0) :val1(vl), val2(v2) //���캯��
	{
		cout << "�����˹��캯����" << endl;
		cout << "val1 = " << val1 << endl;
		cout << "val2 = " << val2 << endl;
	}
	CTemValue(const CTemValue& t) :val1(t.val1), val2(t.val2)//�������캯��
	{
		cout << "�����˿������캯��!" << endl;
	}
	virtual ~CTemValue() {
		cout << "'��������������" << endl;
	}
};

//����(�������ӽ�)
CTemValue Double(CTemValue& ts)
{
//	/*
//	CTemValue tmpm;		 //����һ�����캯����һ������������
//	tmpm.val1 = ts.val1 * 2;
//	tmpm.val2 = ts.val2 * 2;
//	return tmpm;   //����һ����ʱ����Ȼ����ÿ������캯����tmpm�����ݿ������쵽�����ʱ������ȥ��Ȼ�󷵻���ʱ����
//						//�����ʱ����Ҳ������һ���������캯����������һ����������
//						*/
	return CTemValue(ts.val1 * 2, ts.val2 * 2);  //����һ����ʱ����
}

//����(�������ӽ�)
//void Double(CTemValue& tmpobj, CTemValue& ts) //������������һ������
//{
//	tmpobj.CTemValue::CTemValue(ts.val1 * 2, ts.val2 * 2);
//	return;
//}

int main(){
	//�ڰ˽�   ������Ż�
	//�ӿ����߲���
	//�ӱ���������

	//(1)�����߲�����Ż�(�������ӽ�)
	//CTemValue ts1(10, 20);
	//Double(ts1);
	////CTemValue ts2 =  Double(ts1);

	//(2)�������ӽ�
	//CTemValue ts1;
	//ts1.CTemValue::CTemValue(10, 20);
	//CTemValue tmpobj;
	//Double(tmpobj, ts1);

	//(2)�ӱ�����������Ż�
	//linux������������뷵����ʱ�����ں��������NRV�Ż�(Named Return Value)
					//RVO��Retuen Value Optimization��
	//g++ -fno-elide-constructors -o  
	CTemValue ts1(10, 20);  //����ʱ��ǵðѹ��캯�����д�ӡ���ע�͵���
	clock_t start, end;
	start = clock();   //����ʼ������ִ��ʱ���õĺ�����
	cout << "start = " << start << endl;
	for (int i=0; i < 1000000; i++)
	{
		Double(ts1);

	}
	end = clock();
	cout << "end = " << end << endl;
	cout << end - start << endl;


	//�Ż�˵��:
	//(1)�������Ƿ�����Ż�������˵��Ҫ�����ֲ��Բ�֪����
	//(2)�������ܸ��ӣ����������ܷ������Ż���
	//(3)��Ҫ�����Ż���
	//(4)�Ż�����ʹ�㷸����
	return 0;
}