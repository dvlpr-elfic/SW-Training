
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 12
#define maxAge 500

using namespace std;

typedef struct qnode
{
	int x, y, age, n;
	qnode(int x, int y, int age, int n):x(x), y(y), age(age), n(n){}
}qnode;

int recharge[SIZE][SIZE];
int food[SIZE][SIZE];
long long tree[maxAge][SIZE][SIZE];

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void init(void)
{
	for(int y=1; y<SIZE; y++)
		for(int x=1; x<SIZE; x++)
			food[y][x] = 5;
	memset(recharge, 0, sizeof(recharge));
	memset(tree, 0, sizeof(tree));
}

void input(int &n, int &m, int &k)
{
	cin >> n >> m >> k;
	for(int y=1; y<=n; y++){
		for(int x=1; x<=n; x++){
			cin >> recharge[y][x];
		}
	}
	for(int i=0; i<m; i++){
		int x, y, age;
		cin >> y >> x >> age;
		tree[age][y][x]++;
	}
}

void spring(queue<qnode> &dieq, int n)
{
	queue<qnode> liveq;
	for(int age=1; age<maxAge; age++){
		for(int y=1; y<=n; y++){
			for(int x=1; x<=n; x++){
				if(!tree[age][y][x])
					continue;
				int need = tree[age][y][x]*age;
				int die, alive;
				if(need > food[y][x]){
					alive = food[y][x]/age;
					die = tree[age][y][x] - alive;
					dieq.push(qnode(x, y, age, die));
					liveq.push(qnode(x, y, age, alive));
				}
				else{
					alive = tree[age][y][x];
					die = 0;
					liveq.push(qnode(x, y, age, alive));
				}
				food[y][x] -= age*alive;
				tree[age][y][x] = 0;
			}
		}
	}
	while(!liveq.empty()){
		int x = liveq.front().x, y = liveq.front().y, age = liveq.front().age, t = liveq.front().n;	liveq.pop();
		tree[age+1][y][x] += t;
	}
}

void summer(queue<qnode> &q)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, age = q.front().age, t = q.front().n;	q.pop();
		int add = age/2;
		food[y][x] += add*t;
	}
}

void fall(int n)
{
	for(int age=5; age<maxAge; age+=5){
		for(int y=1; y<=n; y++){
			for(int x=1; x<=n; x++){
				if(!tree[age][y][x])
					continue;
				for(int i=0; i<8; i++){
					int nx = x + dx[i];
					int ny = y + dy[i];
					tree[1][ny][nx] += tree[age][y][x];
				}
			}
		}
	}
}

void winter(int n)
{
	for(int y=1; y<=n; y++){
		for(int x=1; x<=n; x++){
			food[y][x] += recharge[y][x];
		}
	}
}

int counting(int n)
{
	int ret = 0;
	for(int age=1; age<maxAge; age++){
		for(int y=1; y<=n; y++){
			for(int x=1; x<=n; x++){
				ret += tree[age][y][x];
			}
		}
	}
	return ret;
}

int solve(int n, int k)
{
	while(k--){
		queue<qnode> dieq;
		spring(dieq, n);
		summer(dieq);
		fall(n);
		winter(n);
	}
	return counting(n);
}

int main(void)
{
	ios::sync_with_stdio(false);
	init();
	//freopen("input.txt", "r", stdin);
	int n, m, k;
	input(n, m, k);
	cout << solve(n, k) << endl;
	return 0;
}

