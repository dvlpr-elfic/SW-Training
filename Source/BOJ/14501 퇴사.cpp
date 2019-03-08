
/**
  * @author Jihoon Jang
  * 44 min
  */

#include <iostream>
#include <algorithm>

#define SIZE 16

using namespace std;

typedef struct tnode
{
	int t, p;
}tnode;

tnode table[SIZE];

void input(int &n)
{
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> table[i].t >> table[i].p;
	}
}

bool isCanComplete(int i, int n)
{
	return ((i+table[i].t-1) <= n);
}

void initTable(int &n)
{
	for(int i=n; i>=0; i--){
		if(!isCanComplete(i, n))
			table[i].p = 0;
	}
}

void picking(int s, int n, int price, int &maxx)
{
	if(s > n){
		// base case
		maxx = max(maxx, price);
		return;
	}
	for(int i=s; i<=n; i++){
		int next = table[i].t + i;
		picking(next, n, price+table[i].p, maxx);
	}
}

int solve(int n)
{
	initTable(n);
	int ret = 0;
	picking(1, n, 0, ret);
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	input(n);
	cout << solve(n) << endl;
	return 0;
}

