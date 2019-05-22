
#include<vector>
struct student{
	int num;
}
一：迭代器简介
	
	迭代器是一种遍历容器内元素的   数据类型，这种数据类型感觉有点像指针，我们理解的时候就理解为迭代器用来指向容器中的某个元素。
	string vector,[],  在++中很少用[],更常用的访问方式就是用迭代器(更通用)。
	通过迭代器，我么就可以读容器中的元素值，读string中的每个字符，还可以修改某个迭代器所指向的元素值。
	迭代器也有 ++,--的操作。
	尽量用迭代器来访问容器中的元素。

二：容器的迭代器类型

	vector<int> iv = {100,200,300};
	vector<int>::iterator  iter;    定义迭代器，也必须是 vector<int>

	在理解的时候，就把整个的vector<int>::iterator 理解成一个类型，这种类型就专门应用于迭代器。
	当我们用这个类型定义一个变量的时候，这个变量就是一个迭代器，这里iter就是个迭代器

三：迭代器begin()/end()操作，反向迭代器rbegin()/rend()操作，反向迭代器rbegin

	begin()/end() 用来返回迭代类型。rbegin()/rend()用来返回迭代类型。rbegin

	(1)begin()：返回一个迭代器类型(理解成返回一个迭代器)。
	
		iter = iv.begin();		如果容器中有元素，则begin返回的迭代器，指向的是容器中的第一个元素。
								相当于 iter 指向了iv[0]

	(2)end()：返回一个迭代器类型(理解成返回一个迭代器)。

		iter = iv.end()			end返回的迭代器指向的并不是末端元素。而是末端元素的后边。
								我们就理解成end()指向的是一个不存在的元素。

	(3)如果一个容器为空，那么begin()和end()返回的迭代器就相同。

		vector<int >= iv2;
		vector<int>::iterator iterbegin = iv2.begin();
		vector<int>::iterator iterend = iv2.end();
		if(iterbegin == iterend){
			cout << "容器iv2为空" << endl;
		}

	(4)传统的迭代器用法

		vector<int> iv = {100,200,300};
		for(vector<int>::iterator iter = iv.begin(); iter !=iv.end();iter++){
			cout << *iter << endl; 			结果为100,200,300
		}

	(1.1)反向迭代器：向从后往前遍历一个容器，那么方向迭代器就比较方便。
		 反向迭代器(逆向迭代器)，用的rbegin(),rend().
		 rbegin():返回一个反向迭代器，指向反向迭代器的第一个元素。
		 rend():返回一个反向迭代器，指向反向迭代器的最后元素的下一个位置。

		vector<int> iv = {100,200,300};
		for(vector<int>::reverse_iterator iter = iv.rbegin(); iter !=iv.rend();iter++){
			cout << *iter << endl; 			结果为 300,200,100
		}

四：迭代器运算符

	(1) *iter :返回迭代器iter所指向元素的引用。必须要保证整个迭代器指向的是有效的容器元素，不能指向end()。
		vector<int>::iterator iter = vi.end()
		cout << *iter << endl;     不能这样做

	(2) ++iter,iter++： 让迭代器指向容器下一个元素；已经指向end()的时候就不能 ++ 了。
		vector<int>::iterator iter = vi.end()
		iter++；			不能这样做

	(3) --iter 和 iter--:让迭代器指向容器中的上一个元素。
		vector<int>::iterator iter = vi.begin()
		iter--;			不能这样做

	(4) iter1 == iter2 ,iter1 != iter2。 判断两个迭代器是否相等

	(5)	如何引用结构中的成员
		vector <student> sv;
		student mystu;
		mystu = 100;
		sv.push_back(mystu);    把对象mystu赋值到了sv容器中

		vector<student>::iterator iter;
		iter = sv.begin();		指向第一个元素
		cout <<(*iter).num <<endl;
		cout << iter->num <<endl;


五：const_iterator迭代器：const ：常量(值不能改变)

		const_iterator迭代器，表示值不能改变。这里的值不能改变，表示这个迭代器指向的元素值不能改变。
		而不是表示这个迭代器本身不能改变。也就是说，迭代器本身是可以不断指向下一个元素。(只能读，不能改变值)

		vector<int> iv = {100,200,300};
		vector<int>::const_iterator iter;
		for(iter =iv.begin();iter != iv.end();++iter){
			*iter = 4;   报错，不能修改。
			cout << *iter << endl;   可以正常读
		}

	(1)	cbegin()和cend()操作
		c++11引入的两个新函数 cbegin(),cend(),跟begin，end类似。cbegin,cend，返回的都是常量迭代器。
		for(auto iter=iv.cbegin(); iter !=iv.cend();++iter){

			*iter = 4;   报错，不能给常量赋值，这说明cbegin返回的是常量迭代器。
			cout << *iter << endl;
		}

六:迭代器实效
	
	vector<int> vacvalue{1,2,3,4,5};
	for(auto vecitem :vacvalue){
		vacvalue.push_back(8888);
		cout << vecitem << endl;
	}

	相当于

	for(auto beg = vacvalue.begin(),end = vacvalue.end();beg !=end; ++beg){
		vecvalue.push_back(888);
		cout << *beg << endl;
	}

	在操作迭代器的过程中(使用了迭代器这种循环体)，千万不要改变vector容器的容量。也就是不要增加或者删除vector容器的元素。
	往容器中增加或者从容器中删除元素，这些操作可能会使指向容器元素的指针，引用，迭代器实效。
	实效就表示不能在代表任何容器中的元素。一旦使用实效的东西，就等于犯了严重的程序错误，很多情况下，程序会直接奔溃。

	(1) 灾难程序演示1

			vector<int > vecvalue {1,2,3,4,5};
			auto beg = vecvalue.begin();
			auto end = vecvalue.end();
			while(beg != end){
				cout << *beg << endl;

				vecvalue.insert(beg,80);    插入新值，第一个参数为插入位置，第二个参数为插入的元素。此操作会使迭代器实效。比如begin,end实效
											具体哪个迭代器实效，取决于这个容器vector内部的实现原理。
											现在不知道那个迭代器失效了，最明智的做法，就是一插入数据，就break出循环体。
				break;     break出循环体
				++beg   
			}

			重新赋值

			auto beg = vecvalue.begin();
			auto end = vecvalue.end();
			while(beg != end){
				cout << *beg << endl;
				++beg   
			}

		另一种方式

			auto beg = vecvalue.begin();
			int icount = 0;
			while (beg != vecvalue.end())   每次更新end 防止end 实效
			{

				beg = vecvalue.insert(beg,icount + 80);    insert的返回结果就要接着
				icount ++;
				if(icount >10)
					break;
				++beg;
			}
			beg = vecvalue.begin();
			auto end = vecvalue.end();
			while(beg != end){
				cout << *beg << endl;
				++beg   
			}

	(2) 灾难程序演示2

			vector<int> iv = {100,200,300};

			for(auto iter = iv.begin();iter != iv.end();++iter){
				iv.erase(iter)   erase 函数，移除iter位置上的元素，返回下一个元素位置。
			}

			转换为

			vector<int>::iterator iter =  iv.begin();

			while (iter !=iv.end()){
				iter = iv.rease(iter);
			}

			更高级的写法

			while(!iv.empty()){
				auto iter = iv.begin();   因为不为空，所以返回begine()是没问题的。
				iv.erase(iter);		删除该位置上的元素。
			}

七：用迭代器遍历string类型数据
	
	string str("i love china！")；
	for(auto iter = str.begine();iter ! str.end(); ++iter){
		*iter = toupper(*iter);
	}
	cout << str <<endl;

八:vector容器常用操作与内存释放
	
	实践程序：

	ServerName = 1区      表示服务器的名称
	ServerID = 100000     表示服务器ID

	struct conf{
		char itemname[40];
		char itemcontent[40];
	}

	char *getinfo(vector<conf *> &conlist,char *pitem){
		for(auto pos = conlist.begin(); pos!=conlist.end();++pos){
			if(_stricmp((*pos)->itemname,pitem) == 0){
				return (*pos)->itemcontent;
			}
		}
		return nullptr;
	}

	conf *pconf1 = new conf;
	strcpy_s(pconf1->itemname,sizeof(pconf1->itemname),"ServerName");
	strcpy_s(pconf1->itemcontent,sizeof(pconf1->itemcontent),"1区");

	conf *pconf1 = new conf;
	strcpy_s(pconf2->itemname,sizeof(pconf2->itemname),"ServerID");
	strcpy_s(pconf2->itemcontent,sizeof(pconf2->itemcontent),"100000");

	vector<conf *> conlist;
	conlist.push_back(pconf1);
	conlist.push_back(pconf2);

	char *p_tmp = getinfo(conflist,"ServerName");
	if(p_tmp != nullptr){
		cout <<p_tmp >> endl;
	}

	我们要释放内存，自己new的就要自己释放，否则会造成内存泄漏。

	std::vector<conf *>::iterator pos;
	for(pos = conflist.begine();pos != conflist.end();++pos){
		delete (*pos);   *pos才是那个指针
	}