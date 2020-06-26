
/**
  * @author Jihoon Jang
  * Time : 20min
  */

#include <iostream>
#include <memory.h>

#define SIZE 200

using namespace std;

char map[2][SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void dfs(int x, int y, int n, char color, int person)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n))
			continue;
		if(!visited[ny][nx] && map[person][ny][nx] == color){
			visited[ny][nx] = true;
			dfs(nx, ny, n, color, person);
		}
	}
}

int travel(int n, int person)
{
	int ret = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(!visited[y][x]){
				visited[y][x] = true;
				dfs(x, y, n, map[person][y][x], person);
				ret++;
			}
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n;
	cin >> n;									// input
	for(int i=0; i<n; i++){						// set map
		for(int j=0; j<n; j++){
			cin >> map[0][i][j];
			if(map[0][i][j] == 'R')
				map[1][i][j] = 'G';
			else
				map[1][i][j] = map[0][i][j];
		}
	}
	int normal = travel(n, 0);
	memset(visited, 0, sizeof(visited));
	int color_weakness = travel(n, 1);
	cout << normal << " " << color_weakness << '\n';
	return 0;
}
