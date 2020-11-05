
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <string.h>

using namespace std;

char *table[8] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z="};
int lentable[8] = {2, 2, 3, 2, 2, 2, 2, 2};

void matching(char *p)
{
	for(int i=0; i<8; i++){
		if(!memcmp(p, table[i], lentable[i])){
			*p = 1;
			memset(p+1, 0, lentable[i]-1);
		}			
	}
}

void solve(char *str)
{
	int len = strlen(str)-1;
	for(int i=0; i<len; i++){
		matching(str+i);
	}
}


int main(void)
{
	char str[200] = {0, };
	cin >> str;
	int len = strlen(str);
	solve(str);
	int cnt = 0;
	for(int i=0; i<len; i++){
		if(str[i])
			cnt++;
	}
	cout << cnt << endl;
	return 0;
}
