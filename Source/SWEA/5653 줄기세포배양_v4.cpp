
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 351

using namespace std;

typedef struct qnode
{
	int x, y, life;
	qnode(int x, int y, int l):x(x), y(y), life(l){}
}qnode;

bool check[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void enQueue(int x, int y, int life, queue<qnode> &q)
{
	q.push(qnode(x, y, life));
}

void input(int &k, queue<qnode> *q)
{
	int h, w;
	cin >> h >> w >> k;
	int base = k/2;
	for(int y=base; y<h+base; y++){
		for(int x=base; x<w+base; x++){
			int temp;
			cin >> temp;
			if(temp){
				enQueue(x, y, temp*2, q[temp]);
				check[y][x] = true;
			}
		}
	}
}

void deQueue(int &x, int &y, int &life, queue<qnode> &q)
{
	x = q.front().x, y = q.front().y, life = q.front().life-1;	q.pop();
}

bool isCanSpread(int life, int level)
{
	return (life == level-1);
}

void spread(int x, int y, int level, queue<qnode> &q)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!check[ny][nx]){
			check[ny][nx] = true;
			enQueue(nx, ny, level*2, q);
		}
	}
}

bool isAlive(int life)
{
	return (life > 0);
}

void simulation(queue<qnode> *q)
{
	for(int level=10; level>=1; level--){
		int len = q[level].size();
		while(len--){
			int x, y, life;
			deQueue(x, y, life, q[level]);
			if(isCanSpread(life, level)){
				spread(x, y, level, q[level]);
			}
			if(isAlive(life)){
				enQueue(x, y, life, q[level]);
			}
		}
	}
}

int counting(queue<qnode> *q)
{
	int ret = 0;
	for(int i=1; i<=10; i++){
		ret += q[i].size();
	}
	return ret;
}

int solve(void)
{
	int k;
	queue<qnode> q[11];
	input(k, q);
	while(k--){
		simulation(q);
	}
	memset(check, 0, sizeof(check));
	return counting(q);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		cout << '#' << tc << ' ' << solve() << '\n';
	}
	return 0;
}

