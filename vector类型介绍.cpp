#include<vector>
struct student
{
	int num;
};
一：vector类型简介：标准库：集合或者动态数组。我们可以吧多个对象放在里面
	vector它能它其他对象装进来，额被称为容器。

	vector<int> vjihe;		表示vjihe 里边保存的是int型数据(int 型对象);
	<int>: 模板vector本身就是个类模板,<int>实际上就是类模板的实例化的过程。

	vector 当成类型 (残缺的类类型)
	vector<int> ：在vector之后加一对<>,<>内部放上类型信息。(完整的类类型)

	vector <student> studlist;
	vector<vector<string>> strchuan;       可以，该集合里边的每一个元素有都是一个vector<string>对象：集合套集合
	vector<int *>vjihe2
	vecotr<int &> vjihe3;  				   不能往里面装引用，引用是个别名，不是对象


二：定义和初始化vector对象
		(1)空vector

			vector<string> mystr;   创建了一个string类型空的vector对象（容器）,目前这个mystr里不包含任何元素。

		(2)元素拷贝的初始化方式

			vector<string> mystr2(mystr)    		把mystr元素拷贝给了mystr2
			vector<string> mystr3 = mystr   		把mystr元素拷贝给了mystr3

		(3)c++11 标准中，用列表初始化方法给值，用{}括起来;
			
			vector<string> mystr4 = {"aaa","bbb","ccc"};

		(4)创建指定数量的元素。有元素数量概念的东西，一般会用圆括号;
			
			vector<int > ijihe(15,-200) 		创建15和int类型的元素，每个元素的值是-200
			vector<string> sjige(5,"hello")		创建5个string类型的元素，每个元素的值是hello

			vector<int> ijihe(20)               20个元素，[0]....[19],每个元素都为0

		(5)多种初始化方式，()一般表示元素数量这么个概念。{}一般表示元素内容这么个概念。但是不绝对。


			vector<int> i1(10);      				表示10个元素，每个元素值是缺省的0
			vector<int> i2{10};		 				表示的是一个元素，该元素的值为10
			vector<string> snor {"hello"};  		表示一个元素，内容是hello。
			vector<string> s22 {10};				10个元素，每个元素"";
			vector<string> s22 {10,"hello"};		10个元素，每个元素的内容都是,"hello";
			vector<int> i3(10,1);				    10和元素，每个元素的值为1；
			vector<int> i4{10,1};					有2个元素，第一个值为10，第二个值为1，等同于初始化列表。

			想要正常的通过{}进行初始化，那么{}里边的值得类型，必须要跟vector后边这个<>里边元素类型相同。

三：vector对象上的操作：最常用的是不知道vector里面多少个元素。需要动态增加/减少。
	所以，一般来讲，先创建空vector
	vector很多操作和string很类似。
	(1) 判断是否为空empty(),返回的是布尔值。

		vector<int >ivec;
		if(ivec.empty()){
			cout << "ivec为空" << endl;
		}

	(2)push_back:常用方法，用于向vector中的末尾添加一个元素;
		ivec.push_back(1);
		ivec.push_back(2);
		
		for(int i =3;i<=100;i++){
			ivec.push_back(i);
		}

	(3)size:返回元素个数;

		cout << ivec.size() << endl;

	(4)clear:移除所有元素，将容器清空

		ivec.clear();
		cout << ivec.size() <<endl;

	(5)v[n]：返回v中第n个元素(n是个整型值)代表位置，位置是从0开始，必须小于.size()。

		cout << ivec[1] << endl;

	(6) = 赋值

		vector<int> ivec2;
		ivec2.push_back(2);
		ivec2 = ivec    				ivec2得到了100 个元素，ivec2原来的元素就消失(被冲掉了)
		ivec2 = {12,14,15,16} 			用{}中的值取代了ivec2中的原有值
		cout <<ivec2.size() << endl;

	(7)== ，！= ：相等，不相等：元素数量相同，对应位置的元素值也得一样。否则就是不相等。

		vector<int> ivec2;
		ivec2 = ivec;
		if(ivec2 == ivec){
			cout << "ivec2 == ivec" << endl;    成立
		}

		ivec2.push_back(12345);
		if(ivec2 != ivec){
			cout << "ivec2 != ivec" << endl;    成立
		}

		ivec2.clear()
		ivec.clear()
		if(ivec2 == ivec){
			cout << "ivec2 == ivec" << endl;    成立
		}

	(8)范围for的应用

		vector<int> vecvalue {1,2,3,4,5};
		for(auto &vecitem : vecvalue){
			vecitem *= 2;
		}

		for(auto vecitem : vecvalue){
			cout << vecitem << endl;
		}

四：范围for进一步讲解


		for(auto vecitem : vecvalue){
			vecvalue.push_back(223);    导致输出彻底乱套
			cout << vecitem << endl;
		}

		结论：在for语句中(遍历一个容器等等类似操作中),千万不要改动vector容器的容量，增加/删除 都不可以
