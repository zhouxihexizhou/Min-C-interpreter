#include"Lexer.h"
#include"route.h"
#include "Analyzer.h"
#include "semantic.h"
#include "calculate.h"

void protreeset(int start, int end);

void check(int ch, vari *h,vari *h1);                   //������ַ��б�

void circulation(int head, int tail, vari *h);

void circul(int head, int tail, vari *h);

void judge(int head, int mid1, int mid2, int tail, vari *h);

int ppp;             //��Ԫ��ɨ��λ��

int type;        //�����ñ���






void jump(int head, int t, vari *h) {
	nti++;
	int tail;
	vari *treepit;
	treepit = (vari *)malloc(sizeof(vari));       //���ɺ����ľֲ�������
	for (int i = 0; i < 83; i++)
	{
		treepit->next[i] = NULL;
	}
	ppp = head;
	if (t == 0) {               //�޲���
		while (list[ppp].name != 27) {
			ppp++;
		}
		ppp = ppp + 1;
		tail = ppp;
		int bracket = 1;
		while (bracket != 0) {
			if (list[tail].name == 27)
				bracket++;
			if (list[tail].name == 28)
				bracket--;
			tail++;
		}
		tail = tail - 1;
		while (ppp < tail) {
			check(list[ppp].name, treepit,h);
		}
	}
	else {
		while (list[ppp].name != 27) {
			if (list[ppp].name == 2) {
				if (list[front].name == 1) {
					createTrie(2, list[ppp + 1].token, treepit);
					if (findTrie(list[front].token) == -1) {               //ȫ�ֱ����Ѷ���
						in_value(list[ppp + 1].token, treepit, get_value_int(list[front].token));   //��ȡȫ�ֱ���ֵ
					}
					else if (findTrie(list[front].token, h) == -1) {        //�ֲ������Ѷ���
						in_value(list[ppp + 1].token, treepit, get_value_int(list[front].token, h));   //��ȡ�ֲ�����ֵ
					}
					else {
						printf("����δ������\n");
						runout = 1;
						return;
					}
					front = front + 2;
				}
				else {
					createTrie(2, list[ppp + 1].token, treepit);
					in_value(list[ppp + 1].token, treepit, integ[list[front].token[0] - '0'].num_integ);
					front = front + 2;
				}
			}
			else if (list[ppp].name == 3) {
				if (list[front].name == 1) {
					createTrie(3, list[ppp + 1].token, treepit);
					if (findTrie(list[front].token) == -1) {               //ȫ�ֱ����Ѷ���
						in_value(list[ppp + 1].token, treepit, get_value_real(list[front].token));   //��ȡȫ�ֱ���ֵ
					}
					else if (findTrie(list[front].token, h) == -1) {        //�ֲ������Ѷ���
						in_value(list[ppp + 1].token, treepit, get_value_real(list[front].token, h));   //��ȡ�ֲ�����ֵ
					}
					else {
						printf("����δ������\n");
						runout = 1;
						return;
					}
					front = front + 2;
				}
				else {
					createTrie(3, list[ppp + 1].token, treepit);
					in_value(list[ppp + 1].token, treepit, real[list[front].token[0] - '0'].num_real);
					front = front + 2;
				}
			}
			else if (list[ppp].name == 4) {
				if (list[front].name == 1) {
					createTrie(4, list[ppp + 1].token, treepit);
					if (findTrie(list[front].token) == -1) {               //ȫ�ֱ����Ѷ���
						in_value(list[ppp + 1].token, treepit, get_value_string(list[front].token));   //��ȡȫ�ֱ���ֵ
					}
					else if (findTrie(list[front].token, h) == -1) {        //�ֲ������Ѷ���
						in_value(list[ppp + 1].token, treepit, get_value_string(list[front].token, h));   //��ȡ�ֲ�����ֵ
					}
					else {
						printf("����δ������\n");
						runout = 1;
						return;
					}
					front = front + 2;
				}
				else {
					createTrie(4, list[ppp + 1].token, treepit);
					in_value(list[ppp + 1].token, treepit, str[list[front].token[0] - '0'].cluster);
					front = front + 2;
				}
			}
			ppp++;
		}
		ppp = ppp + 1;
		tail = ppp;
		int bracket = 1;
		while (bracket != 0) {
			if (list[tail].name == 27)
				bracket++;
			if (list[tail].name == 28)
				bracket--;
			tail++;
		}
		tail = tail - 1;
		while (ppp < tail) {
			check(list[ppp].name, treepit,h);
		}
	}
	nti--;
}



void circul(int head, int tail, vari *h) {       //do_untilѭ����䴦��
	int right = tail;
	int left = tail;
	while (list[left].name != 28) {
		left--;
	}
	left = left + 2;
	do {
		ppp = head + 2;
		while (ppp < left-2) {
			check(list[ppp].name, h,h);
		}
	} while (seman(left, right, h, 0)==0);
}



void circulation(int head, int tail, vari *h,vari *h1) {            //ѭ����䴦��
	int left = head + 1;
	while (list[head].name != 27) {
		head++;
	}
	int right = head - 1;
	while (seman(left, right, h, 0)) {          //�����жϣ����㷵��1�������㷵��0
		ppp = head + 1;
		while (ppp < tail) {           //ִ��elseǰ���
			check(list[ppp].name, h,h);
		}
	}
}



void judge(int head, int mid1, int mid2, int tail, vari *h,vari *h1) {  //������䴦��
	int left = head + 1;
	while (list[head].name != 27) {
		head++;
	}
	int right = head - 1;
	if (seman(left, right, h, 0)) {               //�����жϣ����㷵��1�������㷵��0,����Ϊ�������ұ�1λ�����������1λ
		ppp = head + 1;
		while (ppp < mid1) {           //ִ��elseǰ���
			check(list[ppp].name, h,h1);
		}
	}
	else {
		if (tail > mid2) {            //�������else
			ppp = mid2 + 1;
			while (ppp < tail) {           //ִ��else�����
				check(list[ppp].name, h,h1);
			}
		}
	}
}



void check(int ch, vari *h,vari *h1) {         //������ַ��б�
	int a, b, m1, m2;
	switch (ch) {
	case 1:
		if (list[ppp + 1].name == 18) {          //��ֵ���
			if (findTrie(list[ppp].token)==-1) {                  //ȫ�ֱ����Ѷ���
				a = get_type(list[ppp].token);
				switch (a) {
				case 2:in_value(list[ppp].token, seman(ppp + 2, 10000, h, 0)); break;
				case 3:in_value(list[ppp].token, seman(ppp + 2, 10000, h, 0, 0)); break;
				case 4:in_value(list[ppp].token, seman(ppp + 2, 10000, h, 0, 0, 0)); break;
				}
			}
			else {                                            //ȫ�ֱ���δ����
				if (findTrie(list[ppp].token, h)==-1) {           //�ֲ������Ѷ���
					a = get_type(list[ppp].token, h);          //��ѯ��������
					switch (a) {
					case 2:in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0)); 
						break;
					case 3:in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0, 0)); 
						break;
					case 4:in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0, 0, 0)); 
						break;
					}
				}
				else {                                      //δ����
					createTrie(2, list[ppp].token, h);             //Ĭ��Ϊint�ͱ���
					in_value(list[ppp].token, h, seman(ppp + 2, 10000, h, 0));
				}
			}
			while (list[ppp].name != 31) {
				ppp++;
			}
			ppp++;
		}
		else {                        //��������
			if (list[ppp + 2].name != 26) {           //�в���
				a = get_seman_value(ppp + 2, h);           //��ȡ��������
				front = ppp + 2;
			}
			else {
				a = 0;                             //�޲���
			}
			if (findfunc(list[ppp].token, a)) {          //��������
				b = find_func_line(list[ppp].token, a);            //��ȡ�������±�
			}
			else {
				printf("����δ������\n");
				runout = 1;
				return;
			}
			while (list[ppp].name != 31) {
				ppp++;
			}
			int back = ppp + 1;
			
			jump(b, a, h);
			ppp = back;
		}
		break;
	case 2:
		type = list[ppp].name;
		while (list[ppp].name != 31) {          //int�������
			ppp++;
			if (findTrie(list[ppp].token) == -1) {
				printf("��������ȫ�ֱ����ظ�\n");
				runout = 1;
				return;
			}else if (findTrie(list[ppp].token, h)){           //���Ҿֲ������Ƿ���
				createTrie(type, list[ppp].token, h);      //û���������ֲ��������﷨��
			}
			else {
				printf("��������ֲ������ظ�\n");
				runout = 1;
				return;
			}
			ppp++;
			if (list[ppp].name == 18)
			{
				int svalue = seman(ppp + 1, 10000, h, 0);
				in_value(list[ppp-1].token, h, svalue);        //���¾ֲ�������ֵ
				while (list[ppp].name != 30 && list[ppp].name != 31) {
					ppp++;
				}
			}
		}
		ppp++;
		break;
	case 3:
		type = list[ppp].name;
		while (list[ppp].name != 31) {          //real�������
			ppp++;
			if (findTrie(list[ppp].token) == -1) {
				printf("��������ȫ�ֱ����ظ�\n");
				runout = 1;
				return;
			}
			else if (findTrie(list[ppp].token, h)) {           //���Ҿֲ������Ƿ���
				createTrie(type, list[ppp].token, h);      //û���������ֲ��������﷨��
			}
			else {
				printf("��������ֲ������ظ�\n");
				runout = 1;
				return;
			}
			ppp++;
			if (list[ppp].name == 18)
			{
				double svalue = seman(ppp + 1, 10000, h, 0, 0);
				in_value(list[ppp - 1].token, h, svalue);        //���¾ֲ�������ֵ
				while (list[ppp].name != 30 && list[ppp].name != 31) {
					ppp++;
				}
			}
		}
		ppp++;
		break;
	case 4:
		type = list[ppp].name;
		while (list[ppp].name != 31) {          //string�������
			ppp++;
			if (findTrie(list[ppp].token) == -1) {
				printf("��������ȫ�ֱ����ظ�\n");
				runout = 1;
				return;
			}
			else if (findTrie(list[ppp].token, h)) {           //���Ҿֲ������Ƿ���
				createTrie(type, list[ppp].token, h);      //û���������ֲ��������﷨��
			}
			else {
				printf("��������ֲ������ظ�\n");
				runout = 1;
				return;
			}
			ppp++;
			if (list[ppp].name == 18)
			{
				char *svalue = seman(ppp + 1, 10000, h, 0, 0, 0);
				in_value(list[ppp - 1].token, h, svalue);        //���¾ֲ�������ֵ
				while (list[ppp].name != 30 && list[ppp].name != 31) {
					ppp++;
				}
			}
		}
		ppp++;
		break;
	case 5:
		a = ppp;
		while (list[a].name != 27)           //ѭ�����
			a++;
		a++;
		b = 1;
		while (b != 0) {
			if (list[a].name == 27)
				b++;
			if (list[a].name == 28)
				b--;
			a++;
		}
		circulation(ppp, a-1, h,h1);            //����Ϊwhile�ؼ��ֺ�������
		ppp = a;
		break;
	case 6:                                   //�������
		a = ppp;
		while (list[a].name != 27)
			a++;
		a++;
		b = 1;
		while (b != 0) {
			if (list[a].name == 27)
				b++;
			if (list[a].name == 28)
				b--;
			a++;
		}
		m1 = a - 1;
		m2 = m1 + 2;
		if (list[a].name == 7) {
			a = a + 2;
			b = 1;
			while (b != 0) {
				if (list[a].name == 27)
					b++;
				if (list[a].name == 28)
					b--;
				a++;
			}
		}
		judge(ppp, m1, m2, a-1, h,h1);                        //��ȡ�����ж����,ch-m1Ϊelseǰ��䣬m2-t-1Ϊelse�����
		ppp = a;
		break;
	case 9:
		a = ppp;
		while (list[ppp].name != 31) {          //�������
			ppp++;
		}
		b = ppp - 1;
		in(a, h);                 //�����������,������in�ؼ��ֵ��ֺ�ǰ1λ
		ppp++;
		break;
	case 8:
		a = ppp;
		while (list[ppp].name != 31) {          //������
			ppp++;
		}
		b = ppp - 1;
	    out(a, h);                 //����������
		ppp++;
		break;
	case 27:ppp++; break;            //{
	case 28:ppp++; break;            //}
	case 31:ppp++; break;            //;
	case 40:
		a = ppp;
		a = a + 2;
		b = 1;
		while (b != 0) {
			if (list[a].name == 27)         //do_untilѭ��
				b++;
			if (list[a].name == 28)
				b--;
			a++;
		}
		while (list[a].name != 31) {
			a++;
		}
		circul(ppp, a - 1, h);            //����Ϊdo�ؼ��ֺͷֺ�ǰһλ
		ppp = a+1;
		break;
	case 39:
		char tttt1[20] = { "fanhuizhi" };
		int ssssr=get_type(tttt1, h1);
		if (ssssr == 2)
		{
			in_value(tttt1, h1, seman(ppp+1, 10000, h, 0));
		}
		else if (ssssr==3)
		{
			in_value(tttt1, h1, seman(ppp+1, 10000, h, 0, 0));
		}
		else if (ssssr==4)
		{
			in_value(tttt1, h1, seman(ppp+1, 10000, h, 0, 0, 0));
		}
		while (list[ppp].name != 31) {
			ppp++;
		}
		ppp = ppp + 1;
		break;
	}   
}



void protreeset(int start, int end) {     //��main��ͷִ�е���β

	vari *treepit;
	treepit = (vari *)malloc(sizeof(vari));       //����main�����ľֲ�������
	for (int i = 0; i < 83; i++)
	{
		treepit->next[i] = NULL;
	}
	ppp = start + 1;
	while (ppp < end) {
		check(list[ppp].name, treepit, treepit);
	}
	delete treepit;                          //���پֲ�����
}