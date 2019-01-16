
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 1001

using namespace std;

int building[SIZE];

void input(int &n)
{
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> building[i];
	}
}

int selectHighest(int cur)
{
	int limit = cur + 2;
	int ret = 0;
	for(int i=cur-2; i<=limit; i++){
		if(cur == i)
			continue;
		if(ret < building[i])
			ret = building[i];
	}
	return ret;
}

int solve(int n)
{
	int limit = n - 2;
	int ret = 0;
	for(int cur=2; cur<limit; cur++){
		int s = selectHighest(cur);
		if(building[cur] > s)
			ret += (building[cur] - s);
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t=10;
	for(int tc=1; tc<=t; tc++){
		int n;
		input(n);
		cout << "#" << tc << " " << solve(n) << '\n';
	}
	return 0;
}
