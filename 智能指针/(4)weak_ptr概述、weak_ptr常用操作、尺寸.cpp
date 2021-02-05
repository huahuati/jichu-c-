#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main() {
	//一：weak_ptr: weak_ptr辅助shared_ptr进行工作；
	//weak“弱”,反义词"强"。
	//强指的就是shared_ptr,弱指的就是weak_ptr;
	//weak_ptr :也是个类模板，也是一个智能指针。这个智能指针指向一个由shared_ptr管理的对象。但是weak_ptr这种指针所指向的对象定位声明周期。
	//换句话来说，将weak_ptr绑定到shared_ptr上并不会改变shared_ptr的引用计数(更确切的说,weak_ptr的构造和析构不会增加或者减少所指向对象的引用计数。
	//当shared_ptr需要释放所指定对象的时候照常释放，不管是否有weak_ptr指向该对象。weak这个意思"弱".
	//能力弱（弱共享/弱引用：共享其他的shared_ptr所指向的对象），控制不了所指向对象的生存期。

	//这个弱引用(weak_ptr)的作用：可以理解成，监视shared_ptr(强引用)的声明周期用的。是一种对shared_ptr的扩充。
	//weak_ptr不是一种独立的智能指针，不能用来操作所指向的资源，所以它看起来像是一个shared_ptr的助手。
	//weak_ptr能够监视它所指向的对象是否存在。
	
	//weak_ptr的创建
	//创建weak_ptr的时候一般用一个shared_ptr来初始化;
	auto pi = make_shared<int>(100);   //shared_ptr
	weak_ptr<int> piw(pi);   //piw弱共享pi，pi引用计数（强引用计数不会改变）不变，但是弱引用计数会改变(弱引用计数会从0变成1)
	//强引用计数才能决定对象的生存期；弱引用计数并对对象生存期没有影响。
	weak_ptr<int> piw2;
	piw2 = piw; //把weak_ptr赋给另外一个weak_ptr，现在pi是一个强引用，piw和piw2是两个弱引用

	//lock();功能就是检查weak_ptr所指向的对象是否存在，	
			//如果存在，那么这个lock它就能够返回一个指向该对象的shared_ptr（所指向的强引用计数就会加一）
			//如果它所指向的对象不存在，lock会返回一个空的shared_ptr;
	pi.reset();   //因为pi是唯一指向该对象的强引用智能指针，所以reset()会释放pi所指向的对象，同时将pi置空。
	auto pi2 = piw.lock();  //pi2是一个shared_ptr
	if (pi2 != nullptr)   //也可以写成 if(pi2)
	{
		//所指向的对象存在
		*pi2 = 12;
	}
	else {
		cout << "很遗憾,lock失败" << endl;
	}
	//总结上边这段代码：weak_ptr能够判断所指向的对象是否存在，这种能力

	//二：weak_ptr常用操作
		//(2.1)use_count():获取与该弱指针共享对象的其他shared_ptr的数量，或者说获得当前所观测资源的强引用计数。
	auto pi = make_shared<int>(100);
	auto pi2(pi);   //是个一shared_ptr
	weak_ptr<int> piw(pi);
	int isc = piw.use_count();
	cout << isc << endl; // 2

		//（2.2）expired():是否过期的意思。弱指针的use_count()为零（表示该弱智真所指向的对象已近不存在了），
						//则返回true，否则返回false。换句话说，这个函数用来判断所观测的资源是否已经被释放。
	pi.reset();
	pi2.reset();
	if (piw.expired()) {
		cout << "对象已经过期" << endl;
	}
	
		//(2.3)reset():将该弱引用指针设置为空，不影响指向对象的强引用数量，但指向该弱引用数量会减少1；
	piw.reset();

		//(2.4)lock()
	auto p1 = make_shared<int>(42);
	weak_ptr<int> pw;
	pw = p1;   // 可以用shared_ptr给weak_ptr赋值；
	if (!pw.expired()) {
		auto p2 = pw.lock();   //返回一个shared_ptr,并且此时强引用计数为2;
		if (p2 != nullptr) {
			//做一些操作
			int test;
			test = 1;
			//离开这个范围，强引用计数会恢复为1
		}
	}
	//走到这一，强引用计数会变为一

	//三：尺寸问题
	weak_ptr<int> pw; 
	//weak_ptr的尺寸和shared_ptr尺寸一样大，是裸指针的2倍；
	int* p;
	int ilen1 = sizeof(p);  //4个字节，是个裸指针
	int ilen2 = sizeof(pw); //8个字节，两个裸指针

	auto pi = make_shared<int>(100);
	weak_ptr<int> piw(pi);
	//第一个裸指针指向的是这个只能指针指向的对象
	//第二个裸指针指向一个很大的数据结构(控制块),这个控制块里有
		//控制块里的内容:
			//(1):所指向对象的强引用计数
			//(2):所指向的弱引用计数
			//(3):其他数据

	return 0;
}			