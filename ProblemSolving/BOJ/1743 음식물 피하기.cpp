
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 101

using namespace std;

bool visited[SIZE][SIZE];
int map[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n, int &m, int &k)
{
	cin >> n >> m >> k;
	for(int i=0; i<k; i++){
		int x, y;
		cin >> y >> x;
		map[y-1][x-1] = 1;
	}
}

bool isWall(int x, int y, int n, int m)
{
	return (x<0 || y<0 || x>=m || y>=n);
}

int dfs(int x, int y, int n, int m)
{
	visited[y][x] = true;
	if(!map[y][x])
		return 0;
	int ret = 1;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n, m))	continue;
		if(!visited[ny][nx])
			ret += dfs(nx, ny, n, m);
	}
	return ret;
}

int solve(int n, int m)
{
	int ret = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<m; x++){
			if(visited[y][x] || !map[y][x])
				continue;
			ret = max(ret, dfs(x, y, n, m));
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n, m, k;
	input(n, m, k);
	cout << solve(n, m) << '\n';
	return 0;
}

