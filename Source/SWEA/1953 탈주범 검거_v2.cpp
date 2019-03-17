
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 55

using namespace std;

typedef struct qnode
{
	int x, y, level;
	qnode(int x, int y, int l):x(x), y(y), level(l){}
}qnode;

int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
const bool type[8][4] = 
{{0, }, 
{1, 1, 1, 1}, 
{1, 0, 1, 0}, 
{0, 1, 0, 1},
{1, 1, 0, 0}, 
{0, 1, 1, 0}, 
{0, 0, 1, 1}, 
{1, 0, 0, 1}
};

void input(int &h, int &w, int &r, int &c, int &t)
{
	cin >> h >> w >> r >> c >> t;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			cin >> map[y][x];
		}
	}
}

bool isOpenDir(int x, int y, int dir)
{
	return (type[map[y][x]][dir]);
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

int bfs(int h, int w, int t, queue<qnode> &q)
{
	int ret = 0;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, level = q.front().level;	q.pop();
		ret++;
		if(t <= level)
			continue;
		for(int dir=0; dir<4; dir++){
			if(!isOpenDir(x, y, dir))
				continue;
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if(isOut(nx, ny, h, w))
				continue;
			if(!visited[ny][nx] && map[ny][nx] && isOpenDir(nx, ny, (dir+2)%4)){
				visited[ny][nx] = true;
				q.push(qnode(nx, ny, level+1));
			}
		}
	}
	memset(visited, 0, sizeof(visited));
	return ret;
}

int solve(int h, int w, int x, int y, int t)
{
	queue<qnode> q;
	visited[y][x] = true;
	q.push(qnode(x, y, 1));
	return bfs(h, w, t, q);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int h, w, r, c, t;
		input(h, w, r, c, t);
		cout << '#' << tc << ' ' << solve(h, w, c, r, t) << '\n';
	}
	return 0;
}

