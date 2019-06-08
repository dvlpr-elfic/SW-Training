
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define abs(a) ((a>=0)?(a):(-a))
#define INF 987654321
#define SIZE 101

using namespace std;

void input(char *a, char *b)
{
	cin >> a >> b;
}

int strlenn(char *str)
{
	int ret = 0;
	for(int i=0; str[i]; i++){
		ret++;
	}
	return ret;
}

int strdiff(char *str1, char *str2)
{
	int ret = 0;
	for(int i=0; str1[i] && str2[i]; i++){
		if(str1[i] != str2[i])
			ret++;
	}
	return ret;
}

int minn(int n1, int n2)
{
	if(n1 > n2)
		return n2;
	else
		return n1;
}

int strlendiff(char *str1, char* str2)
{
	int len1 = strlenn(str1), len2 = strlenn(str2);
	return abs((len1-len2));
}

int solve(char *a, char *b)
{
	int ret = INF;
	int len = strlendiff(a, b);
	for(int i=0; i<=len; i++){
		ret = minn(ret, strdiff(a, b+i));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	char a[SIZE];
	char b[SIZE];
	input(a, b);
	cout << solve(a, b) << '\n';
	return 0;
}

