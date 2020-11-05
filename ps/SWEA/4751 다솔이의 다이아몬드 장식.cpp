
#include <stdio.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 100
#define LINES 5

using namespace std;

void SetStr(char*, int, char**, int);
void SetSharpDot(char**, int);
void print(char**);

int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++){
		char str[MAX_CHAR_PER_LINE] ={0, };
		char** table = new char*[LINES];
		scanf("%s", str);
		int len = strlen(str);
		int table_len = len*4+1;				/* 테이블 길이 설정 */
		for(int i=0; i<LINES; i++){
			table[i] = new char[table_len+1];
			table[i][table_len] = 0;
		}
		SetSharpDot(table, table_len);
		SetStr(str, len, table, table_len);
		print(table);
		
	}

	return 0;
}

void SetStr(char* str, int str_len, char** table, int table_len)
{
	int index = 0;
	for(int i=2; i<table_len; i+=4){
		table[2][i] = str[index++];
	}
	for(int i=0; i<table_len; i+=4)
		table[2][i] = '#';
	for(int i=1; i<table_len; i+=2)
		table[2][i] = '.';
}

void SetSharpDot(char** table, int table_len)
{
	for(int i=0; i<table_len; i++){
		if((i-2)%4 == 0)
			table[0][i] = table[4][i] = '#';
		else
			table[0][i] = table[4][i] = '.';
		if(i%2)
			table[1][i] = table[3][i] = '#';
		else
			table[1][i] = table[3][i] = '.';
	}
}

void print(char** table)
{
	for(int i=0; i<LINES; i++){
		printf("%s\n", table[i]);
	}
}
