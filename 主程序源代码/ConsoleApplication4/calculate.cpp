#include "Lexer.h"
#include "Analyzer.h"
#include "semantic.h"
#include "calculate.h"


Ntreenode *newp, *p, *q, *r;

Ntree ntree[200];

int seman(int start, int end, vari *h, int a1) {
	
	
	creatNtree(start, end);

	ntree[nti].root->getvalue(h);

	p = ntree[nti].root;
	if (p->type == 12)
	{
		return p->nsum;
	}
	else
	{
		runout = 1;
		return 0;
	} 
}


double seman(int start, int end, vari *h, int a1, int a2) {

	creatNtree(start, end);

	ntree[nti].root->getvalue(h);

	p = ntree[nti].root;
	if (p->type == 37)
	{
		return real[p->nsum].num_real;
	}
	else
	{
		runout = 1;
		return 0;
	}
}

char *seman(int start, int end, vari *h, int a1, int a2, int a3) {

	creatNtree(start, end);

	ntree[nti].root->getvalue(h);

	p = ntree[nti].root;
	if (p->type == 32)
	{
		return str[p->nsum].cluster;
	}
	else
	{
		runout = 1;
	}
}