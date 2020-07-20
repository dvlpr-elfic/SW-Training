
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define SIZE 10

using namespace std;

void input(int &n, int &m)
{
	cin >> n >> m;
}

void print(int *list, int m)
{
	for(int i=0; i<m; i++){
		cout << list[i] << ' ';
	}
	cout << '\n';
}

void solve(int depth, int n, int m, int *list, bool *picked)
{
	if(depth == m){
		print(list, m);
		return;
	}
	for(int cur=1; cur<=n; cur++){
		if(!picked[cur]){
			picked[cur] = true;
			list[depth] = cur;
			solve(depth+1, n, m, list, picked);
			picked[cur] = false;
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);

	int n, m;
	input(n, m);
	int list[SIZE] = {0, };
	bool picked[SIZE] = {0, };
	solve(0, n, m, list, picked);

	return 0;
}

