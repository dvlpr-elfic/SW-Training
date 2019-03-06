
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>
#include <queue>
#include <algorithm>

#define SIZE 20

using namespace std;

typedef struct qnode
{
	int x, y, level;
	qnode(int x, int y, int l):x(x), y(y), level(l){}
}qnode;

int origin[SIZE][SIZE];
int map[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n, int &h, int &w, int &cnt)
{
	cnt = 0;
	cin >> n >> w >> h;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			cin >> origin[y][x];
			if(origin[y][x])
				cnt++;
		}
	}
}

void copyMap(void)
{
	memcpy(map, origin, sizeof(origin));
}

int getStartPos(int x, int h)
{
	for(int y=0; y<h; y++){
		if(map[y][x])
			return y;
	}
	return -1;
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

int crash(int _x, int _y, int h, int w)
{
	queue<qnode> q;
	q.push(qnode(_x, _y, map[_y][_x]-1));
	map[_y][_x] = 0;
	int ret=0;
	while(!q.empty()){
		int x=q.front().x, y=q.front().y, level=q.front().level;	q.pop();
		ret++;
		if(!level)
			continue;
		for(int dir=0; dir<4; dir++){
			int nx = x, ny = y;
			for(int i=0; i<level; i++){
				nx += dx[dir];
				ny += dy[dir];
				if(isOut(nx, ny, h, w))	break;
				if(!map[ny][nx])	continue;
				q.push(qnode(nx, ny, map[ny][nx]-1));
				map[ny][nx] = 0;
			}
		}
	}
	return ret;
}

void sorting(int h, int w)
{
	for(int x=0; x<w; x++){
		int y = h-1;
		int low = h-1;
		while(y>=0){
			if(map[y][x]){
				int temp = map[y][x];
				map[y][x] = 0;
				map[low][x] = temp;
				low--;
			}
			y--;
		}
	}
}

int simulation(int n, int h, int w, int *ballpos)
{
	copyMap();
	int ret=0;
	for(int i=0; i<n; i++){
		int x = ballpos[i];
		int y = getStartPos(x, h);
		if(y < 0)
			continue;
		ret += crash(x, y, h, w);
		sorting(h, w);
	}
	return ret;
}

int solve(int depth, int n, int *ballpos, int idx, int h, int w)
{
	if(depth == n){
		return simulation(n, h, w, ballpos);
	}
	int ret = 0;
	for(int i=0; i<w; i++){
		ballpos[idx] = i;
		ret = max(ret, solve(depth+1, n, ballpos, idx+1, h, w));
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
		int n, h, w, cnt;
		input(n, h, w, cnt);
		int *ballpos = new int[n];
		int ans = cnt - solve(0, n, ballpos, 0, h, w);
		cout << '#' << tc << ' ' << ans << '\n';
	}
	return 0;
}

