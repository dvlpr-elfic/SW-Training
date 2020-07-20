
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 251
#define SHEEP 'o'
#define WOLF 'v'
#define WALL '#'

using namespace std;

char map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void input(int &n, int &m, int &sheep, int &wolf)
{
	cin >> n >> m;
	for(int y=0; y<n; y++){
		for(int x=0; x<m; x++){
			cin >> map[y][x];
			if(map[y][x] == SHEEP)
				sheep++;
			else if(map[y][x] == WOLF)
				wolf++;
		}
	}
}

bool isInArea(int x, int y, int n, int m)
{
	return (x>=0 && y>=0 && x<m && y<n);
}

void dfs(int x, int y, int n, int m, int &o, int &v)
{
	visited[y][x] = true;
	if(map[y][x] == SHEEP)
		o++;
	else if(map[y][x] == WOLF)
		v++;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!isInArea(nx, ny, n, m))
			continue;
		if(!visited[ny][nx] && map[ny][nx] != WALL){
			dfs(nx, ny, n, m, o, v);
		}
	}
}

void solve(int n, int m, int &wolf, int &sheep)
{
	for(int y=0; y<n; y++){
		for(int x=0; x<m; x++){
			if(!visited[y][x] && map[y][x] != WALL){
				int o=0, v=0;
				dfs(x, y, n, m, o, v);
				if(o > v)
					wolf -= v;
				else
					sheep -= o;
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, m, sheep=0, wolf=0;
	input(n, m, sheep, wolf);
	solve(n, m, wolf, sheep);
	cout << sheep << ' ' << wolf << endl;
	return 0;
}

