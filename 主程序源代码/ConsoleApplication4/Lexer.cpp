#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Lexer.h"


int str_pit = 0;         //串组行号
int real_pit = 0;        //实型数行号
int integ_pit = 0;        //整型数行号

void lexer() {
	char *reserved_word[13] = { "int","real","string","while","if","else","out","in","main","void", "return", "do", "until" };    //保留字名单
	int p = 0;                //mini代码当前扫描位置 
	int m = 0, n, t;                  //计数变量
								   //单词种别码 , 单词种别通常用整数编码。标识符一般统归为一种。
								   //常数则宜按类型（整、实、字符等）分种。关键字可将其全体视为一种。
								   //运算符可采用一符一种的方法。界符一般用一符一种的方法。
								   //对于每个单词符号，除了给出了种别编码之外，还应给出有关单词符号的属性信息。
								   //单词符号的属性是指单词符号的特性或特征。
	int sum = 0;               //整数常型
	int pit = 0;             //三元组当前行号
	int line_number = 1;     //记录源代码行号
	char real_save[40];      //临时存储串


	while (sentence[p] != EOF) {

		char ch;            //mini代码当前扫描位置的内容
		ch = sentence[p];
		p++;

		if (ch== '/'&&sentence[p] == '/') {        //跳过注释
			while (sentence[p] != '\n')
				p++;
			p++;
			continue;
		}

		if (ch == ' ' || ch == '	') {      //跳过空格和tab
			continue;
		}

		if (ch == '"') {                         //当遇到串
			list[pit].name = 29;
			list[pit].line = line_number;
			list[pit].token[0] = ch;
			pit++;
			ch = sentence[p];
			p++;
			n = 0;
			while (ch != '"') {                 //提取出引号中的全部，存入str类数组
				if (ch == '\\') {               //遇到转义符，将转义符变为字符
					ch = sentence[p];
					p++;
					switch (ch) {
					case'a':str[str_pit].cluster[n] = '\a'; n++; break;
					case'b':str[str_pit].cluster[n] = '\b'; n++; break;
					case'c':str[str_pit].cluster[n] = 'c'; n++; break;
					case'd':str[str_pit].cluster[n] = 'd'; n++; break;
					case'e':str[str_pit].cluster[n] = 'e'; n++; break;
					case'f':str[str_pit].cluster[n] = '\f'; n++; break;
					case'g':str[str_pit].cluster[n] = 'g'; n++; break;
					case'h':str[str_pit].cluster[n] = 'h'; n++; break;
					case'i':str[str_pit].cluster[n] = 'i'; n++; break;
					case'j':str[str_pit].cluster[n] = 'j'; n++; break;
					case'k':str[str_pit].cluster[n] = 'k'; n++; break;
					case'l':str[str_pit].cluster[n] = 'l'; n++; break;
					case'm':str[str_pit].cluster[n] = 'm'; n++; break;
					case'n':str[str_pit].cluster[n] = '\n'; n++; break;
					case'o':str[str_pit].cluster[n] = 'o'; n++; break;
					case'p':str[str_pit].cluster[n] = 'p'; n++; break;
					case'q':str[str_pit].cluster[n] = 'q'; n++; break;
					case'r':str[str_pit].cluster[n] = '\r'; n++; break;
					case's':str[str_pit].cluster[n] = 's'; n++; break;
					case't':str[str_pit].cluster[n] = '\t'; n++; break;
					case'u':str[str_pit].cluster[n] = '\000'; n++; break;
					case'v':str[str_pit].cluster[n] = '\v'; n++; break;
					case'w':str[str_pit].cluster[n] = 'w'; n++; break;
					case'x':str[str_pit].cluster[n] = 'x'; n++; break;
					case'y':str[str_pit].cluster[n] = 'y'; n++; break;
					case'z':str[str_pit].cluster[n] = 'z'; n++; break;
					case'A':str[str_pit].cluster[n] = 'A'; n++; break;
					case'B':str[str_pit].cluster[n] = 'B'; n++; break;
					case'C':str[str_pit].cluster[n] = 'C'; n++; break;
					case'D':str[str_pit].cluster[n] = 'D'; n++; break;
					case'E':str[str_pit].cluster[n] = 'E'; n++; break;
					case'F':str[str_pit].cluster[n] = 'F'; n++; break;
					case'G':str[str_pit].cluster[n] = 'G'; n++; break;
					case'H':str[str_pit].cluster[n] = 'H'; n++; break;
					case'I':str[str_pit].cluster[n] = 'I'; n++; break;
					case'J':str[str_pit].cluster[n] = 'J'; n++; break;
					case'K':str[str_pit].cluster[n] = 'K'; n++; break;
					case'L':str[str_pit].cluster[n] = 'L'; n++; break;
					case'M':str[str_pit].cluster[n] = 'M'; n++; break;
					case'N':str[str_pit].cluster[n] = 'N'; n++; break;
					case'O':str[str_pit].cluster[n] = 'O'; n++; break;
					case'P':str[str_pit].cluster[n] = 'P'; n++; break;
					case'Q':str[str_pit].cluster[n] = 'Q'; n++; break;
					case'R':str[str_pit].cluster[n] = 'R'; n++; break;
					case'S':str[str_pit].cluster[n] = 'S'; n++; break;
					case'T':str[str_pit].cluster[n] = 'T'; n++; break;
					case'U':str[str_pit].cluster[n] = '\000'; n++; break;
					case'V':str[str_pit].cluster[n] = 'V'; n++; break;
					case'W':str[str_pit].cluster[n] = 'W'; n++; break;
					case'X':str[str_pit].cluster[n] = 'X'; n++; break;
					case'Y':str[str_pit].cluster[n] = 'Y'; n++; break;
					case'Z':str[str_pit].cluster[n] = 'Z'; n++; break;
					case'0':str[str_pit].cluster[n] = '\0'; n++; break;
					case'\\':str[str_pit].cluster[n] = '\\'; n++; break;
					case'"':str[str_pit].cluster[n] = '\"'; n++; break;
					}
				}
				else {
					str[str_pit].cluster[n] = ch;
					n++;
				}
				ch = sentence[p];
				p++;
			}
			list[pit].name = 32;
			list[pit].line = line_number;
			list[pit].token[0] = str_pit + '0';   //int转char..+'0'
			str_pit++;
			pit++;
			list[pit].name = 29;
			list[pit].line = line_number;
			list[pit].token[0] = ch;
			pit++;
			continue;
		}

		if (ch == '\n') {                    //遇到换行符。换行
			line_number++;
			continue;
		}


		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')) {           //标志符或变量名的起始判定
			m = 0;
			while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9')) {        //标志符的记录(含有char常量值、变量名） 
				list[pit].token[m] = ch;
				m++;
				ch = sentence[p];
				p++;
			}
			list[pit].token[m] = NULL;              //标志符的结束判定
			m++;
			p--;
			list[pit].name = 1;
			list[pit].line = line_number;

			for (n = 0; n < 10; n++) {
				if (strcmp(list[pit].token, reserved_word[n]) == 0) {      //判断是否为保留字
					list[pit].name = n + 2;
					break;
				}
			}

			for (n = 10; n < 13; n++) {
				if (strcmp(list[pit].token, reserved_word[n]) == 0) {      //判断是否为保留字
					list[pit].name = n + 29;
					break;
				}
			}
			pit++;
		}

		else if ((ch >= '0'&&ch <= '9')) {           //数字判定（这里似乎只有整型或实型的整数部分好判断） 
			sum = 0;
			while (ch >= '0'&&ch <= '9'&&sum<8) {   //整型数
				list[pit].token[sum] = ch;
				sum++;
				ch = sentence[p];
				p++;
			}
			p--;


			if (sum < 8 && sentence[p] != '.') {       //判断是否整型数
				integ[integ_pit].num_integ = 0;
				for (m = 0; m < sum; m++) {
					integ[integ_pit].num_integ = integ[integ_pit].num_integ * 10 + list[pit].token[m] - '0';  //整型转int
				}
				list[pit].token[0] = integ_pit + '0';     //int转char..+'0'
				list[pit].line = line_number;
				list[pit].name = 12;
				pit++;
				integ_pit++;
			}
			if ((sentence[p] >= '0'&&sentence[p] <= '9') || sentence[p] == '.') {         //实型数
				for (m = 0; m < sum; m++)
					real_save[m] = list[pit].token[m];
				while ((sentence[p] >= '0'&&sentence[p] <= '9') || sentence[p] == '.') {
					real_save[m] = (char)sentence[p];
					p++;
					m++;
				}
				real_save[m] = '\0';
				for (t = 0; real_save[t] != '.';)
					t++;
				real[real_pit].num_real = 0;
				for (n = 0; n < m; n++){
					if(real_save[n]!='.')
					    real[real_pit].num_real = real[real_pit].num_real * 10 + real_save[n] - '0';        //实型转double
				}
				t = m - t - 1;
				for (n = 0; n < t; n++)
					real[real_pit].num_real = real[real_pit].num_real / 10;
				list[pit].token[0] = real_pit + '0';         //int转char..+'0'
				list[pit].name = 37;
				list[pit].line = line_number;
				pit++;
				real_pit++;
			}
		}

		else switch (ch) {             //其他字符
		case'<':m = 0;
			list[pit].token[m++] = ch;
			ch = sentence[p++];
			if (ch == '>') {                      //<>
				list[pit].name = 19;
				list[pit].token[m++] = ch;
				list[pit].line = line_number;
				pit++;
			}
			else if (ch == '=') {                  //<=
				list[pit].name = 13;
				list[pit].token[m++] = ch;
				list[pit].line = line_number;
				pit++;
			}
			else {                             //<
				list[pit].name = 14;
				list[pit].line = line_number;
				pit++;
				p--;
			}
			break;
		case'>':m = 0;
			list[pit].token[m++] = ch;
			ch = sentence[p++];
			if (ch == '=') {                   //>=
				list[pit].name = 15;
				list[pit].token[m++] = ch;
				list[pit].line = line_number;
				pit++;
			}
			else {                             //>
				list[pit].name = 16;
				list[pit].line = line_number;
				pit++;
				p--;
			}
			break;
		case'=':m = 0;
			list[pit].token[m++] = ch;
			ch = sentence[p++];
			if (ch == '=') {                   //==
				list[pit].name = 17;
				list[pit].token[m++] = ch;
				list[pit].line = line_number;
				pit++;
			}
			else {                             //=
				list[pit].name = 18;
				list[pit].line = line_number;
				pit++;
				p--;
			}
			break;
		case'+':list[pit].name = 20; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'-':list[pit].name = 21; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'*':list[pit].name = 22; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'/':list[pit].name = 23; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'^':list[pit].name = 42; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'$':list[pit].name = 24; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'(':list[pit].name = 25; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case')':list[pit].name = 26; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'{':list[pit].name = 27; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'}':list[pit].name = 28; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'"':list[pit].name = 29; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;            //还有部分符号没写
		case',':list[pit].name = 30; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case';':list[pit].name = 31; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'#':list[pit].name = 33; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'%':list[pit].name = 38; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		case'&':list[pit].name = 34; list[pit].token[0] = ch; list[pit].token[1] = ch; p++; list[pit].line = line_number; pit++; break;
		case'|':list[pit].name = 35; list[pit].token[0] = ch; list[pit].token[1] = ch; p++; list[pit].line = line_number; pit++; break;
		case'!':list[pit].name = 36; list[pit].token[0] = ch; list[pit].line = line_number; pit++; break;
		default: list[pit].name = -1; break;                     //报错 
		}

	}
}


