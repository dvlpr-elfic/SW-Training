
/**
  * @author Jihoon Jang
  * 50 min
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

bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &h, int &w, int &k, queue<qnode> *q)
{
	cin >> h >> w >> k;
	int margin = k/2;
	for(int y=margin; y<h+margin; y++){
		for(int x=margin; x<w+margin; x++){
			int temp;
			cin >> temp;
			if(temp){
				visited[y][x] = true;
				q[temp].push(qnode(x, y, 0));
			}
		}
	}
}

bool isAlive(int level, int life)
{
	return (2*level > life);
}

void spread(int x, int y, queue<qnode> &q)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(!visited[ny][nx]){
			visited[ny][nx] = true;
			q.push(qnode(nx, ny, 0));
		}
	}
}

void simulation(queue<qnode> *q)
{
	for(int i=10; i>0; i--){
		int len = q[i].size();
		while(len--){
			int x = q[i].front().x, y = q[i].front().y, life = q[i].front().life+1;	q[i].pop();
			if(isAlive(i, life)){
				q[i].push(qnode(x, y, life));
			}
			if(life == i+1){
				spread(x, y, q[i]);
			}
		}
	}
}

int counting(queue<qnode> *q)
{
	int ret=0;
	for(int i=1; i<=10; i++){
		ret += q[i].size();
	}
	return ret;
}

int solve(int k, queue<qnode> *q)
{
	while(k--){
		simulation(q);
	}
	memset(visited, 0, sizeof(visited));
	return counting(q);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int h, w, k;
		queue<qnode> q[11];
		input(h, w, k, q);
		cout << '#' << tc << ' ' << solve(k, q) << '\n';
	}
	return 0;
}

