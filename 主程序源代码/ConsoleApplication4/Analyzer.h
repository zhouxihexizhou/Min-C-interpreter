#pragma once
#ifndef Analyzer_H
#define Analyzer_H
#include <iostream>
using namespace std;
extern int runout;//������

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
extern vari *glotree;//����ȫ�ֱ�����
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
extern function *sentree;//����������

int get_seman_value(int re, vari *h);//����ʱ���㺯���β�����ֵ
void in(int re, vari *h);//���뺯��
void out(int re, vari *h);//�������
int find_func_line(char *_str, int type);//���ݺ��������β�����type���ҵ�������ʼλ��
int findTrie(char *_str, vari *treevar);//���Ҿֲ������Ƿ��壨��2��
void createTrie(int type, char *_str, vari *treevar);//����ֲ��������ֲ�������
int findTrie(char *_str);//����ȫ�ֱ����Ƿ��壨��1��
void createTrie(int type, char *_str);//����ȫ�ֱ�����ȫ�ֱ�����
int findfunc(char *_str, int type, int retu);//���Һ����Ƿ���������ʵ�����أ�
int findfunc(char *_str, int type);//���ú���ʱ���Һ����Ƿ���������ʵ�����أ�
void createfunc(char *_str, int retu, int type, int line);//���뺯����
int get_type_value(int re);//���㺯���β�����ֵ
int func_retu_value(char *_str ,int type);//���غ�������ֵ����
int glo_func_var();//ִ��ȫ��ɨ��
int get_type(char *_str);//��ѯȫ�ֱ������ͣ���1.1��
int get_type(char *_str, vari *treevar);//��ѯ�ֲ��������ͣ�2.1��
int get_value_int(char *_str);//����ȫ�ֱ�������������ȡȫ��	������ֵ��֮������ͬ������Ϊ���أ����ز�ͬ���ͱ�����ֵ����1.2��
double get_value_real(char *_str);//��1.2��
char *get_value_string(char *_str);//��1.2��
int get_value_int(char *_str, vari *treevar);//���ݾֲ���������������ȡ�ֲ�������ֵ��֮������ͬ������Ϊ���أ����ز�ͬ���ͱ�����ֵ��
double get_value_real(char *_str, vari *treevar);
char *get_value_string(char *_str, vari *treevar);
void in_value(char *_str, int value);//����ȫ�ֱ�����ֵ��֮������ͬ������Ϊ���أ����ݱ������������£�
void in_value(char *_str, double value);
void in_value(char *_str, char *value);
void in_value(char *_str, vari *treevar, int value);//���¾ֲ�������ֵ��֮������ͬ������Ϊ���أ����ݱ������������£�
void in_value(char *_str, vari *treevar, double value);
void in_value(char *_str, vari *treevar, char *value);
#endif