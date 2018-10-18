
/**
 * @author : Jihoon Jang
 */

#include <iostream>
#include <memory.h>
#include <vector>

#define MAP_SIZE 200

using namespace std;

typedef struct Dragon
{
	vector<int> curve;
	int x, y;
	Dragon(void)
	{
		x = 0, y = 0;
	}
}Dragon;


bool map[MAP_SIZE][MAP_SIZE];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

int changeDir(int dir)
{
	return ((dir+1)%4);
}

void createDragonCurve(Dragon &dragon, int x, int y, int d, int g)
{
	map[y][x] = true;
	dragon.curve.push_back(d);
	dragon.x = x + dx[d], dragon.y = y + dy[d];
	map[dragon.y][dragon.x] = true;
	while(g--){
		int len = dragon.curve.size();
		for(int i=len-1; i>=0; i--){
			int dir = changeDir(dragon.curve[i]);
			dragon.curve.push_back(dir);
			int nx = dragon.x + dx[dir];
			int ny = dragon.y + dy[dir];
			map[ny][nx] = true;
			dragon.x = nx, dragon.y = ny;
		}
	}
}

bool isSquare(int x, int y)
{
	return (map[y][x] && map[y+1][x] && map[y][x+1] && map[y+1][x+1]);
}

int solve(void)
{
	int res = 0;
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			if(isSquare(j, i))
				res++;
		}
	}
	return res;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	memset(map, 0, sizeof(map));
	for(int i=0; i<n; i++){
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		Dragon dragon;
		createDragonCurve(dragon, x, y, d, g);
	}
	int ans = solve();
	cout << ans << endl;

	return 0;
}
