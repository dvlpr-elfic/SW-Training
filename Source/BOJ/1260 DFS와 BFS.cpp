
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>

#define SIZE 1001

using namespace std;

bool visited[SIZE];
bool graph[SIZE][SIZE];

void input(int &n, int &m, int &s)
{
	cin >> n >> m >> s;
	for(int i=0; i<m; i++){
		int parent, child;
		cin >> parent >> child;
		graph[parent][child] = graph[child][parent] = true;
	}
}

void print(vector<int> &list)
{
	int len = list.size();
	for(int i=0; i<len; i++){
		cout << list[i] << ' ';
	}
	cout << '\n';
}

void dfs(int n, vector<int> &list, int cur)
{
	for(int i=1; i<=n; i++){
		if(graph[cur][i] && !visited[i]){
			visited[i] = true;
			list.push_back(i);
			dfs(n, list, i);
		}
	}
}

void bfs(int s, int n, vector<int> &list)
{
	queue<int> q;
	q.push(s);
	visited[s] = true;
	list.push_back(s);
	while(!q.empty()){
		int cur = q.front();	q.pop();
		for(int i=1; i<=n; i++){
			if(graph[cur][i] && !visited[i]){
				visited[i] = true;
				list.push_back(i);
				q.push(i);
			}
		}
	}
	print(list);
}

void solve(int s, int n)
{
	vector<int> list;
	list.push_back(s);
	visited[s] = true;
	dfs(n, list, s);
	print(list);
	list.clear();
	memset(visited, 0, sizeof(visited));
	bfs(s, n, list);
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n, m, s;
	input(n, m, s);
	solve(s, n);
	return 0;
}

