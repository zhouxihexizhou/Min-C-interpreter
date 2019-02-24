#define _CRT_SECURE_NO_WARNINGS
#include "Analyzer.h"
#include "Lexer.h"
#include "semantic.h"
#include "calculate.h"
#include "route.h"

Ntreenode *fff;

void Ntreenode::getvalue(vari *h)
{
	double lsum = 0, rsum = 0, nowsum = 0;              //�������ӽ��Ϊʵ��ʱ��ʱ�洢���Һͼ�������ֵ������Ϊд��ʵ��ֵ������ʱ�����Ǵ洢 
	if (lchild != NULL)              //���������� 
	{
		lchild->getvalue(h);
	}
	if (runout != 0)             //ÿ�β������ж��Ƿ��ѳ������������˳��������� 
		return;
	if (rchild != NULL)              //���������� 
	{
	    rchild->getvalue(h);
	}
	if (runout != 0)
		return;
	//����Ϊ�Ե�ǰ������ 
	if ((type == 12) || (type == 1) || (type == 32) || (type == 37))                //��������ʶ����Ϊ���������ַ�����ʵ�����Ľ�㴦�� 
	{
		switch (type)
		{
		case 12: nsum = integ[list[nsum].token[0]-'0'].num_integ; break;
		case 1:
			if (list[nsum + 1].name == 25) {                  //����
				int aaa1;
				int bbb1;
				if (list[nsum + 2].name != 26) {           //�в���
					aaa1 = get_seman_value(nsum + 2, h);         //��ȡ��������
					front = nsum + 2;
				}
				else {
					aaa1 = 0;                             //�޲���
				}
				if (findfunc(list[nsum].token, aaa1)) {          //��������
					bbb1 = find_func_line(list[nsum].token, aaa1);           //��ȡ�������±�
				}
				else {
					printf("����δ������\n");
					runout = 1;
					return;
				}
				int tttt = func_retu_value(list[nsum].token, aaa1);
				char tttt1[20] = { "fanhuizhi" };
				createTrie(tttt, tttt1, h);
				if (tttt == 2)
				{
					type = 12;
					int back = ppp;
					jump(bbb1, aaa1, h);
					ppp = back;
					int sasa;
					sasa = get_value_int(tttt1, h);
					nsum = sasa;
				}
				else if (tttt == 3)
				{
					type = 37;
					jump(bbb1, aaa1, h);
					nsum = get_value_int(tttt1, h);
				}
				else if (tttt == 4)
				{
					type = 32;
					jump(bbb1, aaa1, h);
					nsum = get_value_int(tttt1, h);
				}
				else
				{
					printf("�кţ�%d,��������ֵ���ʹ������", list[nsum].line);
					exit(-1);
				}
				
				
			}
			else {                      //����
				if (findTrie(list[nsum].token)==-1) {                //��ȫ�ֱ���
					double gg;
					type = get_type(list[nsum].token);
					switch (type) {
					case 2:type = 12; nsum = get_value_int(list[nsum].token); break;
					case 3:type = 37;
						gg = get_value_real(list[nsum].token);
						for (int i = 0; i < 80; i++) {
							if (real[i].num_real == gg) {
								nsum = i;
								break;
							}
						}
						break;
					case 4:type = 32;
						char *mm = get_value_string(list[nsum].token);
						for (int i = 0; i < 80; i++) {
							if (strcmp(str[i].cluster, mm)) {
								nsum = i;
								break;
							}
						}
						break;
					}
				}
				else if(findTrie(list[nsum].token, h) == -1){                                       //�Ǿֲ�����
					double gg;
					type = get_type(list[nsum].token, h);                     //���ý������type��Ϊ��Ӧ�������ͣ�������Ϊ11
					switch (type) {
					case 2:type = 12; nsum = get_value_int(list[nsum].token, h); break;
					case 3:type = 37; 
						gg = get_value_real(list[nsum].token, h);
						for (int i = 0; i < 80; i++) {
							if (real[i].num_real==gg) {
								nsum = i;
								break;
							}
						}
						break;
					case 4:type = 32; 
						char *mm = get_value_string(list[nsum].token, h);
						for (int i = 0; i < 80; i++) {
							if (strcmp(str[i].cluster, mm)==0) {
								nsum = i;
								break;
							}
						}
						break;
					}
				}
				else {
					printf("����δ������\n");
					runout = 1;
					return;
				}
			}
			break;
		case 32: nsum = list[nsum].token[0]-'0'; break;      //����λ��
		case 37: nsum = list[nsum].token[0]-'0'; break;       //ʵ����λ��
		default:  break;
		}
	}
	else if (type == 0)                //���ڵ㴦�� 
	{
		type = lchild->type;
		nsum = lchild->nsum;
		strcpy(data, lchild ->data);
	}
	else
	{
		if (type == 24)        //������$
		{
			if ((lchild != NULL) && (rchild != NULL))       //�﷨�ж� 
			{

				if ((lchild->type == 32) && (rchild->type == 32))            //����������ƥ�� 
				{
					char *a1, *a2;
					a1 = str[lchild->nsum].cluster;
					a2 = str[rchild->nsum].cluster;
					strcpy(str[str_pit].cluster, a1);
					strcat(str[str_pit].cluster, a2);
					nsum = str_pit;
					str_pit++;
					type = 32;            //�Ǹý������������������һ�£�����д˲��� 
				}
				else
					runout = 1;
			}
			else
				runout = 1;
		}
		else if (type == 33)        //������#
		{
			if ((lchild != NULL) && (rchild != NULL))       //�﷨�ж� 
			{

				if ((lchild->type == 32)&& (rchild->type == 32))            //����������ƥ�� 
				{
					char *a1, *a2;
					a1 = str[lchild->nsum].cluster;
					a2 = str[rchild->nsum].cluster;
					if (a2[1] != NULL) {                    //�ұ߲�ֹһ���ַ�
						runout = 1;
					}
					else {
						int i;
						for (i = 0; a1[i] != NULL; i++) {
							if (a1[i] == a2[0]) {
								break;
							}
							else {
								str[str_pit].cluster[i] = a1[i];
							}
						}
						for (; a1[i + 1] != NULL; i++) {
							str[str_pit].cluster[i] = a1[i + 1];
						}
					}
					nsum = str_pit;
					str_pit++;
					type = 32;
				}
				else
					runout = 1;
			}
			else
				runout = 1;
		}
		else if (type == 18)        //=���� 
		{
			if ((lchild != NULL) && (rchild != NULL))       //�﷨�ж� 
			{
				type = lchild->type;
				if ((lchild->type == 32) && (lchild->type == rchild->type))            //����������ƥ�� 
				{
					//�ý���lchild������rchild��㴮���Ʋ��������ı�nsumֵΪ��Ӧ��ַ;
				}
				else if ((lchild->type == 12) && (rchild->type == 12))         //������Ϊ����ʱ����ҲΪ����
				{
					//������ֵ = rchild->nsum;
					nsum == rchild->nsum;
				}
				else if (rchild->type != 32)         //������Ϊʵ��ʱ���Ҳ���Ϊ�ַ����������������;��� 
				{
					//������ֵ = �Ҳ��Ӧֵ;
					nsum == lchild->nsum;
				}
				else
					runout = 1;
			}
			else
				runout = 1;
		}
		else if (type == 30)        //,������ֻ�̳к������ֵ 
		{
			type = rchild->type;
			nsum = rchild->nsum;
		}
		else if (type == 25)        //(�������̳к�������ֵ
		{
			type = lchild->type;
			nsum = lchild->nsum;
		}
		else if (type == 36)        //!��������ǰ����ڵ������ֵ���ƣ���Ҫȡ�� 
		{
			type = 12;          //�߼�����������Ϊint�� 
			if (lchild->type == 12)
			{
				if (lchild->nsum == 0)
					nsum = 1;
				else
					nsum = 0;
			}
			else if (lchild->type == 37)
			{
				if (integ[lchild->nsum].num_integ == 0)   //lchild->nsumλ�ö�Ӧʵ����ֵinteg
					nsum = 1;
				else
					nsum = 0;
			}
			else
			{
				runout = 1;
			}
		}
		else if ((lchild != NULL) && (rchild == NULL) && (type == 21))               //������������־���⴦��,������������������� 
		{
			if (lchild->type == 37)         //ʵ����Ӧ���ҵ���Ӧֵ���õ���ֵ���洢 
			{
				type = 37;
				lsum = real[lchild->nsum].num_real;                            //lchild->nsumλ�ö�Ӧʵ����ֵ
				nowsum = 0 - lsum;
				real[real_pit].num_real = nowsum;                                    //nowsum����ʵ������
				nsum = real_pit;                                          //nowsumʵ������λ��
				real_pit++;
			}
			else           //�������������� 
			{
				type = 12;
				nsum = 0 - lchild->nsum;
			}
		}
		else if ((lchild != NULL) && (rchild != NULL))       //�﷨�ж� 
		{
			if (((lchild->type == 12) || (lchild->type == 37)) && ((rchild->type == 12) || (rchild->type == 37)))        //ʣ������������ͺ�ʵ������˫Ŀ���� 
			{
				switch (type)
				{
				case 13:                                            //<=���� 
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                      //lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                     //rchild->nsumλ�ö�Ӧʵ����ֵ;
					else
						rsum = rchild->nsum;
					if (lsum <= rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 14:                                            //<���� 
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                  //lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                  //rchild->nsumλ�ö�Ӧʵ����ֵ;
					else
						rsum = rchild->nsum;
					if (lsum<rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 15:                                            //>=����  
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                 // lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                     //rchild->nsumλ�ö�Ӧʵ����ֵ
					else
						rsum = rchild->nsum;
					if (lsum >= rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 16:                                            //>���� 
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;            //lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;              // rchild->nsumλ�ö�Ӧʵ����ֵ
					else
						rsum = rchild->nsum;
					if (lsum>rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 17:                                            //==����  
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;              // lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;               // rchild->nsumλ�ö�Ӧʵ����ֵ
					else
						rsum = rchild->nsum;
					if (lsum == rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 19:                                            //����������  
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;                 // lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;                // rchild->nsumλ�ö�Ӧʵ����ֵ
					else
						rsum = rchild->nsum;
					if (lsum != rsum)
						nsum = 1;
					else
						nsum = 0;
					break;

				case 20:                                            //+����  
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsumλ�ö�Ӧʵ����ֵ
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;             // rchild->nsumλ�ö�Ӧʵ����ֵ
						else
							rsum = rchild->nsum;
						nowsum = lsum + rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum����ʵ������
						nsum = real_pit;                                          //nowsumʵ������λ��
						real_pit++;
					}
					else
					{
						type = 12;
						nsum = lchild->nsum + rchild->nsum;
					}
					break;

				case 21:                                            //-����
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsumλ�ö�Ӧʵ����ֵ
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;              // rchild->nsumλ�ö�Ӧʵ����ֵ
						else
							rsum = rchild->nsum;
						nowsum = lsum - rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum����ʵ������
						nsum = real_pit;                                          //nowsumʵ������λ��
						real_pit++;
					}
					else
					{
						type = 12;
						nsum = lchild->nsum - rchild->nsum;
					}
					break;

				case 22:                                            //*����
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsumλ�ö�Ӧʵ����ֵ
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;              // rchild->nsumλ�ö�Ӧʵ����ֵ
						else
							rsum = rchild->nsum;
						nowsum = lsum*rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum����ʵ������
						nsum = real_pit;                                          //nowsumʵ������λ��
						real_pit++;
					}
					else
					{
						type = 12;
						nsum = lchild->nsum*rchild->nsum;
					}
					break;

				case 23:                                            //��������
					if ((lchild->type == 37) || (rchild->type == 37))
					{
						type = 37;
						if (lchild->type == 37)
							lsum = real[lchild->nsum].num_real;              // lchild->nsumλ�ö�Ӧʵ����ֵ
						else
							lsum = lchild->nsum;
						if (rchild->type == 37)
							rsum = real[rchild->nsum].num_real;              // rchild->nsumλ�ö�Ӧʵ����ֵ
						else
							rsum = rchild->nsum;
						if (rsum == 0)              //��������Ϊ0 
						{
							runout = 1;
							return;
						}
						else
							nowsum = lsum / rsum;
						real[real_pit].num_real = nowsum;                                    //nowsum����ʵ������
						nsum = real_pit;                                          //nowsumʵ������λ��
						real_pit++;
					}
					else
					{
						type = 12;
						if (rchild->nsum == 0)
						{
							runout = 1;
							return;
						}
						else
							nsum = lchild->nsum / rchild->nsum;
					}
					break;

				case 38:                                            //������%����
					if ((lchild->type == 37) || (rchild->type == 37))              //���ܶ�ʵ������
					{
						runout = 1;
						return;
					}
					else
					{
						type = 12;
						if (rchild->nsum == 0)              //��������Ϊ0 
						{
							runout = 1;
							return;
						}
						else
							nsum = lchild->nsum%rchild->nsum;
					}
					break;

				case 42:                                            //�˷����㣨ֻ��0���������������Ժ�ָ�������Ϊ����������Ϊʵ����
					if ((lchild->type == 37) || (rchild->type == 37))              //���ܶ�ʵ������
					{
						runout = 1;
						return;
					}
					else
					{
						type = 12;
						if (rchild->nsum == 0)              //ָ��Ϊ0ʱ���� 
						{

							nsum = 1;
						}
						else if (rchild->nsum>0)
						{
							nsum = lchild->nsum;                     //���������Ϊ��������������ָ�� 
							for (int i = 1; i<rchild->nsum; i++)
							{
								nsum = nsum*lchild->nsum;
							}
						}
						else
						{
							runout = 1;
							return;
						}
					}
					break;

				case 34:                                            //&&����
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;              // lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;              // rchild->nsumλ�ö�Ӧʵ����ֵ
					else
						rsum = rchild->nsum;
					if ((lsum != 0) && (rsum != 0))
						nsum = 1;
					else
						nsum = 0;
					break;

				case 35:                                            //||����
					type = 12;
					if (lchild->type == 37)
						lsum = real[lchild->nsum].num_real;              // lchild->nsumλ�ö�Ӧʵ����ֵ
					else
						lsum = lchild->nsum;
					if (rchild->type == 37)
						rsum = real[rchild->nsum].num_real;              // rchild->nsumλ�ö�Ӧʵ����ֵ
					else
						rsum = rchild->nsum;
					if ((lsum != 0) || (rsum != 0))
						nsum = 1;
					else
						nsum = 0;
					break;

				default:runout = 1; break;
				}
			}
			else
				runout = 1;
		}
		else
			runout = 1;
	}
	if (lchild != NULL)              //���������� 
	{
		fff = lchild;
		lchild = NULL;
		delete fff;
	}
	if (rchild != NULL)              //���������� 
	{
		fff = rchild;
		rchild = NULL;
		delete fff;
	}
	return;
}

