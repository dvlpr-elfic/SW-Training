
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <algorithm>

#define SIZE 501

using namespace std;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

void input(int &h, int &w)
{
	cin >> h >> w;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			cin >> map[y][x];
		}
	}
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

int dfs(int depth, int sum, int x, int y, int h, int w)
{
	if(depth == 3){
		// base case
		return sum;
	}
	int ret = 0;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, h, w))	continue;
		if(visited[ny][nx])	continue;
		visited[ny][nx] = true;
		ret = max(ret, dfs(depth+1, sum+map[ny][nx], nx, ny, h, w));
		visited[ny][nx] = false;
	}
	return ret;
}

int _exception(int x, int y, int h, int w)
{
	int ret = 0;
	for(int dir=0; dir<4; dir++){
		int cur = map[y][x];
		for(int delta=0; delta<3; delta++){
			int ndir = (dir+delta)%4;
			int nx = x + dx[ndir];
			int ny = y + dy[ndir];
			if(isOut(nx, ny, h, w)){
				cur = 0;
				break;
			}
			cur += map[ny][nx];
		}
		ret = max(ret, cur);
	}
	return ret;
}

int solve(int h, int w)
{
	int ret = 0;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			visited[y][x] = true;
			ret = max(ret, dfs(0, map[y][x], x, y, h, w));
			ret = max(ret, _exception(x, y, h, w));
			visited[y][x] = false;
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int h, w;
	input(h, w);
	cout << solve(h, w) << endl;
	return 0;
}

