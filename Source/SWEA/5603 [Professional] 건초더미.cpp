
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>
#include <algorithm>

#define SIZE 10001

using namespace std;

int dummy[SIZE];

bool compare(const int &n1, const int &n2)
{
	return n1 < n2;
}

void init(void)
{
	memset(dummy, 0, sizeof(dummy));
}

void input(int &n)
{
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> dummy[i];
	}
}

int getAverage(int n)
{
	int ret = 0;
	for(int i=0; i<n; i++){
		ret += dummy[i];
	}
	return ret/n;
}

int solve(int n)
{
	int ret = 0;
	sort(dummy, dummy+n, compare);
	int average = getAverage(n);
	for(int i=0; dummy[i] < average; i++){
		ret += average - dummy[i];
	}
	return ret;
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		int n;
		input(n);
		cout << "#" << tc << " " << solve(n) << '\n';
	}
	return 0;
}
