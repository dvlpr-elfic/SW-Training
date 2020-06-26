
/**
  * @author Jihoon Jang
  * 20min
  */

#include <iostream>
#include <memory.h>

#define SIZE 101

using namespace std;

char map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n)
{
	cin >> n;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> map[y][x];
		}
	}
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void dfs(char color, int x, int y, int n)
{
	if(map[y][x] != color)
		return;
	visited[y][x] = true;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n))
			continue;
		if(!visited[ny][nx])
			dfs(color, nx, ny, n);
	}
}

int travel(int n)
{
	int ret = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(visited[y][x])
				continue;
			dfs(map[y][x], x, y, n);
			ret++;
		}
	}
	return ret;
}

void transform(int n)
{
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(map[y][x] == 'G')
				map[y][x] = 'R';
		}
	}
}

void solve(int n)
{
	cout << travel(n) << ' ';
	transform(n);
	memset(visited, 0, sizeof(visited));
	cout << travel(n) << '\n';
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n;
	input(n);
	solve(n);
	return 0;
}
