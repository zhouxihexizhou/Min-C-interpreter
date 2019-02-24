#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <string.h>
#include <stdlib.h> 
#include <iostream>
#include "Analyzer.h"
#include "Lexer.h"
void out(int re, vari *h)
{
	re++;
	if (list[re].name == 29)
	{
		re++;
		int ss = list[re].token[0] - '0';
		printf("%s", str[ss].cluster);
		if (list[re + 2].name == 31)
		{
			return;
		}
		else
		{
			re = re + 3;
			if (findTrie(list[re].token) == -1)
			{
				int ss1 = get_type(list[re].token);
				if (ss1 == 2)
				{
					int value;
					value = get_value_int(list[re].token);
					printf("%d", value);
				}
				else if (ss1 == 3)
				{
					double value;
					value = get_value_real(list[re].token);
					printf("%lf", value);
				}
				else if (ss1 = 4)
				{
					char *value;
					value = get_value_string(list[re].token);
					printf("%s", value);
				}
			}
			else if (findTrie(list[re].token, h) == -1)
			{
				int ss1 = get_type(list[re].token, h);
				if (ss1 == 2)
				{
					int value;
					value = get_value_int(list[re].token, h);
					printf("%d", value);
				}
				else if (ss1 == 3)
				{
					double value;
					value = get_value_real(list[re].token, h);
					printf("%lf", value);
				}
				else if (ss1 = 4)
				{
					char *value;
					value = get_value_string(list[re].token, h);
					printf("%s", value);
				}
			}
			else
			{
				printf("行号%d：变量%s没有声明", list[re].line, list[re].token);
				return;
			}
		}
	}
	else
	{
		if (list[re].name == 1)
		{
			re++;
			if (list[re].name == 31)
			{
				re--;
				if (findTrie(list[re].token) == -1)
				{
					int ss1 = get_type(list[re].token);
					if (ss1 == 2)
					{
						int value;
						value = get_value_int(list[re].token);
						printf("%d", value);
						return;
					}
					else if (ss1 == 3)
					{
						double value;
						value = get_value_real(list[re].token);
						printf("%lf", value);
						return;
					}
					else if (ss1 = 4)
					{
						char *value;
						value = get_value_string(list[re].token);
						printf("%s", value);
						return;
					}
				}
				else if (findTrie(list[re].token, h) == -1)
				{
					int ss1 = get_type(list[re].token, h);
					if (ss1 == 2)
					{
						int value;
						value = get_value_int(list[re].token, h);
						printf("%d", value);
					}
					else if (ss1 == 3)
					{
						double value;
						value = get_value_real(list[re].token, h);
						printf("%lf", value);
					}
					else if (ss1 = 4)
					{
						char *value;
						value = get_value_string(list[re].token, h);
						printf("%s", value);
					}
				}
				else
				{
					printf("行号%d：变量%s没有声明", list[re].line, list[re].token);
					return;
				}
			}
			else
			{
				if (list[re].name == 30)
				{
					re = re + 2;
					int value = list[re].token[0] - '0';
					char *ss3 = str[value].cluster;
					int value1;
					if (findTrie(list[re - 3].token) == -1)
					{
						value1 = get_value_int(list[re - 3].token);
					}
					else if (findTrie(list[re - 3].token, h) == -1)
					{
						value1 = get_value_int(list[re - 3].token, h);
					}
					else
					{
						printf("行号%d：变量%s没有声明", list[re - 3].line, list[re - 3].token);
						return;
					}
					
					for (int i = 0; i < value1; i++)
					{
						printf("%s", ss3);
					}
					return;
				}
				else
				{
					printf("错误的输出类型。");
					return;
				}
			}
		}
		else if (list[re].name == 12)
		{
			int value = list[re].token[0] - '0';
			int value1 = integ[value].num_integ;
			char *ss4;
			re = re + 3;
			int value3 = list[re].token[0] - '0';
			ss4 = str[value3].cluster;
			for (int i = 0; i < value1; i++)
			{
				printf("%s", ss4);
			}
			return;
		}
	}
}