
/**
  * @author Jihoon Jang
  * 25 min
  */

#include <iostream>
#include <memory.h>

#define SIZE 51

using namespace std;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void init(void)
{
	memset(map, 0, sizeof(map));
	memset(visited, 0, sizeof(visited));
}

void input(int &n, int &m, int &k)
{
	cin >> m >> n >> k;
	for(int i=0; i<k; i++){
		int x, y;
		cin >> x >> y;
		map[y][x] = 1;
	}
}

bool isWall(int x, int y, int n, int m)
{
	return (x<0 || y<0 || x>=m || y>=n);
}

void dfs(int x, int y, int n, int m)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n, m))
			continue;
		if(!visited[ny][nx] && map[ny][nx]){
			visited[ny][nx] = true;
			dfs(nx, ny, n, m);
		}
	}
}

int solve(int n, int m)
{
	int ret = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<m; x++){
			if(map[y][x] && !visited[y][x]){
				visited[y][x] = true;
				dfs(x, y, n, m);
				ret++;
			}
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
		init();
		int n, m, k;
		input(n, m, k);
		cout << solve(n, m) << '\n';
	}
	return 0;
}
