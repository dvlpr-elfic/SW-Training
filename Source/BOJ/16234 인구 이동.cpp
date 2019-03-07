
/**
  * @author Jihoon Jang
  * 48 min
  */

#include <iostream>
#include <algorithm>
#include <memory.h>
#include <queue>

#define SIZE 51

using namespace std;

typedef struct qnode
{
	int x, y;
	qnode(int x, int y):x(x), y(y){}
}qnode;

int map[SIZE][SIZE];
bool block[SIZE][SIZE][SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n, int &low, int &high)
{
	cin >> n >> low >> high;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> map[y][x];
		}
	}
}

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void blocking(int n, int low, int high)
{
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			for(int i=0; i<4; i++){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if(isOut(nx, ny, n))	continue;
				int diff = abs(map[y][x] - map[ny][nx]);
				if(diff > high || diff < low){
					block[y][x][ny][nx] = true;
				}
			}
		}
	}
}

void dfs(int &cnt, int &val, int n, int x, int y, queue<qnode> &q)
{
	visited[y][x] = true;
	cnt++;
	val += map[y][x];
	q.push(qnode(x, y));
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, n))	continue;
		if(!visited[ny][nx] && !block[y][x][ny][nx]){
			dfs(cnt, val, n, nx, ny, q);
		}
	}
}

bool changeValue(queue<qnode> &q, int val)
{
	bool ret = false;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y;	q.pop();
		if(!ret && map[y][x] != val){
			ret = true;
		}
		map[y][x] = val;
	}
	return ret;
}

bool simulation(int n)
{
	bool ret = false;
	queue<qnode> q;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(visited[y][x])	continue;
			int cnt = 0, val = 0;
			dfs(cnt, val, n, x, y, q);
			val /= cnt;
			ret |= changeValue(q, val);
		}
	}
	memset(visited, 0, sizeof(visited));
	return ret;
}

int solve(int n, int low, int high)
{
	int ret = 0;
	bool flag = true;
	while(flag){
		ret++;
		memset(block, 0, sizeof(block));
		blocking(n, low, high);
		flag = simulation(n);
	}
	return (ret-1);
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n, low, high;
	input(n, low, high);
	cout << solve(n, low, high) << '\n';
	return 0;
}

