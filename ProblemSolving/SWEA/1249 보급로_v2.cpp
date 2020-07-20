
#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 101
#define INF 987654321

using namespace std;

typedef struct qnode
{
	int x, y;
	qnode(int x, int y):x(x), y(y){}
}qnode;

int map[SIZE][SIZE];
int price[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n, queue<qnode> &q)
{
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			char ch;
			cin >> ch;
			map[i][j] = ch - '0';
			price[i][j] = INF;
		}
	}
	price[0][0] = 0;
	q.push(qnode(0, 0));
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

bool isLowerPrice(int nx, int ny, int x, int y)
{
	return (price[ny][nx] > price[y][x] + map[ny][nx]);
}

void pushPrice(int nx, int ny, int x, int y)
{
	price[ny][nx] = price[y][x] + map[ny][nx];
}

int bfs(int n, queue<qnode> &q)
{
	while(!q.empty()){
		int x = q.front().x,  y = q.front().y;	q.pop();
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isWall(nx, ny, n))
				continue;
			if(isLowerPrice(nx, ny, x, y)){
				pushPrice(nx, ny, x, y);
				q.push(qnode(nx, ny));
			}
		}
	}
	return price[n-1][n-1];
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n;
		queue<qnode> q;
		input(n, q);
		int ans = bfs(n, q);
		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}
