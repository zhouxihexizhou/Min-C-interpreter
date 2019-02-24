
#include "Lexer.h"
#include "Analyzer.h"
#include "calculate.h"
int lasttype = 0;             //前一所读取三元组类型，目前0为符号，1为变量或常量 
int pit;                 //当前读取三元组位置 
int startpit;                 //开始读取三元组位置  
int endpit;                    //结束三元组位置 
int kk;                 //(括号层数，初始为之前扫描到的层数 
int nti = 0;                  //普通语句语法树数组下标 
int adv[43] = { 0, 12, 12,12,12,12,12,12,12,12,12,12,12,6,6,6,6,5,2,5,7,7,8,8,7,1,1,12,12,12,1,12,12,7,4,3,10,12,8,12,12,12,9};       //存放符号优先级，非符号设为最高以跳过该结点，根节点（type为0）优先级设为0最低，下标为种别号
int End;

extern Ntreenode *newp, *p, *q, *r;  
Ntreenode *kp;
extern Ntree ntree[200];
void Ntree::buildntree()
{
	if ((list[pit].name == 12) || (list[pit].name == 1) || (list[pit].name == 32) || (list[pit].name == 37))                //整数、标识符、字符串、实型数的结点处理 
	{
		lasttype = 1;
		newp = new Ntreenode;            //申请新空间 
		newp->type = list[pit].name;
		newp->nsum = pit;
		for (int i = 0; i < 9; i++) {
			newp->data[i] = list[pit].token[i];         //复制信息
		}
		if (q->lchild == NULL)              //成为对应未连接子结点 
		{
			q->lchild = newp;
			newp->parent = q;
			p = newp;               //p记录前一含变量常量结点
		}
		else
		{
			q->rchild = newp;
			newp->parent = q;
			p = newp;
		}
		if ((list[pit].name == 1) && (list[pit + 1].name == 25))
		{
			pit = pit + 2;
			while (list[pit].name != 26)
			{
				if ( (list[pit].name == 31) && (pit > End))
				{
					runout = 1;
					break;
				}
				pit++;
			}
		}
	}
	else if (((list[pit].name >= 13) && (list[pit].name <= 25)) || (list[pit].name == 30)|| (list[pit].name == 38) || (list[pit].name == 29) || ((list[pit].name >= 33) && (list[pit].name <= 36)) || (list[pit].name == 42))     //运算符号量加(,=的处理 
	{
		lasttype = 0;
		if (list[pit].name == 18)          //等号
		{
			if (p->type != 1 || lasttype != 1)               //等号左需为变量，否则报错，不支持a+b=c这种判错 
			{
				runout = 1;
			}
			else                //等号所赋值变量作为等号所在结点的左子结点，等号右侧为等号结点右子结点 
			{
				newp = new Ntreenode;
				newp->nsum = pit;
				newp->type = list[pit].name;
				for (int i = 0; i < 9; i++) {
					newp->data[i] = list[pit].token[i];         //复制信息
				}
				q = p->parent;                   //临时用q表示p父节点
				q->lchild = newp;
				newp->parent = q;
				newp->lchild = p;
				p->parent = newp;
				q = newp;
			}                 //最终q为前一含符号结点指针 
		}
		else if ((list[pit].name == 36) || (((list[pit - 1].name==18)||(list[pit - 1].name == 25)) && (list[pit].name == 21)))
		{
			newp = new Ntreenode;
			newp->nsum = pit;
			newp->type = list[pit].name;
			for (int i = 0; i < 9; i++) {
				newp->data[i] = list[pit].token[i];
			}
			if (q->lchild == NULL)              //成为对应未连接子结点 
			{
				q->lchild = newp;
				newp->parent = q;
				q = newp;
			}
			else
			{
				q->rchild = newp;
				newp->parent = q;
				q = newp;
			}
		}
		else if (list[pit].name == 25)        //左括号
		{
			if (lasttype == 1)           //左括号左不能为变量常量，报错 
			{
				runout = 1;
			}
			newp = new Ntreenode;
			newp->nsum = pit;
			newp->type = list[pit].name;
			for (int i = 0; i < 9; i++) {
				newp->data[i] = list[pit].token[i];         //复制信息
			}
			if (q->lchild == NULL)              //含（结点优先级最高，成为前一符号或根节点对应未连接子结点 
			{
				q->lchild = newp;
				newp->parent = q;
				q = newp;               //q记录前一含符号结点
				kp = newp;         //kp记录前一(结点
			}
			else
			{
				q->rchild = newp;
				newp->parent = q;
				q = newp;
				kp = newp;         //kp记录前一(结点
			}
		}
		//        个人觉得这中间可加入$和#的特殊处理 
		else if(list[pit].name!=29)
		{
			newp = new Ntreenode;
			newp->nsum = pit;
			newp->type = list[pit].name;
			for (int i = 0; i < 9; i++) {
				newp->data[i] = list[pit].token[i];         //复制信息
			}
			if (adv[q->type] >= adv[newp->type])                //优先级比较 
			{
				if ((list[pit].name == 42) && (adv[q->type] == adv[newp->type]))           //乘方特殊处理
				{                                         //乘方符号连续出现时，直接作为前一符号结点子结点
					if (q->lchild == p)
					{
						newp->lchild = p;
						q->lchild = newp;
						newp->parent = q;
						q = newp;
					}
					else
					{
						newp->lchild = p;
						q->rchild = newp;
						newp->parent = q;
						q = newp;
					}
				}
				else
				{
					r = q;
					while (adv[r->parent->type] >= adv[newp->type])            //寻找比newp符号优先级低的r->parent结点 
					{
						r = r->parent;
					}
					q = r->parent;                      //临时用q表示r父节点 
					if (r == q->lchild)             //找到后newp作为该r->parent结点对应子结点，r作为newp左子结点 
					{
						q->lchild = newp;
						newp->parent = q;
						newp->lchild = r;
						r->parent = newp;
					}
					else
					{
						q->rchild = newp;
						newp->parent = q;
						newp->lchild = r;
						r->parent = newp;
					}
					q = newp;                        //最终q为前一含符号结点指针 
				}
			}
			else
			{
				if (q->lchild == p)             //newp优先级比前一含符号结点高时，直接作为前一符号结点子结点，原些符号连接的变量（除'('）所在指针p作为newp子结点 
				{
					newp->lchild = p;
					q->lchild = newp;
					newp->parent = q;
					q = newp;
				}
				else
				{
					newp->lchild = p;
					q->rchild = newp;
					newp->parent = q;
					q = newp;
				}
			}
		}else {

        }
	}else
		runout = 1;              //其他符号判错 
	pit++;        //扫描下一三元组 
	return;
}


void creatNtree(int start, int end)      //建造普通语法树函数 
{
	p = ntree[nti].root;
	q = p;
	r = p;
	pit = start;
	ntree[nti].root->type = 0;
	End = end;
	while ((list[pit].name != 30) && (list[pit].name != 31) && (pit <= end)) {
		if (runout == 1)
			break;
		if (list[pit].name == 25)                 //(种别号
		{
			kk++;
		}
		if (list[pit].name == 26)                 //)种别号
		{
			kk--;
			if (kk < 0)              //（数与）数不匹配 
			{
				runout = 1;
			}
			else
			{
				q = kp->parent;
				p = kp;
				while (kp->parent != NULL)
				{
					kp = kp->parent;
					if (kp->type == 25)
						break;
				}
			}
			pit++;
			continue;
		}
		ntree[nti].buildntree();     //分步建树
	}
	if (kk != 0)         //（数与）数不匹配 
		runout = 1;
}



//测试函数
int deep;

void Ntreenode::show()            //中序遍历查看内容 
{
	int deepi = 0;         //计数i 
	if (lchild != NULL)              //遍历左子树 
	{
		deep++;
		lchild->show();
		deep--;
	}
	for (deepi = 0; deepi<deep - 1; deepi++)            //深度1开始无空格，深度0特殊处理 
		cout << "  "; //没深入一层多两个空格（可自行调整空格数） 
	if (deep == 0)
	{
		cout << nsum << endl;          //对于根节点只显示nsum值 
	}
	else           //连续三行分别为该结点三种属性值 
	{
		cout << nsum << endl;
		for (deepi = 0; deepi<deep - 1; deepi++)            //深度1开始无空格，深度0特殊处理 
			cout << "  "; //没深入一层多两个空格（可自行调整空格数）
		cout << type << endl;
		if (type == 32)         //对于实型数和字符串需找到对应位置内容 
		{
//			cout << ... << endl;
		}
		else if (type == 37)
		{
//			cout << ... << endl;
		}
		else
		{
			for (deepi = 0; deepi<deep - 1; deepi++)            //深度1开始无空格，深度0特殊处理 
				cout << "  "; //没深入一层多两个空格（可自行调整空格数）
			cout << data << endl;
		}
	}
	if (rchild != NULL)              //遍历右子树 
	{
	deep++;
	rchild->show();
	deep--;
	}
	return;
}