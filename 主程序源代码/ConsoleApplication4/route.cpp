#include"Lexer.h"
#include"route.h"
#include "Analyzer.h"
#include "semantic.h"
#include "calculate.h"

void protreeset(int start, int end);

void check(int ch, vari *h,vari *h1);                   //语句首字符判别

void circulation(int head, int tail, vari *h);

void circul(int head, int tail, vari *h);

void judge(int head, int mid1, int mid2, int tail, vari *h);

int ppp;             //三元组扫描位置

int type;        //计算用变量






void jump(int head, int t, vari *h) {
	nti++;
	int tail;
	vari *treepit;
	treepit = (vari *)malloc(sizeof(vari));       //生成函数的局部变量树
	for (int i = 0; i < 83; i++)
	{
		treepit->next[i] = NULL;
	}
	ppp = head;
	if (t == 0) {               //无参数
		while (list[ppp].name != 27) {
			ppp++;
		}
		ppp = ppp + 1;
		tail = ppp;
		int bracket = 1;
		while (bracket != 0) {
			if (list[tail].name == 27)
				bracket++;
			if (list[tail].name == 28)
				bracket--;
			tail++;
		}
		tail = tail - 1;
		while (ppp < tail) {
			check(list[ppp].name, treepit,h);
		}
	}
	else {
		while (list[ppp].name != 27) {
			if (list[ppp].name == 2) {
				if (list[front].name == 1) {
					createTrie(2, list[ppp + 1].token, treepit);
					if (findTrie(list[front].token) == -1) {               //全局变量已定义
						in_value(list[ppp + 1].token, treepit, get_value_int(list[front].token));   //获取全局变量值
					}
					else if (findTrie(list[front].token, h) == -1) {        //局部变量已定义
						in_value(list[ppp + 1].token, treepit, get_value_int(list[front].token, h));   //获取局部变量值
					}
					else {
						printf("变量未被声明\n");
						runout = 1;
						return;
					}
					front = front + 2;
				}
				else {
					createTrie(2, list[ppp + 1].token, treepit);
					in_value(list[ppp + 1].token, treepit, integ[list[front].token[0] - '0'].num_integ);
					front = front + 2;
				}
			}
			else if (list[ppp].name == 3) {
				if (list[front].name == 1) {
					createTrie(3, list[ppp + 1].token, treepit);
					if (findTrie(list[front].token) == -1) {               //全局变量已定义
						in_value(list[ppp + 1].token, treepit, get_value_real(list[front].token));   //获取全局变量值
					}
					else if (findTrie(list[front].token, h) == -1) {        //局部变量已定义
						in_value(list[ppp + 1].token, treepit, get_value_real(list[front].token, h));   //获取局部变量值
					}
					else {
						printf("变量未被声明\n");
						runout = 1;
						return;
					}
					front = front + 2;
				}
				else {
					createTrie(3, list[ppp + 1].token, treepit);
					in_value(list[ppp + 1].token, treepit, real[list[front].token[0] - '0'].num_real);
					front = front + 2;
				}
			}
			else if (list[ppp].name == 4) {
				if (list[front].name == 1) {
					createTrie(4, list[ppp + 1].token, treepit);
					if (findTrie(list[front].token) == -1) {               //全局变量已定义
						in_value(list[ppp + 1].token, treepit, get_value_string(list[front].token));   //获取全局变量值
					}
					else if (findTrie(list[front].token, h) == -1) {        //局部变量已定义
						in_value(list[ppp + 1].token, treepit, get_value_string(list[front].token, h));   //获取局部变量值
					}
					else {
						printf("变量未被声明\n");
						runout = 1;
						return;
					}
					front = front + 2;
				}
				else {
					createTrie(4, list[ppp + 1].token, treepit);
					in_value(list[ppp + 1].token, treepit, str[list[front].token[0] - '0'].cluster);
					front = front + 2;
				}
			}
			ppp++;
		}
		ppp = ppp + 1;
		tail = ppp;
		int bracket = 1;
		while (bracket != 0) {
			if (list[tail].name == 27)
				bracket++;
			if (list[tail].name == 28)
				bracket--;
			tail++;
		}
		tail = tail - 1;
		while (ppp < tail) {
			check(list[ppp].name, treepit,h);
		}
	}
	nti--;
}



void circul(int head, int tail, vari *h) {       //do_until循环语句处理
	int right = tail;
	int left = tail;
	while (list[left].name != 28) {
		left--;
	}
	left = left + 2;
	do {
		ppp = head + 2;
		while (ppp < left-2) {
			check(list[ppp].name, h,h);
		}
	} while (seman(left, right, h, 0)==0);
}



void circulation(int head, int tail, vari *h,vari *h1) {            //循环语句处理
	int left = head + 1;
	while (list[head].name != 27) {
		head++;
	}
	int right = head - 1;
	while (seman(left, right, h, 0)) {          //条件判断，满足返回1，不满足返回0
		ppp = head + 1;
		while (ppp < tail) {           //执行else前语句
			check(list[ppp].name, h,h);
		}
	}
}



void judge(int head, int mid1, int mid2, int tail, vari *h,vari *h1) {  //条件语句处理
	int left = head + 1;
	while (list[head].name != 27) {
		head++;
	}
	int right = head - 1;
	if (seman(left, right, h, 0)) {               //条件判断，满足返回1，不满足返回0,参数为左括号右边1位和右括号左边1位
		ppp = head + 1;
		while (ppp < mid1) {           //执行else前语句
			check(list[ppp].name, h,h1);
		}
	}
	else {
		if (tail > mid2) {            //如果存在else
			ppp = mid2 + 1;
			while (ppp < tail) {           //执行else后语句
				check(list[ppp].name, h,h1);
			}
		}
	}
}



void check(int ch, vari *h,vari *h1) {         //语句首字符判别
	int a, b, m1, m2;
	switch (ch) {
	case 1:
		if (list[ppp + 1].name == 18) {          //赋值语句
			if (findTrie(list[ppp].token)==-1) {                  //全局变量已定义
				a = get_type(list[ppp].token);
				switch (a) {
				case 2:in_value(list[ppp].token, seman(ppp + 2, 10000, h, 0)); break;
				case 3:in_value(list[ppp].token, seman(ppp + 2, 10000, h, 0, 0)); break;
				case 4:in_value(list[ppp].token, seman(ppp + 2, 10000, h, 0, 0, 0)); break;
				}
			}
			else {                                            //全局变量未定义
				if (findTrie(list[ppp].token, h)==-1) {           //局部变量已定义
					a = get_type(list[ppp].token, h);          //查询变量类型
					switch (a) {
					case 2:in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0)); 
						break;
					case 3:in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0, 0)); 
						break;
					case 4:in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0, 0, 0)); 
						break;
					}
				}
				else {                                      //未声明
					createTrie(2, list[ppp].token, h);             //默认为int型变量
					in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0));
				}
			}
			while (list[ppp].name != 31) {
				ppp++;
			}
			ppp++;
		}
		else {                        //函数调用
			if (list[ppp + 2].name != 26) {           //有参数
				a = get_seman_value(ppp + 2, h);           //获取参数类型
				front = ppp + 2;
			}
			else {
				a = 0;                             //无参数
			}
			if (findfunc(list[ppp].token, a)) {          //函数存在
				b = find_func_line(list[ppp].token, a);            //获取函数名下标
			}
			else {
				printf("函数未被声明\n");
				runout = 1;
				return;
			}
			while (list[ppp].name != 31) {
				ppp++;
			}
			int back = ppp + 1;
			
			jump(b, a, h);
			ppp = back;
		}
		break;
	case 2:
		type = list[ppp].name;
		while (list[ppp].name != 31) {          //int声明语句
			ppp++;
			if (findTrie(list[ppp].token) == -1) {
				printf("变量名与全局变量重复\n");
				runout = 1;
				return;
			}else if (findTrie(list[ppp].token, h)){           //查找局部变量是否定义
				createTrie(type, list[ppp].token, h);      //没定义则插入局部变量到语法树
			}
			else {
				printf("变量名与局部变量重复\n");
				runout = 1;
				return;
			}
			ppp++;
			if (list[ppp].name == 18)
			{
				int svalue = seman(ppp + 1, 10000, h, 0);
				in_value(list[ppp-1].token, h, svalue);        //更新局部变量的值
				while (list[ppp].name != 30 && list[ppp].name != 31) {
					ppp++;
				}
			}
		}
		ppp++;
		break;
	case 3:
		type = list[ppp].name;
		while (list[ppp].name != 31) {          //real声明语句
			ppp++;
			if (findTrie(list[ppp].token) == -1) {
				printf("变量名与全局变量重复\n");
				runout = 1;
				return;
			}
			else if (findTrie(list[ppp].token, h)) {           //查找局部变量是否定义
				createTrie(type, list[ppp].token, h);      //没定义则插入局部变量到语法树
			}
			else {
				printf("变量名与局部变量重复\n");
				runout = 1;
				return;
			}
			ppp++;
			if (list[ppp].name == 18)
			{
				double svalue = seman(ppp + 1, 10000, h, 0, 0);
				in_value(list[ppp - 1].token, h, svalue);        //更新局部变量的值
				while (list[ppp].name != 30 && list[ppp].name != 31) {
					ppp++;
				}
			}
		}
		ppp++;
		break;
	case 4:
		type = list[ppp].name;
		while (list[ppp].name != 31) {          //string声明语句
			ppp++;
			if (findTrie(list[ppp].token) == -1) {
				printf("变量名与全局变量重复\n");
				runout = 1;
				return;
			}
			else if (findTrie(list[ppp].token, h)) {           //查找局部变量是否定义
				createTrie(type, list[ppp].token, h);      //没定义则插入局部变量到语法树
			}
			else {
				printf("变量名与局部变量重复\n");
				runout = 1;
				return;
			}
			ppp++;
			if (list[ppp].name == 18)
			{
				char *svalue = seman(ppp + 1, 10000, h, 0, 0, 0);
				in_value(list[ppp - 1].token, h, svalue);        //更新局部变量的值
				while (list[ppp].name != 30 && list[ppp].name != 31) {
					ppp++;
				}
			}
		}
		ppp++;
		break;
	case 5:
		a = ppp;
		while (list[a].name != 27)           //循环语句
			a++;
		a++;
		b = 1;
		while (b != 0) {
			if (list[a].name == 27)
				b++;
			if (list[a].name == 28)
				b--;
			a++;
		}
		circulation(ppp, a-1, h,h1);            //参数为while关键字和右括号
		ppp = a;
		break;
	case 6:                                   //条件语句
		a = ppp;
		while (list[a].name != 27)
			a++;
		a++;
		b = 1;
		while (b != 0) {
			if (list[a].name == 27)
				b++;
			if (list[a].name == 28)
				b--;
			a++;
		}
		m1 = a - 1;
		m2 = m1 + 2;
		if (list[a].name == 7) {
			a = a + 2;
			b = 1;
			while (b != 0) {
				if (list[a].name == 27)
					b++;
				if (list[a].name == 28)
					b--;
				a++;
			}
		}
		judge(ppp, m1, m2, a-1, h,h1);                        //提取整个判断语句,ch-m1为else前语句，m2-t-1为else后语句
		ppp = a;
		break;
	case 9:
		a = ppp;
		while (list[ppp].name != 31) {          //输入语句
			ppp++;
		}
		b = ppp - 1;
		in(a, h);                 //处理输入语句,参数从in关键字到分号前1位
		ppp++;
		break;
	case 8:
		a = ppp;
		while (list[ppp].name != 31) {          //输出语句
			ppp++;
		}
		b = ppp - 1;
	    out(a, h);                 //处理输出语句
		ppp++;
		break;
	case 27:ppp++; break;            //{
	case 28:ppp++; break;            //}
	case 31:ppp++; break;            //;
	case 40:
		a = ppp;
		a = a + 2;
		b = 1;
		while (b != 0) {
			if (list[a].name == 27)         //do_until循环
				b++;
			if (list[a].name == 28)
				b--;
			a++;
		}
		while (list[a].name != 31) {
			a++;
		}
		circul(ppp, a - 1, h);            //参数为do关键字和分号前一位
		ppp = a+1;
		break;
	case 39:
		char tttt1[20] = { "fanhuizhi" };
		int ssssr=get_type(tttt1, h1);
		if (ssssr == 2)
		{
			in_value(tttt1, h1, seman(ppp+1, 10000, h, 0));
		}
		else if (ssssr==3)
		{
			in_value(tttt1, h1, seman(ppp+1, 10000, h, 0, 0));
		}
		else if (ssssr==4)
		{
			in_value(tttt1, h1, seman(ppp+1, 10000, h, 0, 0, 0));
		}
		while (list[ppp].name != 31) {
			ppp++;
		}
		ppp = ppp + 1;
		break;
	}   
}



void protreeset(int start, int end) {     //从main开头执行到结尾

	vari *treepit;
	treepit = (vari *)malloc(sizeof(vari));       //生成main函数的局部变量树
	for (int i = 0; i < 83; i++)
	{
		treepit->next[i] = NULL;
	}
	ppp = start + 1;
	while (ppp < end) {
		check(list[ppp].name, treepit, treepit);
	}
	delete treepit;                          //销毁局部变量
}