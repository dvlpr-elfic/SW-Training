
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>

#define SIZE 1001

using namespace std;

typedef struct qnode
{
	int x, y, level;
	qnode(int x, int y, int l):x(x), y(y), level(l){}
}qnode;

int map[SIZE][SIZE];
int damage[SIZE][SIZE];
bool crashed[SIZE][SIZE];
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void input(int &h, int &w)
{
	cin >> h >> w;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			char ch;
			cin >> ch;
			if(ch == '.')
				continue;
			map[y][x] = ch - '0';
		}
	}
}

bool isCrash(int x, int y)
{
	return (damage[y][x] >= map[y][x] && !crashed[y][x]);
}

int bfs(queue<qnode> &q)
{
	int ret = 0;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, level = q.front().level;	q.pop();
		map[y][x] = 0;
		ret = level;
		for(int i=0; i<8; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(map[ny][nx]){
				damage[ny][nx]++;
				if(isCrash(nx, ny)){
					crashed[ny][nx] = true;
					q.push(qnode(nx, ny, level+1));
				}
			}
		}
	}
	return ret;
}

void setQueue(int h, int w, queue<qnode> &q)
{
	h--, w--;
	for(int y=1; y<h; y++){
		for(int x=1; x<w; x++){
			if(!map[y][x])
				continue;
			for(int i=0; i<8; i++){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if(!map[ny][nx])
					damage[y][x]++;
			}
			if(isCrash(x, y)){
				crashed[y][x] = true;
				q.push(qnode(x, y, 1));
			}
		}
	}
}

int solve(int h, int w)
{
	queue<qnode> q;
	setQueue(h, w, q);
	return bfs(q);
}

int main(void)
{
	ios::sync_with_stdio(false);
	int h, w;
	input(h, w);
	cout << solve(h, w) << '\n';
	return 0;
}

