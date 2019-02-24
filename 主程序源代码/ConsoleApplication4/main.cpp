#include<stdio.h>
#include<string.h>
#include <iostream>
#include "Analyzer.h"
#include "Lexer.h"
#include "route.h"
struct List list[2000];
struct Real real[80];
struct Str str[80];
Integ integ[80];
char sentence[100000] = { "\0" };
vari *glotree;
function *sentree;
int front;
int runout = 0;//报错
int lef = 1;
int rig = 1;
int chuan = -1;
int main()
{
	sentree = (function *)malloc(sizeof(function));
	for (int i = 0; i < 83; i++)
	{
		sentree->next[i] = NULL;
	}
	glotree = (vari *)malloc(sizeof(vari));
	for (int i = 0; i < 83; i++)
	{
		glotree->next[i] = NULL;
	}
	read();//打开读取文件

	lexer();//词法分析
	if (runout == 1)
	{
		return 0;
	}
	glo_func_var();//语法分析第一遍扫描
	if (runout == 1)
	{
		return 0;
	}
	protreeset(lef, rig);//语法分析第二遍扫描


	system("pause");

}