#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <iostream>
#include "Analyzer.h"
#include "Lexer.h"
#include "semantic.h"



int get_type(char *_str)//��ѯȫ�ֱ�������

{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->type;
}
int get_type(char *_str, vari *treevar)//��ѯ�ֲ���������

{
	int len = strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->type;
}
int get_value_int(char *_str)//����ȫ�ֱ�������������ȡȫ�ֱ�����ֵ

{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->a1;
}
double get_value_real(char *_str)
{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->a2;
}
char *get_value_string(char *_str)

{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->a3;
}
int get_value_int(char *_str, vari *treevar)//���ݾֲ���������������ȡ�ֲ�������ֵ
{
	int ssssss= strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<ssssss; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->a1;
}
double get_value_real(char *_str, vari *treevar)
{
	int len = strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->a2;
}
char *get_value_string(char *_str, vari *treevar)
{
	int len = strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->a3;
}
void in_value(char *_str, int value)//����ȫ�ֱ�����ֵ
{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	p->a1 = value;
}
void in_value(char *_str, double value)
{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	p->a2 = value;
}
void in_value(char *_str, char *value)
{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	strcpy(p->a3, value);
}
void in_value(char *_str, vari *treevar, int value)//���¾ֲ�������ֵ
{
	int len = strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	p->a1 = value;
}
void in_value(char *_str, vari *treevar, double value)
{
	int len = strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	p->a2 = value;
}
void in_value(char *_str, vari *treevar, char *value)
{
	int len = strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	strcpy(p->a3, value);
}
int findTrie(char *_str, vari *treevar)//���Ҿֲ������Ƿ���
{
	int len = strlen(_str);
	vari *p = treevar;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
		if (p == NULL)   //��Ϊ�ռ�����ʾû��������
			return 1;
		if (i == len - 1)
		{
			if (p->type >= 0)
				return -1;
			else return 1;
		}
	}
}
void createTrie(int type, char *_str, vari *treevar)//����ֲ�����
{
	int len = strlen(_str);
	vari *p = treevar, *q;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		if (p->next[id] == NULL)
		{
			if (i == len - 1)
			{
				q = (vari *)malloc(sizeof(vari));
				q->type = type;
				for (int j = 0; j<83; ++j)
					q->next[j] = NULL;
				p->next[id] = q;
			}
			else
			{
				q = (vari *)malloc(sizeof(vari));
				for (int j = 0; j < 83; ++j)
					q->next[j] = NULL;
				p->next[id] = q;
				p = p->next[id];
			}
		}
		else
		{
			if (i == len - 1)
			{
				p->next[id]->type = type;
			}
			else
			{
				p = p->next[id];
			}
		}
	}
}
int findTrie(char *_str)//����ȫ�ֱ����Ƿ���
{
	int len = strlen(_str);
	vari *p = glotree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
		if (p == NULL)
			return 1;
		if (i == len - 1)
		{
			if (p->type >= 0)
				return -1;
			else return 1;
		}
	}
}
void createTrie(int type, char *_str)//����ȫ�ֱ���
{
	int len = strlen(_str);
	vari *p = glotree, *q;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		if (p->next[id] == NULL)
		{
			if (i == len - 1)
			{
				q = (vari *)malloc(sizeof(vari));
				q->type = type;
				for (int j = 0; j<83; ++j)
					q->next[j] = NULL;
				p->next[id] = q;
			}
			else
			{
				q = (vari *)malloc(sizeof(vari));
				for (int j = 0; j < 83; ++j)
					q->next[j] = NULL;
				p->next[id] = q;
				p = p->next[id];
			}
		}
		else
		{
			if (i == len - 1)
			{
				p->next[id]->type = type;
			}
			else
			{
				p = p->next[id];
			}
		}
	}
}
int findfunc(char *_str, int type, int retu)//���Һ����Ƿ�����
{
	int len = strlen(_str);
	function *p = sentree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
		if (p == NULL)
			return 1;
		if (i == len - 1)
		{
			if (p->line[type] >= 0)
			{
				if (p->retu[type] == retu)
				{
					return -1;
				}
				else
				{
					return -2;
				}
			}
			else return 1;
		}
	}
}
int findfunc(char *_str, int type)
{
	int len = strlen(_str);
	function *p = sentree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
		if (p == NULL)
			return -1;
		if (i == len - 1)
		{
			if (p->line[type] < 0)
			{
				return -1;
			}
			else return 1;
		}
	}
}
int find_func_line(char *_str, int type)//���ݺ��������β�����type���ҵ�������ʼλ��
{
	int len = strlen(_str);
	function *p = sentree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->line[type];
}
void createfunc(char *_str, int retu, int type, int line)//����ȫ�ֺ���
{
	int len = strlen(_str);
	function *p = sentree, *q;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		if (p->next[id] == NULL)
		{
			if (i == len - 1)
			{
				q = (function *)malloc(sizeof(function));
				q->line[type] = line;
				q->type[type] = type;
				q->retu[type] = retu;
				for (int j = 0; j<83; ++j)
					q->next[j] = NULL;
				p->next[id] = q;
				p = p->next[id];
			}
			else
			{
				q = (function *)malloc(sizeof(function));
				for (int j = 0; j < 83; ++j)
					q->next[j] = NULL;
				p->next[id] = q;
				p = p->next[id];
			}
		}
		else
		{
			if (i == len - 1)
			{
				p->next[id]->line[type] = line;
				p->next[id]->type[type] = type;
				p->next[id]->retu[type] = retu;
			}
			else
			{
				p = p->next[id];
			}
		}
	}
}

int get_type_value(int re)//���㺯���β�����ֵ
{
	int ss = 0;
	while (list[re].name != 26)
	{
		if (list[re].name == 30)
		{
			re++;
			continue;
		}

		else if (list[re].name >=2 && list[re].name <= 4)
		{
			ss = ss + list[re].name;
			re++;
		}
		else re++;
	}
	return ss;
}
int func_retu_value(char *_str,int type)
{
	int len = strlen(_str);
	function *p = sentree;
	for (int i = 0; i<len; ++i)
	{
		int id = _str[i] - '0';
		p = p->next[id];
	}
	return p->retu[type];
}
int get_seman_value(int re, vari *h)//����ʱ���㺯���β�����ֵ
{
	int ss = 0;
	while (list[re].name != 26)
	{
		if (list[re].name == 1)
		{
			if (findTrie(list[re].token)==-1)
			{
				int typp;
				typp = get_type(list[re].token);
				if (typp == 2)
				{
					ss = ss + 2;
				}
				else if (typp == 3)
				{
					ss = ss + 3;
				}
				else if (typp == 4)
				{
					ss = ss + 4;
				}
			}
			else if (findTrie(list[re].token,h)==-1)
			{
				int typp;
				typp = get_type(list[re].token, h);
				if (typp == 2)
				{
					ss = ss + 2;
				}
				else if (typp == 3)
				{
					ss = ss + 3;
				}
				else if (typp == 4)
				{
					ss = ss + 4;
				}
			}
			else
			{
				printf("����δ����");
			}
			re++;
		}
		else if (list[re].name == 30)
		{
			re++;
			continue;
		}

		else if (list[re].name == 37)
		{
			ss = ss + 3;
			re++;
		}
		else if (list[re].name == 12) {
			ss = ss + 2;
			re++;
		}else re++;
	}
	return ss;
}
int glo_func_var()//��һ��ɨ�裬��������ȫ�ֱ����ͺ�����ȫ�ֱ������ͺ�����
{

	int i = 0;
	while (list[i].token[0] != NULL)//
	{
		if ((list[i].name >= 2 && list[i].name <= 4) || (list[i].name == 11 || list[i].name == 10))
		{
			if (list[i].name == 11)
			{
				i = i + 2;
				int ss = get_type_value(i);
				i = i - 1;
				int settreess = findfunc(list[i].token, ss, list[i - 1].name);
				if (settreess == 1)
				{
					createfunc(list[i].token, list[i - 1].name, ss, i);
					int re = 1;
					while (list[i].name != 27)
					{
						i++;
					}
					while (re != 0)
					{
						i++;
						if (list[i].name == 27) re++;
						else if (list[i].name == 28) re--;
					}
					i++;
				}
				else
				{
					runout = 1;
					if (settreess == -1)
					{
						printf("�кţ�%d,����%s�ظ�����", list[i].line, list[i].token);
						return 0;
					}
					else if (settreess == -2)
					{
						printf("�кţ�%d,����%s�����ܽ����ݷ���ֵ���������غ���", list[i].line, list[i].token);
						return 0;
					}
					else
					{
						printf("�кţ�%d,����%sϵͳ�������", list[i].line, list[i].token);
					}
				}
			}
			else if (list[i].name >= 2 && list[i].name <= 4)
			{
				if (list[i + 2].name == 25)
				{
					i = i + 2;
					int ss = get_type_value(i);
					i = i - 1;
					int settreess = findfunc(list[i].token, ss, list[i - 1].name);
					if (settreess == 1)
					{
						createfunc(list[i].token, list[i - 1].name, ss, i);
						int re = 1;
						while (list[i].name != 27)
						{
							i++;
						}
						while (re != 0)
						{
							i++;
							if (list[i].name == 27) re++;
							else if (list[i].name == 28) re--;
						}
						i++;
					}
					else
					{
						runout = 1;
						if (settreess == -1)
						{
							printf("�кţ�%d,����%s�ظ�����", list[i].line, list[i].token);
							return 0;
						}
						else if (settreess == -2)
						{
							printf("�кţ�%d,����%s�����ܽ����ݷ���ֵ���������غ���", list[i].line, list[i].token);
							return 0;
						}
						else
						{
							printf("�кţ�%d,����%sϵͳ�������", list[i].line, list[i].token);
						}
					}
				}
				else
				{
					int type = list[i].name;
					while (list[i].name != 31)
					{
						i++;
						if (findTrie(list[i].token) == 1)
						{
							createTrie(type, list[i].token);
						}
						else
						{
							runout = 1;
							printf("�кţ�%d,����%s�ظ�����", list[i].line, list[i].token);
							return 0;
						}
						if (list[i + 1].name == 18)
						{
							if (type == 2)
							{
								int sss = i + 2;
								while (list[sss].name != 30 && list[sss].name != 31)
								{
									sss++;
								}
								vari *ssr;
								ssr = (vari *)malloc(sizeof(vari));
								for (int i = 0; i < 83; i++)
								{
									ssr->next[i] = NULL;
								}
								int svalue = seman(i + 2, sss, ssr, 0);
								in_value(list[i].token, svalue);
							}
							else if (type == 3)
							{
								int sss = i + 2;
								while (list[sss].name != 30 && list[sss].name != 31)
								{
									sss++;
								}
								vari *ssr;
								ssr = (vari *)malloc(sizeof(vari));
								for (int i = 0; i < 83; i++)
								{
									ssr->next[i] = NULL;
								}
								double svalue = seman(i + 2, sss, ssr, 0, 0);
								in_value(list[i].token, svalue);
							}
							else if (type == 4)
							{
								int sss = i + 2;
								while (list[sss].name != 30 && list[sss].name != 31)
								{
									sss++;
								}
								vari *ssr;
								ssr = (vari *)malloc(sizeof(vari));
								for (int i = 0; i < 83; i++)
								{
									ssr->next[i] = NULL;
								}
								char *svalue = seman(i + 2, sss, ssr, 0, 0, 0);
								in_value(list[i].token, svalue);
							}
						}
						while (list[i].name != 30 && list[i].name != 31)
						{
							i++;
						}
					}
					i++;
				}
			}
			else if (list[i].name == 10)
			{
				lef = i + 3;
				int re = 1;
				while (list[i].name != 27)
				{
					i++;
				}
				while (re != 0)
				{
					i++;
					if (list[i].name == 27) re++;
					else if (list[i].name == 28) re--;
				}
				i++;
				rig = i-1;
			}
		}
	}
}