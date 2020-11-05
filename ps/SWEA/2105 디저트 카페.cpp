
/**
 * @author : Jihoon Jang
 */
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <memory.h>

#define MAP_SIZE 20
#define MAX 101

using namespace std;

int map[MAP_SIZE][MAP_SIZE];
bool road[MAP_SIZE][MAP_SIZE][MAP_SIZE][MAP_SIZE];
bool eaten[MAX];
int ans = 0;
int dx[] = {1, -1, -1, 1};
int dy[] = {1, 1, -1, -1};

void init(void)
{
	ans = -1;
}

void print(int n)
{
	cout << "---------------------------------------------------------------------" << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout.width(3);
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------" << endl;
}


bool isCorner(int x, int y, int n)
{
	return ((x == 0 || x == n-1) && (y == 0 || y == n-1));
}

bool isInErea(int x, int y, int n)
{
	return (x>=0 && y>=0 && x<n && y<n);
}

bool isCanGo(int x, int y, int nx, int ny, int n)
{
	if(isInErea(nx, ny, n))
		if(!isCorner(nx, ny, n))
			if(!eaten[map[ny][nx]])
				if(!road[x][y][nx][ny])
					return true;
	return false;
}

void travel(int depth, int x, int y, int s_x, int s_y, int dir, int n)
{
	if(dir >= 4)
		// error
		return;
	for(int i=dir; i<=dir+1; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(s_x == nx && s_y == ny){
			ans = max(ans, depth+2);
			return;
		}
		if(isCanGo(x, y, nx, ny, n)){
			eaten[map[ny][nx]] = true;
			road[x][y][nx][ny] = road[nx][ny][x][y] = true;
			travel(depth+1, nx, ny, s_x, s_y, i, n);
			eaten[map[ny][nx]] = false;
			road[x][y][nx][ny] = road[nx][ny][x][y] = false;
		}
	}
}

void solve(int n)
{
	for(int i=0; i<n-2; i++){
		for(int j=0; j<n; j++){
			if(!isCorner(j, i, n)){
				int x = j + dx[0];
				int y = i + dy[0];
				eaten[map[i][j]] = true;
				if(isCanGo(j, i, x, y, n)){
					eaten[map[y][x]] = true;
					road[j][i][y][x] = road[x][y][j][i] = true;
					travel(0, x, y, j, i, 0, n);
					eaten[map[y][x]] = false;
					road[j][i][y][x] = road[x][y][j][i] = false;
				}
				eaten[map[i][j]] = false;
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
		int n;
		cin >> n;
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				cin >> map[i][j];
		//if(tc == 6)
		//	print(n);
		solve(n);
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
