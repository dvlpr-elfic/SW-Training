
#include <iostream>
#include <memory.h>

#define MAP_SIZE 100

using namespace std;

int dx[] = {-1, 1, 0};
int dy[] = {0, 0, -1};
int map[MAP_SIZE][MAP_SIZE];
bool visited[MAP_SIZE][MAP_SIZE];
int s_x, s_y;

void init(void)
{
	s_x = s_y = 0;
	memset(visited, 0, sizeof(visited));
}

bool isWall(int x, int y)
{
	return (x<0 || y<0 || x>=MAP_SIZE || y>=MAP_SIZE);
}


void input(void)
{
	int temp;
	cin >> temp;
	for(int i=0; i<MAP_SIZE; i++){
		for(int j=0; j<MAP_SIZE; j++){
			cin >> map[i][j];
			if(map[i][j] == 2){
				s_x = j, s_y = i;
			}
		}
	}
}

int travel(void)
{
	int x = s_x, y = s_y;
	visited[y][x] = true;
	while(1){
		if(y == 0){
			return x;
		}
		for(int i=0; i<3; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(!isWall(nx, ny)){
				if(map[ny][nx] && !visited[ny][nx]){
					x = nx, y = ny, visited[ny][nx] = true;
					continue;
				}
			}
		}
	}

}



int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		init();
		input();
		cout << "#" << tc << " " << travel() << endl;
	}
	return 0;
}
