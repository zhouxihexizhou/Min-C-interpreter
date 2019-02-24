#pragma once
#ifndef Calculate_H
#define Calculate_H
#include<iostream>
#include "Analyzer.h"

extern int lasttype;             //ǰһ����ȡ��Ԫ�����ͣ�Ŀǰ0Ϊ���ţ�1Ϊ�������� 
extern int pit;                 //��ǰ��ȡ��Ԫ��λ�� 
extern int startpit;                 //��ʼ��ȡ��Ԫ��λ��  
extern int endpit;                    //������Ԫ��λ�� 
extern int kk;                 //(���Ų�������ʼΪ֮ǰɨ�赽�Ĳ��� 
extern int nti;                  //��ͨ����﷨�������±� 
extern int adv[43];            //��ŷ������ȼ����Ƿ�����Ϊ����������ý�㣬���ڵ㣨typeΪ0�����ȼ���Ϊ0��ͣ��±�Ϊ�ֱ��   
extern int deep;


class Ntreenode        //��ͨ����﷨������� 
{
public:
	int nsum;            //nsumΪ�˽ڵ�Ϊ��������������ֵ���ַ�������ĵ�ַ�±� 
	int type;            //Ŀǰ��ָ�ֱ�ţ�typeΪ0Ϊ���ڵ� 
	char data[9];        //�ý��洢���ݣ�����Ԫ��token��Ӧ 
	Ntreenode *lchild, *rchild, *parent;          //�ӽ��͸����ָ�� 
	Ntreenode()           //���캯�� 
	{
		nsum = 0;
		type = 0;
		for(int i=0;i<9;i++)
		    data[i] = NULL;
		lchild = NULL;
		rchild = NULL;
		parent = NULL;
	}
	void getvalue(vari *h);         //���������ǰ���nsumֵ�������������ֵ 
	void show();
};                //newpΪ�½�㣬pΪǰһ������������㣬qΪǰһ�����Ž��,rΪ��ǰ���ڵ���newp�Ƚ����ȼ����


class Ntree           //��ͨ����﷨���� 
{
public:
	Ntreenode *root;          //���ڵ�ָ�� 
	Ntree()                 //���캯��
	{
		root = new Ntreenode;
	}
	void buildntree();         //�ֲ��������� 
};       //�﷨������

void creatNtree(int start, int end);

#endif