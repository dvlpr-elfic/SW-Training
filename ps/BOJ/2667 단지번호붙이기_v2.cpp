
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <algorithm>

#define SIZE 30

using namespace std;

bool visited[SIZE][SIZE];
int map[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

bool compare(const int &n1, const int &n2)
{
	return (n1 < n2);
}

void input(int &n)
{
	cin >> n;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			char ch;
			cin >> ch;
			map[y][x] = ch-'0';
		}
	}
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

int dfs(int x, int y, int n)
{
	visited[y][x] = true;
	if(!map[y][x])
		return 0;
	int ret = 1;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n))
			continue;
		if(!visited[ny][nx])
			ret += dfs(nx, ny, n);
	}
	return ret;
}

int solve(int n, vector<int> &v)
{
	int ret = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(visited[y][x] || !map[y][x])
				continue;
			v.push_back(dfs(x, y, n));
			ret++;
		}
	}
	return ret;
}

void print(int n)
{
	vector<int> v;
	cout << solve(n, v) << '\n';
	sort(v.begin(), v.end(), compare);
	int len = v.size();
	for(int i=0; i<len; i++){
		cout << v[i] << '\n';
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n;
	input(n);
	print(n);
	return 0;
}

