
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>

#define SIZE 20

using namespace std;

typedef struct qnode
{
	int x, y, dir;
	qnode(int x, int y, int d):x(x), y(y), dir(d){}
}qnode;

int wall[SIZE][SIZE];
int dx[] = {1, 1, 0};
int dy[] = {0, 1, 1};

void input(int &n)
{
	cin >> n;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> wall[y][x];
		}
	}
}

void pop(queue<qnode> &q, int &x, int &y, int &dir)
{
	x = q.front().x, y = q.front().y, dir = q.front().dir;	q.pop();
}

bool isArrive(int x, int y, int n)
{
	return (x == n-1 && y == n-1);
}

void setNextPos(int &nx, int &ny, int x, int y, int ndir)
{
	nx = x + dx[ndir], ny = y + dy[ndir];
}

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

bool isCanCross(int _x, int _y)
{
	for(int y=_y; y<_y+2; y++){
		for(int x=_x; x<_x+2; x++){
			if(wall[y][x])
				return false;
		}
	}
	return true;
}

bool isCanGo(int x, int y, int nx, int ny, int n, int ndir)
{
	if(isOut(nx, ny, n))
		return false;
	if(ndir == 1)
		return isCanCross(x, y);
	else
		return (!wall[ny][nx]);
}

int simulation(int n)
{
	queue<qnode> q;
	q.push(qnode(1, 0, 0));
	int ret = 0;
	while(!q.empty()){
		int x, y, dir;
		pop(q, x, y, dir);
		if(isArrive(x, y, n)){
			ret++;
			continue;
		}
		for(int delta=-1; delta<=1; delta++){
			int ndir = dir + delta;
			if(ndir < 0 || ndir > 2)
				continue;
			int nx, ny;
			setNextPos(nx, ny, x, y, ndir);
			if(isCanGo(x, y, nx, ny, n, ndir)){
				q.push(qnode(nx, ny, ndir));
			}
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n;
	input(n);
	cout << simulation(n) << endl;
	return 0;
}

