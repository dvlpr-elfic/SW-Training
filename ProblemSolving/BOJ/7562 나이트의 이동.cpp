
/**
  * @author Jihoon Jang
  * 20min
  */

#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 301

using namespace std;

typedef struct pos
{
	int x, y;
}pos;

typedef struct qnode
{
	int x, y, d;
	qnode(int x, int y, int d):x(x), y(y), d(d){}
}qnode;

bool visited[SIZE][SIZE];
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

void init(void)
{
	memset(visited, 0, sizeof(visited));
}

void input(int &n, pos& start, pos& arrive)
{
	cin >> n >> start.x >> start.y >> arrive.x >> arrive.y;
}

bool isArrive(pos& arrive, int x, int y)
{
	return (arrive.x == x && arrive.y == y);
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

int bfs(pos& start, pos& arrive, int n)
{
	int ret = -1;
	visited[start.y][start.x] = true;
	queue<qnode> q;
	q.push(qnode(start.x, start.y, 0));
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, d = q.front().d;	q.pop();
		if(isArrive(arrive, x, y)){
			ret = d;
			break;
		}
		for(int i=0; i<8; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isWall(nx, ny, n))
				continue;
			if(!visited[ny][nx]){
				visited[ny][nx] = true;
				q.push(qnode(nx, ny, d+1));
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
		pos start, arrive;
		int n;
		input(n, start, arrive);
		cout << bfs(start, arrive, n) << '\n';
	}
	return 0;
}

