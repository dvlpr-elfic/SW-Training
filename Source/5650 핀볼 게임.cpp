

#include <iostream>
#include <string.h>

#define MAX_MAP 102

using namespace std;

typedef struct wormhole
{
	int x, y;
	int size;
}wormhole;

typedef struct pinball
{
	int x, y;
}pinball;

int map[MAX_MAP][MAX_MAP];
int block_dir[6][4] = {{0, }, {2, 3, 1, 0}, {1, 3, 0, 2}, {3, 2, 0, 1}, {2, 0, 3, 1}, {2, 3, 0, 1}};
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
wormhole wh[2][11];
int ans = 0;

void init(void)
{
	memset(map, 0, sizeof(map));
	memset(wh, 0, sizeof(wh));
	ans = 0;
}

bool isBlackHole(int x, int y)
{
	return (map[y][x] == -1);
}

bool isOriginPos(int x1, int y1, int x2, int y2)
{
	return (x1 == x2 && y1 == y2);
}

bool isBlock(int x, int y)
{
	return (map[y][x] > 0 && map[y][x] < 6);
}

void changeDirection(int &dir, int x, int y)
{
	dir = block_dir[map[y][x]][dir];
}

bool isWormHole(int x, int y)
{
	return (map[y][x] > 5 && map[y][x] < 11);
}

void changePos(int &x, int &y)
{
	int i = y, j = x;
	if(wh[0][map[i][j]].x == j && wh[0][map[i][j]].y == i)
		x = wh[1][map[i][j]].x, y = wh[1][map[i][j]].y;
	else if(wh[1][map[i][j]].x == j && wh[1][map[i][j]].y == i)
		x = wh[0][map[i][j]].x, y = wh[0][map[i][j]].y;
	else
		cout << "change pos error" << endl;
}

void goNextStep(pinball &pb, int dir)
{
	pb.x += dx[dir], pb.y += dy[dir];
}


void travel(int x, int y, int direction)
{
	pinball pb = {x, y};
	int dir = direction;
	int count = 0;
	do{
		int cur = map[pb.y][pb.x];
		if(cur > 0){
			if(isBlock(pb.x, pb.y)){
				changeDirection(dir, pb.x, pb.y);
				count++;
				goNextStep(pb, dir);
			}
			else if(isWormHole(pb.x, pb.y)){
				changePos(pb.x, pb.y);
				goNextStep(pb, dir);
			}
			else
				cout << "error in travel" << endl;
		}
		else if(cur == 0){
			goNextStep(pb, dir);
		}
	}while(!isBlackHole(pb.x, pb.y) && !isOriginPos(x, y, pb.x, pb.y));

	if(ans < count)
		ans = count;
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
		for(int i=0; i<=n+1; i++){
			for(int j=0; j<=n+1; j++){
				if(i==0 || j==0 || i == n+1 || j == n+1){
					map[i][j] = 5;
				}
				else{
					cin >> map[i][j];
					if(isWormHole(j, i)){
						if(wh[0][map[i][j]].x && wh[0][map[i][j]].y)
							wh[1][map[i][j]].x = j, wh[1][map[i][j]].y = i;
						else
							wh[0][map[i][j]].x = j, wh[0][map[i][j]].y = i;
					}
				}
			}
		}
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				if(!map[i][j])
					for(int d=0; d<4; d++)
						travel(j, i, d);
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
