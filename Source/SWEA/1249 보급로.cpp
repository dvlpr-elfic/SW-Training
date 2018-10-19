
/**
 * @author : Jihoon Jang
 */

#include <stdio.h>
#include <queue>

#define MAX_MAP_SIZE 101
#define MAX_INT 0x7EEEEEEE

using namespace std;

int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

typedef struct element
{
	int x, y;
	element(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
}element;

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

bool isCanGo(int x, int y, int n)
{
	if(isWall(x, y, n))
		return false;
	else
		return true;
}

bool isMin(int x, int y, int nx, int ny, int map[][MAX_MAP_SIZE], int distance[][MAX_MAP_SIZE])
{
	return (distance[ny][nx] > distance[y][x] + map[ny][nx]);
}

void bfs(int map[][MAX_MAP_SIZE], queue<element> &q, int n, int distance[][MAX_MAP_SIZE])
{
	while(!q.empty()){
		int x = q.front().x;
		int y = q.front().y;
		q.pop();
		for(int type=0; type<4; type++){
			int nx = x + dx[type];
			int ny = y + dy[type];
			if(nx >= 0 && ny >= 0 && nx < n && ny < n){
				if(distance[ny][nx] > map[ny][nx] + distance[y][x]){
					distance[ny][nx] = map[ny][nx] + distance[y][x];
					q.push(element(nx, ny));
				}
			}
		}
	}
}


int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++){
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE] = {0, };
		int distance[MAX_MAP_SIZE][MAX_MAP_SIZE];
		int N;
		scanf("%d", &N);					// ют╥б
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				scanf("%1d", &map[i][j]);
				distance[i][j] = MAX_INT;
			}
		}
		distance[0][0] = 0;
		queue<element> q;
		q.push(element(0, 0));
		bfs(map, q, N, distance);
		int ans = distance[N-1][N-1];
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
