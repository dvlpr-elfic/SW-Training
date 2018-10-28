

/**
 * @author Jihoon Jang
 */

#include <iostream>
#include <queue>
#include <memory.h>

#define MAP_SIZE 51

using namespace std;

typedef struct qnode
{
	int x, y, t;
	qnode(int x, int y, int t):x(x), y(y), t(t){}
}qnode;


int map[MAP_SIZE][MAP_SIZE];
int visited[MAP_SIZE][MAP_SIZE];
int tunnel[8][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 1, 0, 0, }, {0, 1, 1, 0}, {0, 0, 1, 1}, {1, 0, 0, 1}};
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int ans = 0;

bool isWall(int x, int y, int n, int m)
{
	return (x<0 || y<0 || x>=m || y >=n);
}

void print(int n, int m)
{
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cout.width(3);
			cout << visited[i][j];
		}
		cout << endl;
	}

}


void init(void)
{
	ans = 0;
	memset(visited, 0, sizeof(visited));
	memset(map, 0, sizeof(map));
}

void bfs(queue<qnode> &q, int n, int m, int l)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, t = q.front().t;	q.pop();
		if(t > l)
			continue;
		if(visited[y][x])
			continue;
		visited[y][x] = t;
		ans++;
		int type = map[y][x];
		for(int i=0; i<4; i++){
			if(tunnel[type][i]){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if(!isWall(nx, ny, n, m)){
					int reverse_dir = (i+2)%4;
					int n_type = map[ny][nx];
					if(!tunnel[n_type][reverse_dir])
						continue;
					if(visited[ny][nx] || !map[ny][nx])
						continue;
					q.push(qnode(nx, ny, t+1));
				}
			}
		}
	}
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		int n, m, r, c, l;
		cin >> n >> m >> r >> c >> l;
		queue<qnode> q;
		q.push(qnode(c, r, 1));
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				cin >> map[i][j];
			}
		}
		bfs(q, n, m, l);
		//print(n, m);
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
