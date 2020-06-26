
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 40

using namespace std;

int map[SIZE][SIZE];

void putLine(int x, int y)
{
	map[y][x] = x+1;
}

void input(int &h, int &w)
{
	int n;
	cin >> w >> n >> h;
	for(int i=0; i<n; i++){
		int x, y;
		cin >> y >> x;
		putLine(x, y);
	}
}

void eraseLine(int x, int y)
{
	map[y][x] = 0;
}

int followLine(int x, int y, int h)
{
	while(y <= h){
		if(map[y][x]){
			x = x+1;
			y++;
		}
		else if(map[y][x-1]){
			x = x-1;
			y++;
		}
		else{
			y++;
		}
	}
	return x;
}

bool simulation(int h, int w)
{
	for(int s=1; s<=w; s++){
		if(followLine(s, 1, h) != s)
			return false;
	}
	return true;
}

bool isCanPutLine(int x, int y)
{
	return (!map[y][x] && !map[y][x+1] && map[y][x-1] != x);
}

bool dfs(int depth, int n, int h, int w, int _x, int _y)
{
	if(depth == n){
		return simulation(h, w);
	}
	bool ret = false;
	int x = _x;
	for(int y=_y; y<=h; y++){
		for( ; x<w; x++){
			if(x == _x && y == _y)
				continue;
			if(!isCanPutLine(x, y))
				continue;
			putLine(x, y);
			ret |= dfs(depth+1, n, h, w, x, y);
			eraseLine(x, y);
		}
		x = 0;
	}
	return ret;
}

int solve(int h, int w)
{
	for(int ret=0; ret<=3; ret++){
		if(dfs(0, ret, h, w, 0, 1))
			return ret;
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int h, w;
	input(h, w);
	cout << solve(h, w) << '\n';
	return 0;
}

