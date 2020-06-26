
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>

#define SIZE 101

using namespace std;

typedef struct qnode
{
	int x, y, z, level;
	qnode(int x, int y, int z, int level):x(x), y(y), z(z), level(level){}
}qnode;

int map[SIZE][SIZE][SIZE];
int dx[] = {0, 1, 0, -1, 0, 0};
int dy[] = {-1, 0, 1, 0, 0, 0};
int dz[] = {0, 0, 0, 0, -1, 1};

int input(int &m, int &n, int &h, int &counter, queue<qnode> &q)
{
	bool allblank = true;
	bool no_one = true;
	counter = 0;
	cin >> m >> n >> h;
	for(int z=0; z<h; z++){
		for(int y=0; y<n; y++){
			for(int x=0; x<m; x++){
				int tmp;
				cin >> tmp;
				map[z][y][x] = tmp;
				if(tmp != -1 && allblank)
					allblank = false;
				if(tmp == 1 && no_one)
					no_one = false;
				if(tmp == 0)
					counter++;
				if(tmp == 1)
					q.push(qnode(x, y, z, 0));
			}
		}
	}
	if(!allblank && !no_one && counter)		// 1이 하나라도 있고, 모두 빈칸이 아닐 경우
		return 1;
	else if(counter == 0)
		return 0;
	else
		return -1;
}

bool isWall(int x, int y, int z, int m, int n, int h)
{
	return (x<0 || y<0 || z<0 || x>=m || y>=n || z>=h);
}

bool isFinished(int counter)
{
	return !counter;
}

int bfs(queue<qnode> &q, int &counter, int m, int n, int h)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, z = q.front().z, level = q.front().level;	q.pop();
		for(int i=0; i<6; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			int nz = z + dz[i];
			if(isWall(nx, ny, nz, m, n, h))
				continue;
			if(map[nz][ny][nx] == 0){
				map[nz][ny][nx] = 1;
				q.push(qnode(nx, ny, nz, level+1));
				counter--;
			}
			if(isFinished(counter))
				return level+1;
		}
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n, m, h, counter;
	queue<qnode> q;
	int temp = input(m, n, h, counter, q);
	if(temp != 1)
		cout << temp;
	else
		cout << bfs(q, counter, m, n, h);
	return 0;
}
