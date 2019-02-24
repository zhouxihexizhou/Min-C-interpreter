#pragma once
#ifndef Lexer_H
#define Lexer_H
#include <iostream>
extern char sentence[100000];
extern int lef;
extern int rig;

void lexer();

void read();

void protreeset(int start, int end);

struct List {                    //��Ԫ������
	char token[9] = { NULL };         //token
	int name = 0;              //�����
	int line = 0;              //�к�
};
extern struct List list[2000];


struct Str {                 //��¼���Ľṹ
	char cluster[50] = { NULL };        //������
};
extern struct Str str[80];


struct Real {               //��¼ʵ�����Ľṹ
	double num_real;           //ʵ��������
};
extern struct Real real[80];


struct Integ {               //��¼�������Ľṹ
	int num_integ;           //����������
};
extern struct Integ integ[80];


extern int str_pit;         //�����к�
extern int real_pit;        //ʵ�����к�
extern int integ_pit;         //�������к�

#endif