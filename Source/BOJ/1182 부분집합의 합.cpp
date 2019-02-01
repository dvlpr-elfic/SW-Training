
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 21

using namespace std;

int arr[SIZE];
bool picked[SIZE];

void input(int &n, int &s)
{
	cin >> n >> s;
	for(int i=0; i<n; i++){
		cin >> arr[i];
	}
}

int subset(int depth, int start, int n, int r, int sum, int s)
{
	if(depth == r){
		// base case
		if(sum == s){
			return 1;
		}
		else
			return 0;
	}
	int ret = 0;
	int limit = n-r+depth;
	for(int i=start; i<=limit; i++){
		if(!picked[i]){
			picked[i] = true;
			ret += subset(depth+1, i+1, n, r, sum+arr[i], s);
			picked[i] = false;
		}
	}
	return ret;
}

int solve(int n, int s)
{
	int ret = 0;
	for(int i=1; i<=n; i++){
		ret += subset(0, 0, n, i, 0, s);
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, s;
	input(n, s);
	cout << solve(n, s) << endl;
	return 0;
}

