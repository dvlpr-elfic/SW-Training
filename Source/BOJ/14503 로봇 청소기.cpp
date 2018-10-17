

#include <iostream>

#define MAP_SIZE 60

using namespace std;

typedef struct Robot
{
	int x, y, dir;
	Robot(void)
	{
		x = 0, y = 0, dir = 0;
	}
}Robot;


int map[MAP_SIZE][MAP_SIZE];
int visited[MAP_SIZE][MAP_SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
int n, m;

bool isCanGoBack(Robot &robot)
{
	int dir = (robot.dir+2)%4;
	int x = robot.x + dx[dir], y = robot.y + dy[dir];
	return (!map[y][x]);
}

void GoBack(Robot &robot)
{
	int dir = (robot.dir+2)%4;
	robot.x = robot.x + dx[dir], robot.y = robot.y + dy[dir];
}

bool isCleanedLeft(Robot &robot)
{
	int dir = (robot.dir+3)%4;
	int x = robot.x + dx[dir], y = robot.y + dy[dir];
	return visited[y][x];
}

void DoClean(Robot &robot)
{
	int dir = (robot.dir + 3)%4;
	robot.x = robot.x + dx[dir], robot.y = robot.y + dy[dir], robot.dir = dir;
}

void print(void)
{
	cout << "-----------------------------------------------------------------------------------" << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cout.width(3);
			cout << visited[i][j];
		}
		cout << endl;
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
}


int cleaning(Robot &robot)
{
	int cnt = 0;
	while(1){
		int x = robot.x, y = robot.y;
		if(map[y][x])
			// error
			return 0;
		if(!visited[y][x])
			cnt++, visited[y][x] = 1;
		//print();
		if(visited[y+1][x] && visited[y-1][x] && visited[y][x+1] && visited[y][x-1]){
			if(!isCanGoBack(robot))
				break;
			GoBack(robot);
			continue;
		}
		if(!isCleanedLeft(robot)){
			DoClean(robot);
			continue;
		}
		robot.dir = (robot.dir+3)%4;
	}
	return cnt;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	Robot robot;
	cin >> n >> m >> robot.y >> robot.x >> robot.dir;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> map[i][j];
			visited[i][j] = map[i][j];
		}
	}
	int ans = cleaning(robot);
	cout << ans << endl;
	
	return 0;
}
