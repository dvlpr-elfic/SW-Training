
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <string.h>

using namespace std;

bool isO(char ch)
{
	return (ch == 'O');
}


int findO(char *str, int p)
{
	int cnt = 0;
	for(int i=p; i>=0 && isO(str[i]); i--){
		cnt++;
	}
	return cnt;
}

int solve(char *str)
{
	int len = strlen(str);
	int ret = 0;
	for(int i=0; i<len; i++){
		ret += findO(str, i);
	}
	return ret;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		char str[100] = {0, };
		cin >> str;
		int ans = solve(str);
		cout << ans << endl;
	}
	return 0;
}
