#pragma once
#ifndef Calculate_H
#define Calculate_H
#include<iostream>
#include "Analyzer.h"

extern int lasttype;             //前一所读取三元组类型，目前0为符号，1为变量或常量 
extern int pit;                 //当前读取三元组位置 
extern int startpit;                 //开始读取三元组位置  
extern int endpit;                    //结束三元组位置 
extern int kk;                 //(括号层数，初始为之前扫描到的层数 
extern int nti;                  //普通语句语法树数组下标 
extern int adv[43];            //存放符号优先级，非符号设为最高以跳过该结点，根节点（type为0）优先级设为0最低，下标为种别号   
extern int deep;


class Ntreenode        //普通语句语法树结点类 
{
public:
	int nsum;            //nsum为此节点为根的子树运数算值或字符串结果的地址下标 
	int type;            //目前暂指种别号，type为0为根节点 
	char data[9];        //该结点存储数据，与三元组token对应 
	Ntreenode *lchild, *rchild, *parent;          //子结点和父结点指针 
	Ntreenode()           //构造函数 
	{
		nsum = 0;
		type = 0;
		for(int i=0;i<9;i++)
		    data[i] = NULL;
		lchild = NULL;
		rchild = NULL;
		parent = NULL;
	}
	void getvalue(vari *h);         //后序遍历当前结点nsum值函数，返回语句值 
	void show();
};                //newp为新结点，p为前一含变量常量结点，q为前一含符号结点,r为当前父节点与newp比较优先级结点


class Ntree           //普通语句语法树类 
{
public:
	Ntreenode *root;          //根节点指针 
	Ntree()                 //构造函数
	{
		root = new Ntreenode;
	}
	void buildntree();         //分步建树函数 
};       //语法树对象

void creatNtree(int start, int end);

#endif