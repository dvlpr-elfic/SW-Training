
#include <iostream>
#include <memory.h>
#include <algorithm>

#define MAP_SIZE 100


using namespace std;

typedef struct PinBall
{
	int x, y, dir, point;
	PinBall(void)
	{
		x = y = dir = point = 0;
	}
}PinBall;

typedef struct Pos
{
	int x, y;
}Pos;

int map[MAP_SIZE][MAP_SIZE];
int block[6][4] = {{0, }, {2, 3, 1, 0}, {1, 3, 0, 2}, {3, 2, 0, 1}, {2, 0, 3, 1}, {2, 3, 0, 1}};
Pos wormhole[11][2];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int ans = 0;

void init(void)
{
	ans = 0;
	memset(wormhole, 0, sizeof(wormhole));
}


void input(int &n)
{
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> map[i][j];
			if(map[i][j] >= 6 && map[i][j] <= 10){
				if(wormhole[map[i][j]][0].x == 0 && wormhole[map[i][j]][0].y == 0)
					wormhole[map[i][j]][0].x = j, wormhole[map[i][j]][0].y = i;
				else
					wormhole[map[i][j]][1].x = j, wormhole[map[i][j]][1].y = i;
			}
		}
	}
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void goStraight(PinBall &pb)
{
	pb.x += dx[pb.dir], pb.y += dy[pb.dir];	// ม๘วเ
}

void changeDir(PinBall &pb, int block_num)
{
	pb.dir = block[block_num][pb.dir];
}

void getPoint(PinBall &pb)
{
	pb.point++;
}

bool isBlackHole(PinBall &pb)
{
	return (map[pb.y][pb.x] == -1);
}

bool isStartPoint(PinBall &pb, int s_x, int s_y)
{
	return (pb.x == s_x && pb.y == s_y);
}

bool isThereWormHole(PinBall &pb)
{
	return (map[pb.y][pb.x] >= 6 && map[pb.y][pb.x] <= 10);
}

void moveToLinkedHole(PinBall &pb)
{
	int n = map[pb.y][pb.x];
	if(wormhole[n][0].x == pb.x && wormhole[n][0].y == pb.y){
		pb.x = wormhole[n][1].x, pb.y = wormhole[n][1].y;
	}
	else
		pb.x = wormhole[n][0].x, pb.y = wormhole[n][0].y;
}

bool isThereBlock(PinBall &pb)
{
	return (map[pb.y][pb.x] >= 1 && map[pb.y][pb.x] <= 5);
}

void travel(PinBall &pb, int n, int x, int y)
{
	goStraight(pb);
	while(1){
		if(isBlackHole(pb) || isStartPoint(pb, x, y))
			break;
		else if(isWall(pb.x, pb.y, n)){
			getPoint(pb);
			changeDir(pb, 5);
			goStraight(pb);
			continue;
		}
		else if(isThereWormHole(pb)){
			moveToLinkedHole(pb);
			goStraight(pb);
			continue;
		}
		else if(isThereBlock(pb)){
			getPoint(pb);
			changeDir(pb, map[pb.y][pb.x]);
			goStraight(pb);
			continue;
		}
		goStraight(pb);
	}
	ans = max(ans, pb.point);
}

void solve(PinBall &pb, int n)
{
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(map[i][j])
				continue;
			for(int dir=0; dir<4; dir++){
				pb.x = j, pb.y = i;
				pb.dir = dir;
				pb.point = 0;
				travel(pb, n, j, i);
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
		input(n);
		PinBall pb;
		solve(pb, n);
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
