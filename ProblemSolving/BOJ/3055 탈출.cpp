
/**
  * @author Jihoon Jang
  * 44min
  */

#include <iostream>
#include <queue>
#include <algorithm>

#define SIZE 51
#define INF 0x7FFFFFFF

using namespace std;

typedef struct qnode
{
	int x, y, level;
	qnode(int x, int y, int l):x(x), y(y), level(l){}
}qnode;

typedef struct pos
{
	int x, y;
}pos;

bool stone[SIZE][SIZE];
int map[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
bool visited[SIZE][SIZE];

void input(int &h, int &w, queue<qnode> &waterq, pos &cave, queue<qnode> &sq)
{
	cin >> h >> w;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			char ch;
			cin >> ch;
			if(ch == '*')
				waterq.push(qnode(x, y, 0));
			else if(ch == 'D')
				cave.x = x, cave.y = y;
			else if(ch == 'X')
				stone[y][x] = true;
			else if(ch == 'S')
				map[y][x] = INF, sq.push(qnode(x, y, 0));
			else if(ch == '.')
				map[y][x] = INF;
		}
	}
}

void pop(int &x, int &y, int &level, queue<qnode> &q)
{
	x = q.front().x, y = q.front().y, level = q.front().level;	q.pop();
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

bool isStone(int x, int y)
{
	return stone[y][x];
}

bool isCave(int x, int y, pos &cave)
{
	return (x == cave.x && y == cave.y);
}

bool isLower(int x, int y, int level)
{
	return (map[y][x] > level);
}

void marking(int x, int y, int level)
{
	map[y][x] = level;
}

void setWaterRoute(int h, int w, pos &cave, queue<qnode> &q)
{
	if(q.empty())
		return;
	map[q.front().y][q.front().x] = min(map[q.front().y][q.front().x], q.front().level);
	while(!q.empty()){
		int x, y, level;
		pop(x, y, level, q);
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isOut(nx, ny, h, w))	continue;
			if(isStone(nx, ny))	continue;
			if(isCave(nx, ny, cave))	continue;
			if(isLower(nx, ny, level)){
				marking(nx, ny, level);
				q.push(qnode(nx, ny, level+1));
			}
		}
	}
}

void travel(int h, int w, pos &cave, queue<qnode> &q)
{
	if(q.empty()){
		cout << "KAKTUS" << '\n';
		return;
	}
	visited[q.front().y][q.front().x] = true;
	while(!q.empty()){
		int x, y, level;
		pop(x, y, level, q);
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isOut(nx, ny, h, w))	continue;
			if(isStone(nx, ny))	continue;
			if(isCave(nx, ny, cave)){
				cout << level+1 << '\n';
				return;
			}
			if(isLower(nx, ny, level)){
				if(!visited[ny][nx]){
					visited[ny][nx] = true;
					q.push(qnode(nx, ny, level+1));
				}
			}
		}
	}
	cout << "KAKTUS" << '\n';
}

void solve(int h, int w, pos &cave, queue<qnode> &waterq, queue<qnode> &sq)
{
	setWaterRoute(h, w, cave, waterq);
	travel(h, w, cave, sq);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int h, w;
	queue<qnode> waterq, sq;
	pos cave;
	input(h, w, waterq, cave, sq);
	solve(h, w, cave, waterq, sq);
	return 0;
}

