#include<string>

一：前言 int ,float char ，c++标准库：string，vector
	string：可变长字符串的处理。vector一种集合或者容器的概念

二：string类型简介：c++标准库中的类型，代表一个可变长的字符串。
	string这个类型，看成一个类类型(类似于struct)
	char str[100] = "I LOVE CHINA";   c言语中的用法

三：定义和初始化string对象
	
	string s1;   默认初始化，s1 = ""; 空串，表示里边没有字符
	string s1 = "I LOVE CHINA"；    把 I LOVE CHINA !把这个字符串内容拷贝到了s2代表的一段内存中。拷贝时不包括末尾的\0。
	string s3("I LOVE CHINA");   跟s2的写法效果一样·
	string s4 = s2;  把s2中的内容拷贝到了s4所代表的一段内存中

	int num = 6;
	string s5(num,'a');  aaaaa,把s5初始化为连续num个字符'a'组成的字符串。这种方式不太推荐，因为会在系统内部创建临时对象。

四：string对象上的操作
	
	(1)判断是否为空 empty(),返回布尔值。
		
		string s1;
		if(s1.empty()){
			cout << "s1为空" << endl;
		}
	
	(2)size() 或 length():返回字节/字符数量 代表该字符的长度。unsigned int

		string s1;
		cout << s1.size() << endl;
		cout << s1.length() << endl;
		
		string s2 = "I LOVE CHINA";
		cout << s2.size() << endl;
		cout << s2.length()<< endl;

	(3)s[n]: 返回s中的地n个字符(n是个整型值)，n代表的是一个位置，位置从0开始，到，size() - 1;

		string s3 = " I LOVE CHINA";
		if(s3.size() > 4){
			cout << s3[4] << endl;
			s3[4] = 'w';
		}
		cout << s3 << endl;

	(4)s1 + s2 ; 字符串的链接，返回链接的结果，其实就是得到一个新的string对象。

		string s4 = "abcd";
		string s5 = "hijk";
		string s6 = s4 + s5;
		cout << s6 <<endl;

	(5)s1 = s2; 字符串对象赋值，用s2里边的内容取代原来s1里的内容。

		string s7 = "abcd";
		string s8 = "de";
		s7 =s8;
		cout << s7 << endl;

	(6)s1 == s2 ; 判断两个字符串是否相等。大小写敏感：也就是大小写字符跟小写字符是两个不同的字符。
	   向等：长度相同。字符全相同。
	   string s9 = "abc";
	   string s10 = "abc";
	   if(s9 == s10){
	   	cout << "s9 == s10" << endl;
	   }

	(7)s1 != s2;  判断两个字符串是否不相等。

		string s9 = "ABC";
	    string s10 = "abc";
	    if(s9 != s10){
	   	 cout << "s9 != s10" << endl;
	    }

	(8)s.c_str();返回一个字符串s中的内容指针。返回一个指向正规的c字符串的指针常量，也就是以\0结尾的。
	   这个函数的引入是为了与C语言兼容，在c语言中没有string类型，所以我们通过string类对象的s_str成原函数把string对象转换成c语言中的字符串样式。

	   string s9 = "abc";
	   string s10 = "abC";
	   const char *p = s10.s_str();

	   char str[100];
	   strcpy_s(str,sizeof(str),p);
	   cout << str << endl;

	   记住这也是一种初始化string的方式。用的是c语言形式的字符数组(字符串)来初始化string。
	   string s11(str);   用c语言的字符数组初始化string类型。

	(9)读写string对象：

		string s1;
		cin >> s1;  从键盘输入
		cout << s1 << endl;

	(10)字面值和string相加 +
	string s1 = "abc";
	string s2 = "defg";
	string s3 = s1 + " and " + s2 +'e';
	cout << s3 << endl; 

	string s5 = "abc" +"def"; 语法上不允许这么加

	(11)范围for针对string的使用;c++11 中提供了范围for：能够遍历一个序列中的每一个元素
		string可以看成是一个字符序列。

		string s1 = " i love china "；
		for(auto c:s1){			auto ：变量类型自动推断 char
			cout << c << endl; 每次输出一个字符，后边跟一个换行符
		}

		for(auto &c : s1){
			c = toupper(c);
		}
		cout << s1 << endl;



