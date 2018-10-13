

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#define MAX_STR 1000

using namespace std;

int compare(const void* arg1, const void* arg2)
{
	char* a = (char*)arg1;
	char* b = (char*)arg2;
	return strcmp(a, b);
}

int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++){
		char str[MAX_STR][MAX_STR] = {0, };
		int n;
		scanf("%d", &n);
		scanf("%s", str[0]);
		int len = strlen(str[0]);
		for(int i=1; i<len; i++){
			strcpy(str[i], &str[0][i]);
		}
		qsort(str, len, sizeof(str[0]), compare);
		printf("#%d %s\n", tc, str[n-1]);
	}

	return 0;
}
