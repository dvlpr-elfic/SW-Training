
/**
  * @author Jihoon Jang
  * 15min
  */

#include <iostream>
#include <vector>

#define SIZE 1000

using namespace std;

bool visited[SIZE];

void input(vector<vector<int>> &v, int &n, int &m)
{
	cin >> n >> m;
	v.resize(n+1);
	for(int i=0; i<m; i++){
		int parent, child;
		cin >> parent >> child;
		v[parent].push_back(child);
		v[child].push_back(parent);
	}
}

void dfs(int parent, vector<vector<int>> &v)
{
	int len = v[parent].size();
	for(int i=0; i<len; i++){
		int next = v[parent][i];
		if(!visited[next]){
			visited[next] = true;
			dfs(next, v);
		}
	}
}

int solve(vector<vector<int>> &v, int n)
{
	int ret = 0;
	for(int i=1; i<=n; i++){
		if(visited[i])
			continue;
		visited[i] = true;
		dfs(i, v);
		ret++;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, m;
	vector<vector<int>> v;
	input(v, n, m);
	cout << solve(v, n) << '\n';
	return 0;
}

