
#include <iostream>
#include <queue>
#include <string.h>

#define MAP_SIZE 351

using namespace std;

typedef struct qnode
{
	int x, y, level, life;
	qnode(int _x, int _y, int _level, int _life)
	{
		x = _x, y = _y, level = _level, life = _life;
	}
}qnode;


int map[MAP_SIZE][MAP_SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

int solve(queue<qnode> *q)
{
	int ans = 0;
	for(int i=1; i<11; i++){
		ans += q[i].size();
	}
	return ans;
}


void print(int n, int m, int k)
{
	cout << "--------------------------------------------------" << endl;
	for(int i=0; i<n+k; i++){
		for(int j=0; j<m+k; j++){
			cout.width(3);
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "--------------------------------------------------" << endl;
}

void init(void)
{
	memset(map, 0, sizeof(map));
}


void input(queue<qnode> *q, int n, int m, int k)
{
	int start = k/2;
	for(int i=start; i<n; i++){
		for(int j=start; j<m; j++){
			int temp;
			cin >> temp;
			if(temp){
				map[i][j] = temp;
				q[temp].push(qnode(j, i, temp, temp*2));
			}
		}
	}
}

void spread(queue<qnode> &q, qnode &item)
{
	int x = item.x, y = item.y, level = item.level;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!map[ny][nx]){
			map[ny][nx] = level;
			q.push(qnode(nx, ny, level, level*2));
		}
	}
}

void bfs(queue<qnode> *q, int k, int n, int m)
{
	int K = k;
	while(k--){
		//cout << k << endl;
		//print(n, m, K);
		for(int n=10; n>0; n--){
			int len = q[n].size();
			//print(n, m, k);
			for(int i=0; i<len; i++){
				qnode item = q[n].front();	q[n].pop();
				if(item.level == item.life){
					spread(q[n], item);
				}
				item.life--;
				if(item.life > 0)
					q[n].push(item);
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
		queue<qnode> q[11];
		int n, m, k;
		cin >> n >> m >> k;
		init();
		input(q, n+k/2, m+k/2, k);
		//print(n, m, k);
		bfs(q, k, n, m);
		//print(n, m, k);
		cout << "#" << tc << " " << solve(q) << endl;
	}

	return 0;
}
