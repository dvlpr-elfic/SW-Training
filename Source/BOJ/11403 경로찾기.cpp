
/**
  * @author Jihoon Jang
  * 18min
  */

#include <iostream>

#define SIZE 101

using namespace std;

bool graph[SIZE][SIZE];
int path[SIZE][SIZE];

void input(int &n)
{
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> graph[i][j];
		}
	}
}

void dfs(int cur, int n, int start)
{
	for(int i=0; i<n; i++){
		if(graph[cur][i] && !path[start][i]){
			path[start][i] = 1;
			dfs(i, n, start);
		}
	}
}

void solve(int n)
{
	for(int i=0; i<n; i++){
		dfs(i, n, i);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << path[i][j] << ' ';
		}
		cout << '\n';
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	input(n);
	solve(n);
	return 0;
}
