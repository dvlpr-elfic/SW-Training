
#include <iostream>
#include <vector>
#include <queue>

#define SIZE 51

using namespace std;

int map[SIZE][SIZE];

typedef struct node
{
	int x, y;
	node(int x, int y):x(x), y(y){}
}node;

typedef struct qnode
{
	int x, y, n;
	qnode(int x, int y, int n):x(x), y(y), n(n){}
}qnode;

int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int manual[2][4] = {{0, 1, 2, 3}, {2, 1, 0, 3}};

void input(int &h, int &w, int &t, vector<node> &cleaner)
{
	cin >> h >> w >> t;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			cin >> map[y][x];
			if(map[y][x] == -1){
				cleaner.push_back(node(x, y));
			}
		}
	}
}

bool isDust(int x, int y)
{
	return (map[y][x] > 0);
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

bool isCleaner(int x, int y)
{
	return (map[y][x] == -1);
}

void spread(int x, int y, int h, int w, queue<qnode> &q)
{
	int next = map[y][x]/5;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, h, w) || isCleaner(nx, ny))
			continue;
		q.push(qnode(nx, ny, next));
		map[y][x] -= next;
	}
}

void process(int &x, int &y, int h, int w, int limit, int dir)
{
	while(1){
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if(isOut(nx, ny, h, w) || ny == limit || isCleaner(nx, ny))
			break;
		if(isCleaner(x, y)){
			map[ny][nx] = 0;
		}
		else{
			map[y][x] = map[ny][nx];
			map[ny][nx] = 0;
		}
		x = nx, y = ny;
	}
}

void circulate(int h, int w, vector<node> &cleaner)
{
	for(int i=0; i<2; i++){
		int x = cleaner[i].x, y = cleaner[i].y;
		int limit = cleaner[(i+1)%2].y;
		for(int j=0; j<4; j++){
			process(x, y, h, w, limit, manual[i][j]);
		}
	}
}

void simulation(int h, int w, vector<node> &cleaner)
{
	queue<qnode> q;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			if(isDust(x, y)){
				spread(x, y, h, w, q);
			}
		}
	}
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, n = q.front().n;	q.pop();
		map[y][x] += n;
	}
	circulate(h, w, cleaner);
}

int counting(int h, int w)
{
	int ret = 0;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			if(map[y][x] > 0){
				ret += map[y][x];
			}
		}
	}
	return ret;
}

int solve(int h, int w, int t, vector<node> &cleaner)
{
	while(t--){
		simulation(h, w, cleaner);
	}
	return counting(h, w);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int h, w, t;
	vector<node> cleaner;
	input(h, w, t, cleaner);
	cout << solve(h, w, t, cleaner) << '\n';
	return 0;
}

