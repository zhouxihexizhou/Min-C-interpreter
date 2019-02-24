#define _CRT_SECURE_NO_WARNINGS
#include"Lexer.h"

void read() {
	int read = 0;
	char ch;
	FILE *fp;
	fp = fopen("test.txt", "r");
	while ((ch = fgetc(fp)) != EOF) {       // 从文件读一字符
		sentence[read] = ch;
		read++;
	}
	fclose(fp);
	sentence[read] = EOF;
}