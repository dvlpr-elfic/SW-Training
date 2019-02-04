
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 100001

using namespace std;

int graph[SIZE];
bool visited[SIZE];
bool finished[SIZE];

void input(int &n)
{
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> graph[i];
		visited[i] = finished[i] = false;
	}
}

int dfs(int n, int cur)
{
	int ret = 0;
	visited[cur] = true;
	int next = graph[cur];
	if(!visited[next]){
		ret += dfs(n, next);
	}
	else{
		if(!finished[next]){
			ret++;
			for(int v=next; v != cur; v = graph[v]){
				ret++;
			}
		}
	}
	finished[cur] = true;
	return ret;
}

int solve(int n)
{
	int ret = 0;
	for(int v=1; v<=n; v++){
		if(!visited[v]){
			ret += dfs(n, v);
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n;
		input(n);
		cout << n - solve(n) << '\n';
	}
	return 0;
}

