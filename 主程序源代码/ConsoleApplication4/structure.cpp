
#include "Lexer.h"
#include "Analyzer.h"
#include "calculate.h"
int lasttype = 0;             //ǰһ����ȡ��Ԫ�����ͣ�Ŀǰ0Ϊ���ţ�1Ϊ�������� 
int pit;                 //��ǰ��ȡ��Ԫ��λ�� 
int startpit;                 //��ʼ��ȡ��Ԫ��λ��  
int endpit;                    //������Ԫ��λ�� 
int kk;                 //(���Ų�������ʼΪ֮ǰɨ�赽�Ĳ��� 
int nti = 0;                  //��ͨ����﷨�������±� 
int adv[43] = { 0, 12, 12,12,12,12,12,12,12,12,12,12,12,6,6,6,6,5,2,5,7,7,8,8,7,1,1,12,12,12,1,12,12,7,4,3,10,12,8,12,12,12,9};       //��ŷ������ȼ����Ƿ�����Ϊ����������ý�㣬���ڵ㣨typeΪ0�����ȼ���Ϊ0��ͣ��±�Ϊ�ֱ��
int End;

extern Ntreenode *newp, *p, *q, *r;  
Ntreenode *kp;
extern Ntree ntree[200];
void Ntree::buildntree()
{
	if ((list[pit].name == 12) || (list[pit].name == 1) || (list[pit].name == 32) || (list[pit].name == 37))                //��������ʶ�����ַ�����ʵ�����Ľ�㴦�� 
	{
		lasttype = 1;
		newp = new Ntreenode;            //�����¿ռ� 
		newp->type = list[pit].name;
		newp->nsum = pit;
		for (int i = 0; i < 9; i++) {
			newp->data[i] = list[pit].token[i];         //������Ϣ
		}
		if (q->lchild == NULL)              //��Ϊ��Ӧδ�����ӽ�� 
		{
			q->lchild = newp;
			newp->parent = q;
			p = newp;               //p��¼ǰһ�������������
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
	else if (((list[pit].name >= 13) && (list[pit].name <= 25)) || (list[pit].name == 30)|| (list[pit].name == 38) || (list[pit].name == 29) || ((list[pit].name >= 33) && (list[pit].name <= 36)) || (list[pit].name == 42))     //�����������(,=�Ĵ��� 
	{
		lasttype = 0;
		if (list[pit].name == 18)          //�Ⱥ�
		{
			if (p->type != 1 || lasttype != 1)               //�Ⱥ�����Ϊ���������򱨴���֧��a+b=c�����д� 
			{
				runout = 1;
			}
			else                //�Ⱥ�����ֵ������Ϊ�Ⱥ����ڽ������ӽ�㣬�Ⱥ��Ҳ�Ϊ�ȺŽ�����ӽ�� 
			{
				newp = new Ntreenode;
				newp->nsum = pit;
				newp->type = list[pit].name;
				for (int i = 0; i < 9; i++) {
					newp->data[i] = list[pit].token[i];         //������Ϣ
				}
				q = p->parent;                   //��ʱ��q��ʾp���ڵ�
				q->lchild = newp;
				newp->parent = q;
				newp->lchild = p;
				p->parent = newp;
				q = newp;
			}                 //����qΪǰһ�����Ž��ָ�� 
		}
		else if ((list[pit].name == 36) || (((list[pit - 1].name==18)||(list[pit - 1].name == 25)) && (list[pit].name == 21)))
		{
			newp = new Ntreenode;
			newp->nsum = pit;
			newp->type = list[pit].name;
			for (int i = 0; i < 9; i++) {
				newp->data[i] = list[pit].token[i];
			}
			if (q->lchild == NULL)              //��Ϊ��Ӧδ�����ӽ�� 
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
		else if (list[pit].name == 25)        //������
		{
			if (lasttype == 1)           //����������Ϊ�������������� 
			{
				runout = 1;
			}
			newp = new Ntreenode;
			newp->nsum = pit;
			newp->type = list[pit].name;
			for (int i = 0; i < 9; i++) {
				newp->data[i] = list[pit].token[i];         //������Ϣ
			}
			if (q->lchild == NULL)              //����������ȼ���ߣ���Ϊǰһ���Ż���ڵ��Ӧδ�����ӽ�� 
			{
				q->lchild = newp;
				newp->parent = q;
				q = newp;               //q��¼ǰһ�����Ž��
				kp = newp;         //kp��¼ǰһ(���
			}
			else
			{
				q->rchild = newp;
				newp->parent = q;
				q = newp;
				kp = newp;         //kp��¼ǰһ(���
			}
		}
		//        ���˾������м�ɼ���$��#�����⴦�� 
		else if(list[pit].name!=29)
		{
			newp = new Ntreenode;
			newp->nsum = pit;
			newp->type = list[pit].name;
			for (int i = 0; i < 9; i++) {
				newp->data[i] = list[pit].token[i];         //������Ϣ
			}
			if (adv[q->type] >= adv[newp->type])                //���ȼ��Ƚ� 
			{
				if ((list[pit].name == 42) && (adv[q->type] == adv[newp->type]))           //�˷����⴦��
				{                                         //�˷�������������ʱ��ֱ����Ϊǰһ���Ž���ӽ��
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
					while (adv[r->parent->type] >= adv[newp->type])            //Ѱ�ұ�newp�������ȼ��͵�r->parent��� 
					{
						r = r->parent;
					}
					q = r->parent;                      //��ʱ��q��ʾr���ڵ� 
					if (r == q->lchild)             //�ҵ���newp��Ϊ��r->parent����Ӧ�ӽ�㣬r��Ϊnewp���ӽ�� 
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
					q = newp;                        //����qΪǰһ�����Ž��ָ�� 
				}
			}
			else
			{
				if (q->lchild == p)             //newp���ȼ���ǰһ�����Ž���ʱ��ֱ����Ϊǰһ���Ž���ӽ�㣬ԭЩ�������ӵı�������'('������ָ��p��Ϊnewp�ӽ�� 
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
		runout = 1;              //���������д� 
	pit++;        //ɨ����һ��Ԫ�� 
	return;
}


void creatNtree(int start, int end)      //������ͨ�﷨������ 
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
		if (list[pit].name == 25)                 //(�ֱ��
		{
			kk++;
		}
		if (list[pit].name == 26)                 //)�ֱ��
		{
			kk--;
			if (kk < 0)              //�����룩����ƥ�� 
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
		ntree[nti].buildntree();     //�ֲ�����
	}
	if (kk != 0)         //�����룩����ƥ�� 
		runout = 1;
}



//���Ժ���
int deep;

void Ntreenode::show()            //��������鿴���� 
{
	int deepi = 0;         //����i 
	if (lchild != NULL)              //���������� 
	{
		deep++;
		lchild->show();
		deep--;
	}
	for (deepi = 0; deepi<deep - 1; deepi++)            //���1��ʼ�޿ո����0���⴦�� 
		cout << "  "; //û����һ��������ո񣨿����е����ո����� 
	if (deep == 0)
	{
		cout << nsum << endl;          //���ڸ��ڵ�ֻ��ʾnsumֵ 
	}
	else           //�������зֱ�Ϊ�ý����������ֵ 
	{
		cout << nsum << endl;
		for (deepi = 0; deepi<deep - 1; deepi++)            //���1��ʼ�޿ո����0���⴦�� 
			cout << "  "; //û����һ��������ո񣨿����е����ո�����
		cout << type << endl;
		if (type == 32)         //����ʵ�������ַ������ҵ���Ӧλ������ 
		{
//			cout << ... << endl;
		}
		else if (type == 37)
		{
//			cout << ... << endl;
		}
		else
		{
			for (deepi = 0; deepi<deep - 1; deepi++)            //���1��ʼ�޿ո����0���⴦�� 
				cout << "  "; //û����һ��������ո񣨿����е����ո�����
			cout << data << endl;
		}
	}
	if (rchild != NULL)              //���������� 
	{
	deep++;
	rchild->show();
	deep--;
	}
	return;
}