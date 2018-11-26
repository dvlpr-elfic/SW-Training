
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int cnt;
bool visited[101];

void init(void){
	cnt = 0;
	memset(visited, 0, sizeof(visited));
}


void input(int &n, int &e, vector<int> *graph){
	cin >> n >> e;
	for(int i=0; i<e; i++){
		int s, a;
		cin >> s >> a;
		graph[s].push_back(a);
		graph[a].push_back(s);
	}
}

void dfs(int cur, vector<int> *graph){
	// base case is not exist
	int len = graph[cur].size();
	for(int i=0; i<len; i++){
		int next = graph[cur][i];
		if(!visited[next]){
			visited[next] = true;
			cnt++;
			dfs(next, graph);
		}
	}
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	init();
	//freopen("input.txt", "r", stdin);
	int n, e;
	vector<int> graph[101];
	input(n, e, graph);
	visited[1] = true;
	dfs(1, graph);
	cout << cnt << endl;
	return 0;
}
