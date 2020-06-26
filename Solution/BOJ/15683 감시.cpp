
/**
 * @author : Jihoon Jang
 * 147 Minuites
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define MAP_SIZE 10

using namespace std;

typedef struct vnode
{
	int x, y;
	vnode(int _x, int _y)
	{
		x = _x, y = _y;
	}
}vnode;


int map[MAP_SIZE][MAP_SIZE] = {0, };
int visited[MAP_SIZE][MAP_SIZE] = {0, };
int cctv_num=0;
int ans = 987654231;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int cctv[] = {0, 4, 2, 4, 4, 1};

int counting(int n, int m)
{
	int res = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(!map[i][j] && !visited[i][j])
				res++;
		}
	}
	return res;
}

bool isWall(int x, int y, int n, int m)
{
	return (x<0 || y<0 || x>=m || y>=n);
}

void go(vector<vnode> &v, int x, int y, int dir, int n, int m)
{
	while(1){
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if(isWall(nx, ny, n, m))
			break;
		if(map[ny][nx] == 6)
			break;
		if(!(map[ny][nx] > 0 && map[ny][nx] < 6)){			// CCTV¸é ÆÐ½º
			//if(map[ny][nx] != 7){
				visited[ny][nx]++;
				v.push_back(vnode(nx, ny));
			//}
		}
		x = nx, y = ny;
	}
}

void marking(vector<vnode> &v, int x, int y, int cctv, int dir, int n, int m)
{
	switch(cctv){
	case 1:
		go(v, x, y, dir, n, m);
		break;
	case 2:
		go(v, x, y, dir, n, m);
		dir = (dir+2)%4;
		go(v, x, y, dir, n, m);
		break;
	case 3:
		go(v, x, y, dir, n, m);
		dir = (dir+1)%4;
		go(v, x, y, dir, n, m);
		break;
	case 4:
		go(v, x, y, dir, n, m);
		dir = (dir+1)%4;
		go(v, x, y, dir, n, m);
		dir = (dir+1)%4;
		go(v, x, y, dir, n, m);
		break;
	case 5:
		go(v, x, y, dir, n, m);
		dir = (dir+1)%4;
		go(v, x, y, dir, n, m);
		dir = (dir+1)%4;
		go(v, x, y, dir, n, m);
		dir = (dir+1)%4;
		go(v, x, y, dir, n, m);
		break;
	default:
		break;
	}
}

void unmarking(vector<vnode> &v)
{
	while(!v.empty()){
		int x = v.back().x, y = v.back().y;	v.pop_back();
		visited[y][x]--;
	}
}

void dfs(int depth, int n, int m, vector<vnode> *v, vector<vnode> &pos, int picked)
{
	if(depth == cctv_num){
		// base case
		ans = min(ans, counting(n, m));
		return;
	}

	int i = picked+1;
	int x = pos[i].x, y = pos[i].y;
	int type = map[y][x];
	int max = cctv[type];
	for(int t=0; t<max; t++){
		marking(v[depth], x, y, type, t, n, m);
		dfs(depth+1, n, m, v, pos, i);
		unmarking(v[depth]);
	}

}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int n, m;
	cin >> n >> m;
	vector<vnode> v[8];
	vector<vnode> pos;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int temp;
			cin >> temp;
			if(temp > 0 && temp < 6){
				pos.push_back(vnode(j, i));
				cctv_num++;
			}
			map[i][j] = temp;
		}
	}
	dfs(0, n, m, v, pos, -1);
	cout << ans << endl;
	return 0;
}
