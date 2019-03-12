
/**
  * @author Jihoon Jang
  * 40 min
  */

#include <iostream>
#include <queue>
#include <algorithm>
#include <memory.h>

#define SIZE 21

using namespace std;

typedef struct qnode
{
	int x, y;
	qnode(int x, int y):x(x), y(y){}
}qnode;

int house[SIZE][SIZE];
bool visited[SIZE][SIZE];
int operating_price[41];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n, int &m)
{
	cin >> n >> m;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> house[y][x];
		}
	}
}

void setOperatingPrice(void)
{
	int diff = 4;
	operating_price[1] = 1;
	for(int k=2; k<=40; k++){
		operating_price[k] = operating_price[k-1] + diff;
		diff += 4;
	}
}

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void spread(int x, int y, int n, queue<qnode> &q)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, n))	continue;
		if(!visited[ny][nx]){
			visited[ny][nx] = true;
			q.push(qnode(nx, ny));
		}
	}
}

int getOperatingPrice(int k)
{
	return operating_price[k];
}

int simulation(int _x, int _y, int n, int m)
{
	queue<qnode> q;
	q.push(qnode(_x, _y));
	visited[_y][_x] = true;
	int k = 1;
	int ret = 0, cnt = 0;
	while(!q.empty()){
		int len = q.size();
		for(int i=0; i<len; i++){
			int x = q.front().x, y = q.front().y;	q.pop();
			if(house[y][x])
				cnt++;
			spread(x, y, n, q);
		}
		int price = getOperatingPrice(k);
		if(price <= cnt*m){
			ret = max(ret, cnt);
		}
		k++;
	}
	memset(visited, 0, sizeof(visited));
	return ret;
}

int solve(int n, int m)
{
	int ret = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			ret = max(ret, simulation(x, y, n, m));
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	setOperatingPrice();
	for(int tc=1; tc<=t; tc++){
		int n, m;
		input(n, m);
		cout << '#' << tc << ' ' << solve(n, m) << '\n';
	}
	return 0;
}

