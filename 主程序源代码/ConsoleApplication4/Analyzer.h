#pragma once
#ifndef Analyzer_H
#define Analyzer_H
#include <iostream>
using namespace std;
extern int runout;//报错数

struct vari
{
	int type;
	int a1;
	double a2;
	char a3[100];
	vari *next[83];
	vari()
	{
		type = -1;
	}
};
extern vari *glotree;//创建全局变量树
struct function
{
	int line[20];
	int type[100];
	int retu[20];
	function *next[83];

	function()
	{
		for (int i = 0; i <= 19; i++)
		{
			line[i] = -1;
			type[i] = -1;
			retu[i] = -1;
		}
	}
};
extern function *sentree;//创建函数树

int get_seman_value(int re, vari *h);//调用时计算函数形参类型值
void in(int re, vari *h);//输入函数
void out(int re, vari *h);//输出函数
int find_func_line(char *_str, int type);//根据函数名和形参类型type来找到函数开始位置
int findTrie(char *_str, vari *treevar);//查找局部变量是否定义（毕2）
void createTrie(int type, char *_str, vari *treevar);//插入局部变量到局部变量树
int findTrie(char *_str);//查找全局变量是否定义（毕1）
void createTrie(int type, char *_str);//插入全局变量到全局变量树
int findfunc(char *_str, int type, int retu);//查找函数是否被声明（已实现重载）
int findfunc(char *_str, int type);//调用函数时查找函数是否被声明（已实现重载）
void createfunc(char *_str, int retu, int type, int line);//插入函数树
int get_type_value(int re);//计算函数形参类型值
int func_retu_value(char *_str ,int type);//返回函数返回值类别号
int glo_func_var();//执行全局扫描
int get_type(char *_str);//查询全局变量类型（毕1.1）
int get_type(char *_str, vari *treevar);//查询局部变量类型（2.1）
int get_value_int(char *_str);//根据全局变量的类型来获取全局	变量的值（之后两个同名函数为重载，返回不同类型变量的值）（1.2）
double get_value_real(char *_str);//（1.2）
char *get_value_string(char *_str);//（1.2）
int get_value_int(char *_str, vari *treevar);//根据局部变量的类型来获取局部变量的值（之后两个同名函数为重载，返回不同类型变量的值）
double get_value_real(char *_str, vari *treevar);
char *get_value_string(char *_str, vari *treevar);
void in_value(char *_str, int value);//更新全局变量的值（之后两个同名函数为重载，根据变量类型来更新）
void in_value(char *_str, double value);
void in_value(char *_str, char *value);
void in_value(char *_str, vari *treevar, int value);//更新局部变量的值（之后两个同名函数为重载，根据变量类型来更新）
void in_value(char *_str, vari *treevar, double value);
void in_value(char *_str, vari *treevar, char *value);
#endif