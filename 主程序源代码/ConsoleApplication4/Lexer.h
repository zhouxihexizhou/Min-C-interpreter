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

struct List {                    //三元组数组
	char token[9] = { NULL };         //token
	int name = 0;              //种类号
	int line = 0;              //行号
};
extern struct List list[2000];


struct Str {                 //记录串的结构
	char cluster[50] = { NULL };        //串内容
};
extern struct Str str[80];


struct Real {               //记录实型数的结构
	double num_real;           //实型数内容
};
extern struct Real real[80];


struct Integ {               //记录整型数的结构
	int num_integ;           //整型数内容
};
extern struct Integ integ[80];


extern int str_pit;         //串组行号
extern int real_pit;        //实型数行号
extern int integ_pit;         //整型数行号

#endif