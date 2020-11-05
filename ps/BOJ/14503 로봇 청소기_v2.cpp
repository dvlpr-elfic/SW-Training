
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>

#define SIZE 51

using namespace std;

typedef struct qnode
{
	int x, y, dir, clean;
	qnode(int x, int y, int d, int c):x(x), y(y), dir(d), clean(c){}
}qnode;

int wall[SIZE][SIZE];
bool cleaned[SIZE][SIZE];
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

void input(int &h, int &w, queue<qnode> &q)
{
	cin >> h >> w;
	int x, y, dir;
	cin >> y >> x >> dir;
	q.push(qnode(x, y, dir, 1));
	for(y=0; y<h; y++){
		for(x=0; x<w; x++){
			cin >> wall[y][x];
		}
	}
}

bool checking(int x, int y)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!wall[ny][nx] && !cleaned[ny][nx])
			return false;
	}
	return true;
}

bool isCanBack(int x, int y, int dir)
{
	int nx = x + dx[(dir+2)%4];
	int ny = y + dy[(dir+2)%4];
	return (!wall[ny][nx]);
}

void goBack(int x, int y, int dir, queue<qnode> &q)
{
	int nx = x + dx[(dir+2)%4];
	int ny = y + dy[(dir+2)%4];
	q.push(qnode(nx, ny, dir, 0));
}

bool isCanGoLeft(int x, int y, int dir)
{
	int nx = x + dx[(dir+3)%4];
	int ny = y + dy[(dir+3)%4];
	return (!wall[ny][nx] && !cleaned[ny][nx]);
}

void goLeft(int x, int y, int dir, queue<qnode> &q)
{
	int ndir = (dir+3)%4;
	int nx = x + dx[ndir];
	int ny = y + dy[ndir];
	q.push(qnode(nx, ny, ndir, 1));
}

void turnLeft(int x, int y, int dir, queue<qnode> &q)
{
	int ndir = (dir+3)%4;
	q.push(qnode(x, y, ndir, 0));
}

int simulation(queue<qnode> &q)
{
	int ret = 0;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, dir = q.front().dir, clean = q.front().clean;	q.pop();
		if(clean){
			ret++;
			cleaned[y][x] = 1;
		}
		if(checking(x, y)){
			if(isCanBack(x, y, dir)){
				goBack(x, y, dir, q);
			}
		}
		else{
			if(isCanGoLeft(x, y, dir)){
				goLeft(x, y, dir, q);
			}
			else{
				turnLeft(x, y, dir, q);
			}
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int h, w;
	queue<qnode> q;
	input(h, w, q);
	cout << simulation(q);
	return 0;
}

