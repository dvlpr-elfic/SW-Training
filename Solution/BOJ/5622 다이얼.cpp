
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <string.h>

using namespace std;

const int offset = 1;

int atod[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

void input(char *str)
{
	cin >> str;
}

int solve(char* str)
{
	int len = strlen(str);
	int ret = 0;
	for(int i=0; i<len; i++){
		ret += atod[str[i]-'A'] + offset;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	char str[20];
	input(str);
	cout << solve(str) << '\n';
	return 0;
}
