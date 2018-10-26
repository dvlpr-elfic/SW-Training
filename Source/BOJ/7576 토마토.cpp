
#include <iostream>
#include <queue>
#define MAP_SIZE 1001

using namespace std;

typedef struct qnode
{
	int x, y, count;
	qnode(int x, int y, int c):x(x), y(y), count(c){}
}qnode;

int map[MAP_SIZE][MAP_SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int max_cnt = 0;

bool isWall(int x, int y, int n, int m)
{
	return (x>=m || y>=n || x<0 || y<0);
}

void bfs(queue<qnode> &q, int n, int m)
{
	while(!q.empty()){
		qnode item = q.front();	q.pop();
		for(int i=0; i<4; i++){
			int nx = item.x + dx[i];
			int ny = item.y + dy[i];
			if(!isWall(nx, ny, n, m)){
				if(!map[ny][nx]){
					map[ny][nx] = 1;
					q.push(qnode(nx, ny, item.count+1));
					if(max_cnt < item.count+1)
						max_cnt = item.count+1;
				}
			}
		}
	}
}

int main(void)
{

	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	cin.tie(NULL);
	int m, n;
	cin >> m >> n;
	max_cnt = 0;
	queue<qnode> q;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> map[i][j];
			if(map[i][j] == 1){
				q.push(qnode(j, i, 0));
			}
			else if(map[i][j] == 0)		// 익지 않은 토마토가 하나라도 있으면 -1로
				max_cnt = -1;
		}
	}
	if(!max_cnt){
		cout << 0 << endl;
	}
	else{
		bfs(q, n, m);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(!map[i][j]){
					cout << -1 << endl;
					return 0;
				}
			}
		}
		cout << max_cnt << endl;
	}

	return 0;
}
