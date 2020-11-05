
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <algorithm>

#define SIZE 101

using namespace std;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

bool cmp(const int &n1, const int &n2)
{
	return (n1<n2);
}

bool isWall(int x, int y, int n, int m)
{
	return (x<0 || y<0 || x>=m || y>=n);
}

void input(int &n, int &m)
{
	int k;
	cin >> n >> m >> k;
	for(int i=0; i<k; i++){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		for(int y=y1; y<y2; y++){
			for(int x=x1; x<x2; x++){
				map[y][x] = 1;
			}
		}
	}
}

int dfs(int x, int y, int n, int m)
{
	visited[y][x] = true;
	if(map[y][x])
		return 0;
	int ret = 1;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n, m))
			continue;
		if(!visited[ny][nx])
			ret += dfs(nx, ny, n, m);
	}
	return ret;
}

void travel(vector<int> &v, int n, int m)
{
	for(int y=0; y<n; y++){
		for(int x=0; x<m; x++){
			if(visited[y][x] || map[y][x])
				continue;
			v.push_back(dfs(x, y, n, m));
		}
	}
}

void solve(int n, int m)
{
	vector<int> v;
	travel(v, n, m);
	sort(v.begin(), v.end(), cmp);
	cout << v.size() << '\n';
	for(int i=0; i<v.size(); i++){
		cout << v[i] << ' ';
	}
	cout << '\n';
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n, m;
	input(n, m);
	solve(n, m);
	return 0;
}

