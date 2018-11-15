
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>

#define MAP_SIZE 30

using namespace std;

int map[MAP_SIZE][MAP_SIZE];
int dx[][3] = {{0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {0, -1, 0}};
int dy[][3] = {{0, 1, 1}, {0, 0, 1}, {0, 0, 1}, {0, 1, 1}};

int cnt;

void init(void)
{
	cnt = 0;
	memset(map, 0, sizeof(map));
}


bool isWall(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

bool isCanCover(int x, int y, int type, int h, int w)
{
	for(int i=0; i<3; i++){
		int nx = x + dx[type][i];
		int ny = y + dy[type][i];
		if(isWall(nx, ny, h, w))
			return false;
		if(map[ny][nx])
			return false;
	}
	return true;
}

void doCover(int x, int y, int type)
{
	for(int i=0; i<3; i++){
		int nx = x + dx[type][i];
		int ny = y + dy[type][i];
		map[ny][nx] = 1;
	}
}

void unCover(int x, int y, int type)
{
	for(int i=0; i<3; i++){
		int nx = x + dx[type][i];
		int ny = y + dy[type][i];
		map[ny][nx] = 0;
	}
}

void backtrack(int depth, int n, int h, int w)
{
	if(depth == n){
		// base case
		cnt++;
		return;
	}
	bool for_flag = true;
	int x, y;
	for(int i=0; i<h && for_flag; i++){
		for(int j=0; j<w && for_flag; j++){
			if(!map[i][j]){
				x = j, y = i;
				for_flag = false;
			}
		}
	}

	for(int type=0; type<4; type++){
		if(isCanCover(x, y, type, h, w)){
			doCover(x, y, type);
			backtrack(depth+1, n, h, w);
			unCover(x, y, type);
		}
	}
}


int main(void)
{
	int t;
	//freopen("input.txt", "r", stdin);
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		int h, w;
		cin >> h >> w;
		int n = h*w;
		for(int y=0; y<h; y++){
			for(int x=0; x<w; x++){
				char temp;
				cin >> temp;
				temp == '#' ? (map[y][x] = 1, n--) : map[y][x] = 0;
			}
		}
		if(n % 3 != 0){
			cout << cnt << endl;
			continue;
		}
		n /= 3;
		backtrack(0, n, h, w);
		cout << cnt << endl;
	}

	return 0;
}
