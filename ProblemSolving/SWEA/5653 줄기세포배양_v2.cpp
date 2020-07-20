
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 400

using namespace std;

typedef struct qnode
{
	int x, y, life;
	qnode(int x, int y, int life):x(x), y(y), life(life){}
}qnode;


bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void init(void)
{
	memset(visited, 0, sizeof(visited));
}

int calAnswer(queue<qnode> *q)
{
	int ret = 0;
	for(int i=1; i<=10; i++){
		ret += q[i].size();
	}
	return ret;
}


void input(int &n, int &m, int &k, queue<qnode> *q)
{
	cin >> n >> m >> k;
	int start = k/2+1;
	for(int y=start; y<n+start; y++){
		for(int x=start; x<m+start; x++){
			int tmp;
			cin >> tmp;
			if(!tmp)
				continue;
			visited[y][x] = true;
			q[tmp].push(qnode(x, y, tmp*2));
		}
	}
}

void spread(int x, int y, int level, queue<qnode> *q)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!visited[ny][nx]){
			visited[ny][nx] = true;
			q[level].push(qnode(nx, ny, level*2));
		}
	}
}

void bfs(queue<qnode> *q, int k)
{
	while(k--){
		for(int level=10; level>0; level--){
			int len = q[level].size();
			for(int i=0; i<len; i++){
				int x = q[level].front().x, y = q[level].front().y, life = q[level].front().life;	q[level].pop();
				life--;
				if(life == level-1){
					spread(x, y, level, q);
				}
				if(life == 0){
					continue;
				}
				q[level].push(qnode(x, y, life));
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
		int n, m, k;
		queue<qnode> q[11];
		input(n, m, k, q);
		bfs(q, k);
		int ans = calAnswer(q);
		cout << "#" << tc << " " << ans << '\n';
	}

	return 0;
}
