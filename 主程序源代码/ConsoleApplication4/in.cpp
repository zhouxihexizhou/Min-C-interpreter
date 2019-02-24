#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <string.h>
#include <stdlib.h> 
#include <iostream>
#include "Analyzer.h"
#include "Lexer.h"
void in(int re, vari *h)
{
	re++;
	if (list[re].name == 29)
	{
		re++;
		int aa = list[re].token[0] - '0';
		char *ss = str[aa].cluster;
		printf("%s", ss);
		re = re + 3;
		if (findTrie(list[re].token) == -1)
		{
			int ss1 = get_type(list[re].token);
			if (ss1 == 2)
			{
				int value;
				scanf("%d", &value);
				in_value(list[re].token, value);
			}
			else if (ss1 == 3)
			{
				double value;
				scanf("%lf", &value);
				in_value(list[re].token, value);
			}
			else if (ss1 = 4)
			{
				char src[100];
				scanf("%s", src);
				in_value(list[re].token, src);
			}
		}
		else if (findTrie(list[re].token, h) == -1)
		{
			int ss1 = get_type(list[re].token, h);
			if (ss1 == 2)
			{
				int value;
				scanf("%d", &value);
				in_value(list[re].token, h, value);
			}
			else if (ss1 == 3)
			{
				double value;
				scanf("%lf", &value);
				in_value(list[re].token, h, value);
			}
			else if (ss1 = 4)
			{
				char src[100];
				scanf("%s", src);
				in_value(list[re].token, h, src);
			}
		}
		else
		{
			printf("行号%d：变量%s没有声明", list[re].line, list[re].token);
			return;
		}
	}
	else if (list[re].name == 1)
	{
		if (findTrie(list[re].token) == -1)
		{
			int ss1 = get_type(list[re].token);
			if (ss1 == 2)
			{
				int value;
				scanf("%d", &value);
				in_value(list[re].token, value);
			}
			else if (ss1 == 3)
			{
				double value;
				scanf("%lf", &value);
				in_value(list[re].token, value);
			}
			else if (ss1 = 4)
			{
				char src[100];
				scanf("%s", src);
				in_value(list[re].token, src);
			}
		}
		else if (findTrie(list[re].token, h) == -1)
		{
			int ss1 = get_type(list[re].token, h);
			if (ss1 == 2)
			{
				int value;
				scanf("%d", &value);
				in_value(list[re].token, h, value);
			}
			else if (ss1 == 3)
			{
				double value;
				scanf("%lf", &value);
				in_value(list[re].token, h, value);
			}
			else if (ss1 = 4)
			{
				char src[100];
				scanf("%s", src);
				in_value(list[re].token, h, src);
			}
		}
		else
		{
			printf("行号%d：变量%s没有声明", list[re].line, list[re].token);
			return;
		}
	}
	return;
}