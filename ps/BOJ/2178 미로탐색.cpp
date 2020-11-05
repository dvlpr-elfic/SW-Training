
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>

#define SIZE 200

using namespace std;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

typedef struct qnode
{
	int x, y, n;
	qnode(int x, int y, int n):x(x), y(y), n(n){}
}qnode;

bool isWall(int x, int y, int n, int m)
{
	return (x<1 || y<1 || x>m || y>n);
}

void input(int &n, int &m, queue<qnode> &q)
{
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			char ch;
			cin >> ch;
			map[i][j] = ch - '0';
		}
	}
	q.push(qnode(1, 1, 1));
	visited[1][1] = true;
}

int bfs(queue<qnode> &q, int m, int n)
{
	while(!q.empty()){
		int cnt = q.front().n, x = q.front().x, y = q.front().y;	q.pop();
		if(x == m && y == n){
			return cnt;
		}
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isWall(nx, ny, n, m))
				continue;
			if(map[ny][nx] && !visited[ny][nx]){
				visited[ny][nx] = true;
				q.push(qnode(nx, ny, cnt+1));
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n, m;
	queue<qnode> q;
	input(n, m, q);
	cout << bfs(q, m, n) << '\n';
	return 0;
}
