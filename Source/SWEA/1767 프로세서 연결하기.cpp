
/**
 * @author : Jihoon Jang
 */


#include <iostream>
#include <vector>
#include <memory.h>

#define MAP_SIZE 12

using namespace std;

typedef struct vnode
{
	int x, y;
	vnode(int x, int y):x(x), y(y){}
}vnode;


int map[MAP_SIZE][MAP_SIZE];
bool check[MAP_SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int line, cnt, maximum, minimum;

void init(void)
{
	line = cnt = maximum = 0;
	minimum = 987654321;
	memset(check, 0, sizeof(check));
}


bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

bool isCanConnect(vector<vnode> &v, int dir, int map_size, int processor)
{
	int x = v[processor].x + dx[dir], y = v[processor].y + dy[dir];
	while(!isWall(x, y, map_size)){
		if(map[y][x])
			return false;
		x += dx[dir];
		y += dy[dir];
	}
	return true;
}

void doConnect(vector<vnode> &v, int dir, int map_size, int processor)
{
	int x = v[processor].x + dx[dir], y = v[processor].y + dy[dir];
	while(!isWall(x, y, map_size)){
		map[y][x] += 2;
		line++;
		x += dx[dir];
		y += dy[dir];
	}
	cnt++;
}

void unConnect(vector<vnode> &v, int dir, int map_size, int processor)
{
	int x = v[processor].x + dx[dir], y = v[processor].y + dy[dir];
	while(!isWall(x, y, map_size)){
		map[y][x] -= 2;
		line--;
		x += dx[dir];
		y += dy[dir];
	}
	cnt--;
}

void dfs(int depth, int processor, int n, vector<vnode> &v, int map_size)
{
	if(depth == n){
		if(maximum == cnt){
			if(minimum > line){
				minimum = line;
			}
		}
		else if(maximum < cnt){
			minimum = line;
			maximum = cnt;
		}
		return;
	}
	for(int dir=0; dir<4; dir++){
		if(isCanConnect(v, dir, map_size, processor)){
			doConnect(v, dir, map_size, processor);
			dfs(depth+1, processor+1, n, v, map_size);
			unConnect(v, dir, map_size, processor);
		}
	}
	dfs(depth+1, processor+1, n, v, map_size);
}

void input(int &map_size, vector<vnode> &v)
{
	cin >> map_size;
	for(int i=0; i<map_size; i++){
		for(int j=0; j<map_size; j++){
			cin >> map[i][j];
			if(map[i][j]){
				if(i == 0 || i == map_size-1 || j == 0 || j == map_size-1)
					continue;
				v.push_back(vnode(j, i));
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
		int map_size;
		vector<vnode> v;
		input(map_size, v);
		dfs(0, 0, v.size(), v, map_size);
		cout << "#" << tc << " " << minimum << endl;
	}

	return 0;
}
