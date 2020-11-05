
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <memory.h>
#include <algorithm>

#define SIZE 100
#define INF 0x3FFFFFFF

using namespace std;

typedef struct qnode
{
	int x, y, d;
	qnode(int x, int y, int d):x(x), y(y), d(d){}
}qnode;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {-1, 1, 0};
int dy[] = {0, 0, 1};

void input(void)
{
	int tmp;
	cin >> tmp;
	for(int y=0; y<SIZE; y++){
		for(int x=0; x<SIZE; x++){
			cin >> map[y][x];
		}
	}
}

bool isWall(int x, int y)
{
	return (x<0 || y<0 || x>=SIZE || y>=SIZE);
}

bool isArrive(int y)
{
	return (y == (SIZE-1));
}

int travel(queue<qnode> &q)
{
	while(1){
		int x = q.front().x, y = q.front().y, d = q.front().d;	q.pop();
		if(isArrive(y))
			return d;
		for(int i=0; i<3; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isWall(nx, ny))
				continue;
			if(!visited[ny][nx] && map[ny][nx]){
				visited[ny][nx] = true;
				q.push(qnode(nx, ny, d+1));
				break;
			}
		}
	}
	return -1;
}

int solve(void)
{
	queue<qnode> q;
	int ret = 0;
	int d = INF;
	for(int x=0; x<SIZE; x++){
		if(!map[0][x])
			continue;
		memset(visited, 0, sizeof(visited));
		visited[0][x] = true;
		q.push(qnode(x, 0, 0));
		int temp = travel(q);
		if(d > temp){
			d = temp;
			ret = x;
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		input();
		cout << '#' << tc << ' ' << solve() << '\n';
	}
	return 0;
}

