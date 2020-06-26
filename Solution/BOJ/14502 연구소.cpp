
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <memory.h>

#define SIZE 10

using namespace std;

typedef struct vnode
{
	int x, y;
	vnode(int x, int y):x(x), y(y){}
}vnode;

int lab[SIZE][SIZE];
int map[SIZE][SIZE];
bool picked[SIZE*SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int ans = 0;

bool isWall(int x, int y, int n, int m)
{
	return (x<0 || y<0 || x>=m || y>=n);
}

void spread(int x, int y, int n, int m)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n, m))
			continue;
		if(!visited[ny][nx] && !map[ny][nx]){
			map[ny][nx] = 2;
			visited[ny][nx] = true;
			spread(nx, ny, n, m);
		}
	}
}

int virus(int n, int m, vector<vnode> pick)
{
	int ret = 0;
	memcpy(map, lab, sizeof(map));
	memset(visited, 0, sizeof(visited));
	int len = pick.size();
	for(int i=0; i<len; i++){					// 벽 세우기
		int x = pick[i].x, y = pick[i].y;
		map[y][x] = 1;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(map[i][j] == 2 && !visited[i][j]){
				visited[i][j] = true;
				spread(j, i, n, m);
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			(!map[i][j]) ? ret++ : 0;
		}
	}
	return ret;
}

void input(int &n, int &m)
{
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> lab[i][j];
			if(lab[i][j])
				picked[i*m+j] = true;
		}
	}
}

void print_pick(vector<vnode> &pick)
{
	int len = pick.size();
	for(int i=0; i<len; i++){
		cout << "(" << pick[i].x << ", " << pick[i].y << ")";
	}
	cout << endl;
}

void picking(int depth, int start, vector<vnode> &pick, int m, int n)
{
	if(depth == 3){
		// base case
		ans = max(ans, virus(n, m, pick));
		return;
	}
	int limit = n*m;
	for(int i=start; i<limit; i++){
		if(!picked[i]){
			picked[i] = true;
			pick.push_back(vnode(i%m, i/m));
			picking(depth+1, i+1, pick, m, n);
			picked[i] = false;
			pick.pop_back();
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n, m;
	input(n, m);
	vector<vnode> pick;
	picking(0, 0, pick, m, n);
	cout << ans << endl;
	return 0;
}
