
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>

#define SIZE 21

using namespace std;

typedef struct vnode
{
	int x, y, size;
	vnode(int x, int y, int s):x(x), y(y), size(s){}
}vnode;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

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

void dfs(int x, int y, int &size, int h, int w)
{
	visited[y][x] = true;
	size++;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, h, w))	continue;
		if(!visited[ny][nx] && map[ny][nx] == 2){
			dfs(nx, ny, size, h, w);
		}
	}
}

void init(int h, int w, vector<vnode> &black)
{
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			if(visited[y][x])	continue;
			if(map[y][x] == 2){
				int size = 0;
				dfs(x, y, size, h, w);
				black.push_back(vnode(x, y, size));
			}
		}
	}
	memset(visited, 0, sizeof(visited));
}

void calXY(int &x1, int &y1, int &x2, int &y2, int p1, int p2, int h, int w)
{
	x1 = p1%w, y1 = p1/w, x2 = p2%w, y2 = p2/w;
}

void stone(int x1, int y1, int x2, int y2, int mark)
{
	map[y1][x1] = map[y2][x2] = mark;
}

bool isCanEat(int x, int y, int h, int w)
{
	if(!map[y][x])	return false;
	bool ret = true;
	visited[y][x] = true;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, h, w))	continue;
		if(!visited[ny][nx] && map[ny][nx] != 1){
			ret &= isCanEat(nx, ny, h, w);
		}
	}
	return ret;
}

int getMax(int h, int w, vector<vnode> &black)
{
	int len = black.size();
	int ret = 0;
	for(int i=0; i<len; i++){
		if(isCanEat(black[i].x, black[i].y, h, w)){
			ret += black[i].size;
		}
	}
	memset(visited, 0, sizeof(visited));
	return ret;
}

int solve(int h, int w, vector<vnode> &black)
{
	int limit = h*w;
	int ret = 0;
	for(int p1=0; p1<limit; p1++){
		for(int p2=p1+1; p2<limit; p2++){
			int x1, y1, x2, y2;
			calXY(x1, y1, x2, y2, p1, p2, h, w);
			if(map[y1][x1] || map[y2][x2])	continue;
			stone(x1, y1, x2, y2, 1);
			ret = max(ret, getMax(h, w, black));
			stone(x1, y1, x2, y2, 0);
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int h, w;
	vector<vnode> black;
	input(h, w);
	init(h, w, black);
	cout << solve(h, w, black) << '\n';
	return 0;
}

