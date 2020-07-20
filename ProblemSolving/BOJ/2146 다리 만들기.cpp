
/**
  * @author Jihoon Jang
  * 69 min
  */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>

#define SIZE 101
#define INF 0x3FFFFFFF

using namespace std;

typedef struct pos
{
	int x, y;
	pos(int x, int y):x(x), y(y){}
}pos;

typedef struct qnode
{
	int x, y, d;
	qnode(int x, int y, int d):x(x), y(y), d(d){}
}qnode;

int map[SIZE][SIZE];
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

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void dfs(int number, int x, int y, int n)
{
	visited[y][x] = true;
	map[y][x] = number;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, n))
			continue;
		if(!visited[ny][nx] && map[ny][nx]){
			dfs(number, nx, ny, n);
		}
	}
}

void numbering(int n, vector<pos> &island)
{
	int number = 1;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(map[y][x] && !visited[y][x]){
				dfs(number++, x, y, n);
				island.push_back(pos(x, y));
			}
		}
	}
	memset(visited, 0, sizeof(visited));
}

void setStartQueue(queue<qnode> &startq, int _x, int _y, int n, int number)
{
	queue<qnode> q;
	q.push(qnode(_x, _y, 0));
	visited[_y][_x] = true;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y;	q.pop();
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isOut(nx, ny, n))
				continue;
			if(!visited[ny][nx]){
				visited[ny][nx] = true;
				if(map[ny][nx] == number){
					q.push(qnode(nx, ny, 0));
				}
				else if(!map[ny][nx]){
					startq.push(qnode(nx, ny, 1));
				}
			}
		}
	}
}

int bridge(queue<qnode> &q, int n, int number)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, d = q.front().d;	q.pop();
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isOut(nx, ny, n))
				continue;
			if(!visited[ny][nx]){
				visited[ny][nx] = true;
				if(map[ny][nx] && map[ny][nx] != number){
					return d;
				}
				q.push(qnode(nx, ny, d+1));
			}
		}
	}
	return INF;
}

int solve(int n)
{
	vector<pos> island;
	numbering(n, island);
	int len = island.size();
	int ret = INF;
	for(int i=0; i<len; i++){
		queue<qnode> startq;
		setStartQueue(startq, island[i].x, island[i].y, n, i+1);
		ret = min(ret, bridge(startq, n, i+1));
		memset(visited, 0, sizeof(visited));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	input(n);
	cout << solve(n) << '\n';
	return 0;
}

