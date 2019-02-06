
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <algorithm>

using namespace std;

int arr[4][2];

void input(int &cur)
{
	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			cin >> arr[i][j];
		}
	}
	cur = 0;
}

int getCount(int &cur, int i)
{
	cur = cur - arr[i][0] + arr[i][1];
	return cur;
}

int solve(int &cur)
{
	int ret = 0;
	for(int i=0; i<4; i++){
		ret = max(ret, getCount(cur, i));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int cur;
	input(cur);
	cout << solve(cur) << endl;
	return 0;
}

