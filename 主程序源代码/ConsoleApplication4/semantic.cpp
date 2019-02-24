#define _CRT_SECURE_NO_WARNINGS
#include "Analyzer.h"
#include "Lexer.h"
#include "semantic.h"
#include "calculate.h"
#include "route.h"

Ntreenode *fff;

void Ntreenode::getvalue(vari *h)
{
	double lsum = 0, rsum = 0, nowsum = 0;              //当左右子结点为实数时临时存储左、右和计算结果数值，以下为写出实数值均可临时用它们存储 
	if (lchild != NULL)              //遍历左子树 
	{
		lchild->getvalue(h);
	}
	if (runout != 0)             //每次操作后都判断是否已出错，若出错则退出函数调用 
		return;
	if (rchild != NULL)              //遍历右子树 
	{
	    rchild->getvalue(h);
	}
	if (runout != 0)
		return;
	//后面为对当前结点操作 
	if ((type == 12) || (type == 1) || (type == 32) || (type == 37))                //整数、标识符（为变量）、字符串、实型数的结点处理 
	{
		switch (type)
		{
		case 12: nsum = integ[list[nsum].token[0]-'0'].num_integ; break;
		case 1:
			if (list[nsum + 1].name == 25) {                  //函数
				int aaa1;
				int bbb1;
				if (list[nsum + 2].name != 26) {           //有参数
					aaa1 = get_seman_value(nsum + 2, h);         //获取参数类型
					front = nsum + 2;
				}
				else {
					aaa1 = 0;                             //无参数
				}
				if (findfunc(list[nsum].token, aaa1)) {          //函数存在
					bbb1 = find_func_line(list[nsum].token, aaa1);           //获取函数名下标
				}
				else {
					printf("函数未被声明\n");
					runout = 1;
					return;
				}
				int tttt = func_retu_value(list[nsum].token, aaa1);
				char tttt1[20] = { "fanhuizhi" };
				createTrie(tttt, tttt1, h);
				if (tttt == 2)
				{
					type = 12;
					int back = ppp;
					jump(bbb1, aaa1, h);
					ppp = back;
					int sasa;
					sasa = get_value_int(tttt1, h);
					nsum = sasa;
				}
				else if (tttt == 3)
				{
					type = 37;
					jump(bbb1, aaa1, h);
					nsum = get_value_int(tttt1, h);
				}
				else if (tttt == 4)
				{
					type = 32;
					jump(bbb1, aaa1, h);
					nsum = get_value_int(tttt1, h);
				}
				else
				{
					printf("行号：%d,函数返回值类型错误错误", list[nsum].line);
					exit(-1);
				}
				
				
			}
			else {                      //变量
				if (findTrie(list[nsum].token)==-1) {                //是全局变量
					double gg;
					type = get_type(list[nsum].token);
					switch (type) {
					case 2:type = 12; nsum = get_value_int(list[nsum].token); break;
					case 3:type = 37;
						gg = get_value_real(list[nsum].token);
						for (int i = 0; i < 80; i++) {
							if (real[i].num_real == gg) {
								nsum = i;
								break;
							}
						}
						break;
					case 4:type = 32;
						char *mm = get_value_string(list[nsum].token);
						for (int i = 0; i < 80; i++) {
							if (strcmp(str[i].cluster, mm)) {
								nsum = i;
								break;
							}
						}
						break;
					}
				}
				else if(findTrie(list[nsum].token, h) == -1){                                       //是局部变量
					double gg;
					type = get_type(list[nsum].token, h);                     //将该结点类型type改为对应常量类型，如整数为11
					switch (type) {
					case 2:type = 12; nsum = get_value_int(list[nsum].token, h); break;
					case 3:type = 37; 
						gg = get_value_real(list[nsum].token, h);
						for (int i = 0; i < 80; i++) {
							if (real[i].num_real==gg) {
								nsum = i;
								break;
							}
						}
						break;
					case 4:type = 32; 
						char *mm = get_value_string(list[nsum].token, h);
						for (int i = 0; i < 80; i++) {
							if (strcmp(str[i].cluster, mm)==0) {
								nsum = i;
								break;
							}
						}
						break;
					}
				}
				else {
					printf("变量未被声明\n");
					runout = 1;
					return;
				}
			}
			break;
		case 32: nsum = list[nsum].token[0]-'0'; break;      //串的位置
		case 37: nsum = list[nsum].token[0]-'0'; break;       //实型数位置
		default:  break;
		}
	}
	else if (type == 0)                //根节点处理 
	{
		type = lchild->type;
		nsum = lchild->nsum;
		strcpy(data, lchild ->data);
	}
	else
	{
		if (type == 24)        //串操作$
		{
			if ((lchild != NULL) && (rchild != NULL))       //语法判断 
			{

				if ((lchild->type == 32) && (rchild->type == 32))            //数据类型需匹配 
				{
					char *a1, *a2;
					a1 = str[lchild->nsum].cluster;
					a2 = str[rchild->nsum].cluster;
					strcpy(str[str_pit].cluster, a1);
					strcat(str[str_pit].cluster, a2);
					nsum = str_pit;
					str_pit++;
					type = 32;            //是该结点类型与操作结点类型一致，后均有此操作 
				}
				else
					runout = 1;
			}
			else
				runout = 1;
		}
		else if (type == 33)        //串操作#
		{
			if ((lchild != NULL) && (rchild != NULL))       //语法判断 
			{

				if ((lchild->type == 32)&& (rchild->type == 32))            //数据类型需匹配 
				{
					char *a1, *a2;
					a1 = str[lchild->nsum].cluster;
					a2 = str[rchild->nsum].cluster;
					if (a2[1] != NULL) {                    //右边不止一个字符
						runout = 1;
					}
					else {
						int i;
						for (i = 0; a1[i] != NULL; i++) {
							if (a1[i] == a2[0]) {
								break;
							}
							else {
								str[str_pit].cluster[i] = a1[i];
							}
						}
						for (; a1[i + 1] != NULL; i++) {
							str[str_pit].cluster[i] = a1[i + 1];
						}
					}
					nsum = str_pit;
					str_pit++;
					type = 32;
				}
				else
					runout = 1;
			}
			else
				runout = 1;
		}
		else if (type == 18)        //=操作 
		{
			if ((lchild != NULL) && (rchild != NULL))       //语法判断 
			{
				type = lchild->type;
				if ((lchild->type == 32) && (lchild->type == rchild->type))            //数据类型需匹配 
				{
					//该结点和lchild结点均与rchild结点串复制操作，并改变nsum值为对应地址;
				}
				else if ((lchild->type == 12) && (rchild->type == 12))         //左子树为整型时，右也为整型
				{
					//左侧变量值 = rchild->nsum;
					nsum == rchild->nsum;
				}
				else if (rchild->type != 32)         //左子树为实型时，右不能为字符串，其他变量类型均可 
				{
					//左侧变量值 = 右侧对应值;
					nsum == lchild->nsum;
				}
				else
					runout = 1;
			}
			else
				runout = 1;
		}
		else if (type == 30)        //,操作，只继承后续语句值 
		{
			type = rchild->type;
			nsum = rchild->nsum;
		}
		else if (type == 25)        //(操作，继承后续运算值
		{
			type = lchild->type;
			nsum = lchild->nsum;
		}
		else if (type == 36)        //!操作，与前面根节点求语句值类似，但要取反 
		{
			type = 12;          //逻辑运算结果均设为int型 
			if (lchild->type == 12)
			{
				if (lchild->nsum == 0)
					nsum = 1;
				else
					nsum = 0;
			}
			else if (lchild->type == 37)
			{
				if (integ[lchild->nsum].num_integ == 0)   //lchild->nsum位置对应实型数值integ
					nsum = 1;
				else
					nsum = 0;
			}
			else
			{
				runout = 1;
			}
		}
		else if ((lchild != NULL) && (rchild == NULL) && (type == 21))               //减号作负数标志特殊处理,后续四则运算操作类似 
		{
			if (lchild->type == 37)         //实型数应先找到对应值，得到新值并存储 
			{
				type = 37;
				lsum = real[lchild->nsum].num_real;                            //lchild->nsum位置对应实型数值
				nowsum = 0 - lsum;
				real[real_pit].num_real = nowsum;                                    //nowsum存入实数组中
				nsum = real_pit;                                          //nowsum实数组中位置
				real_pit++;
			}
			else           //常规整型数计算 
			{
				type = 12;
				nsum = 0 - lchild->nsum;
			}
		}
		else if ((lchild != NULL) && (rchild != NULL))       //语法判断 
		{
			if (((lchild->type == 12) || (lchild->type == 37)) && ((rchild->type == 12) || (rchild->type == 37)))        //剩余操作均对整型和实型运算双目操作 
			{
				switch (type)
				{
				case 13:                                            //<=运算 
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                      //lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                     //rchild->nsum位置对应实型数值;
					else
						rsum = rchild->nsum;
					if (lsum <= rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 14:                                            //<运算 
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                  //lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                  //rchild->nsum位置对应实型数值;
					else
						rsum = rchild->nsum;
					if (lsum<rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 15:                                            //>=运算  
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                 // lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                     //rchild->nsum位置对应实型数值
					else
						rsum = rchild->nsum;
					if (lsum >= rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 16:                                            //>运算 
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;            //lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;              // rchild->nsum位置对应实型数值
					else
						rsum = rchild->nsum;
					if (lsum>rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 17:                                            //==运算  
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;              // lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;               // rchild->nsum位置对应实型数值
					else
						rsum = rchild->nsum;
					if (lsum == rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 19:                                            //不等于运算  
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                 // lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                // rchild->nsum位置对应实型数值
					else
						rsum = rchild->nsum;
					if (lsum != rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 20:                                            //+运算  
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsum位置对应实型数值
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;             // rchild->nsum位置对应实型数值
						else
							rsum = rchild->nsum;
						nowsum = lsum + rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum存入实数组中
						nsum = real_pit;                                          //nowsum实数组中位置
						real_pit++;
					}
					else
					{
						type = 12;
						nsum = lchild->nsum + rchild->nsum;
					}
					break;

				case 21:                                            //-运算
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsum位置对应实型数值
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;              // rchild->nsum位置对应实型数值
						else
							rsum = rchild->nsum;
						nowsum = lsum - rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum存入实数组中
						nsum = real_pit;                                          //nowsum实数组中位置
						real_pit++;
					}
					else
					{
						type = 12;
						nsum = lchild->nsum - rchild->nsum;
					}
					break;

				case 22:                                            //*运算
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsum位置对应实型数值
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;              // rchild->nsum位置对应实型数值
						else
							rsum = rchild->nsum;
						nowsum = lsum*rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum存入实数组中
						nsum = real_pit;                                          //nowsum实数组中位置
						real_pit++;
					}
					else
					{
						type = 12;
						nsum = lchild->nsum*rchild->nsum;
					}
					break;

				case 23:                                            //除法运算
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsum位置对应实型数值
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;              // rchild->nsum位置对应实型数值
						else
							rsum = rchild->nsum;
						if (rsum == 0)              //除数不能为0 
						{
							runout = 1;
							return;
						}
						else
							nowsum = lsum / rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum存入实数组中
						nsum = real_pit;                                          //nowsum实数组中位置
						real_pit++;
					}
					else
					{
						type = 12;
						if (rchild->nsum == 0)
						{
							runout = 1;
							return;
						}
						else
							nsum = lchild->nsum / rchild->nsum;
					}
					break;

				case 38:                                            //求余数%运算
					if ((lchild->type == 37) || (rchild->type == 37))              //不能对实数操作
					{
						runout = 1;
						return;
					}
					else
					{
						type = 12;
						if (rchild->nsum == 0)              //除数不能为0 
						{
							runout = 1;
							return;
						}
						else
							nsum = lchild->nsum%rchild->nsum;
					}
					break;

				case 42:                                            //乘方运算（只对0和正整数操作，以后指数最多能为负数，不能为实数）
					if ((lchild->type == 37) || (rchild->type == 37))              //不能对实数操作
					{
						runout = 1;
						return;
					}
					else
					{
						type = 12;
						if (rchild->nsum == 0)              //指数为0时操作 
						{

							nsum = 1;
						}
						else if (rchild->nsum>0)
						{
							nsum = lchild->nsum;                     //左子树存的为底数，右子树存指数 
							for (int i = 1; i<rchild->nsum; i++)
							{
								nsum = nsum*lchild->nsum;
							}
						}
						else
						{
							runout = 1;
							return;
						}
					}
					break;

				case 34:                                            //&&运算
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;              // lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;              // rchild->nsum位置对应实型数值
					else
						rsum = rchild->nsum;
					if ((lsum != 0) && (rsum != 0))
						nsum = 1;
					else
						nsum = 0;
					break;

				case 35:                                            //||运算
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;              // lchild->nsum位置对应实型数值
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;              // rchild->nsum位置对应实型数值
					else
						rsum = rchild->nsum;
					if ((lsum != 0) || (rsum != 0))
						nsum = 1;
					else
						nsum = 0;
					break;

				default:runout = 1; break;
				}
			}
			else
				runout = 1;
		}
		else
			runout = 1;
	}
	if (lchild != NULL)              //遍历左子树 
	{
		fff = lchild;
		lchild = NULL;
		delete fff;
	}
	if (rchild != NULL)              //遍历右子树 
	{
		fff = rchild;
		rchild = NULL;
		delete fff;
	}
	return;
}

