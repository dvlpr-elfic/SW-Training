
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 100

using namespace std;

bool visited[SIZE][SIZE];
int map[SIZE][SIZE];
int dx[] = {-1, 1, 0};
int dy[] = {0, 0, -1};

typedef struct qnode
{
	int x, y;
	qnode(int x, int y):x(x), y(y){}
}qnode;

void init(void)
{
	memset(visited, 0, sizeof(visited));
}

void input(queue<qnode> &q)
{
	int tmp;
	cin >> tmp;
	for(int y=0; y<SIZE; y++){
		for(int x=0; x<SIZE; x++){
			cin >> map[y][x];
			if(map[y][x] == 2){
				q.push(qnode(x, y));
				visited[y][x] = true;
			}
		}
	}
}

bool isArrive(int y)
{
	return (!y);
}

bool isWall(int x, int y)
{
	return (x<0 || y<0 || x>=SIZE || y>=SIZE);
}

int travel(queue<qnode> &q)
{
	while(1){
		int x = q.front().x, y = q.front().y;	q.pop();
		if(isArrive(y))
			return x;
		for(int i=0; i<3; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isWall(nx, ny))
				continue;
			if(!visited[ny][nx] && map[ny][nx]){
				visited[ny][nx] = true;
				q.push(qnode(nx, ny));
				break;
			}
		}
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		queue<qnode> q;
		init();
		input(q);
		cout << '#' << tc << ' ' << travel(q) << '\n';
	}
	return 0;
}
