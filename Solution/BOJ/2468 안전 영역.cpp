
/**
  * @author Jihoon Jang
  * 27min
  */

#include <iostream>
#include <memory.h>
#include <algorithm>

#define SIZE 101
#define INF 0x7FFFFFFF

using namespace std;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n, int &low, int &high)
{
	cin >> n;
	low = INF, high = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> map[y][x];
			if(low > map[y][x])
				low = map[y][x];
			if(high < map[y][x])
				high = map[y][x];
		}
	}
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void dfs(int x, int y, int n)
{
	visited[y][x] = true;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n))
			continue;
		if(!visited[ny][nx] && map[ny][nx]){
			dfs(nx, ny, n);
		}
	}
}

int counting(int n)
{
	int ret = 0;
	memset(visited, 0, sizeof(visited));
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(map[y][x] && !visited[y][x]){
				dfs(x, y, n);
				ret++;
			}
		}
	}
	return ret;
}

void setArea(int n, int h)
{
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(map[y][x] && map[y][x] <= h){
				map[y][x] = 0;
			}
		}
	}
}

int solve(int n, int low, int high)
{
	int ret = counting(n);
	for(int h=low; h<=high; h++){
		setArea(n, h);
		ret = max(ret, counting(n));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, low, high;
	input(n, low, high);
	cout << solve(n, low, high) << '\n';
	return 0;
}

