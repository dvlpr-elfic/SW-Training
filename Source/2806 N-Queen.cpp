

#include <stdio.h>

#define MAX_N 11

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}


void putQueen(int check[][MAX_N], int row, int col, int N)
{
	for(int dir=0; dir<8; dir++){
		int x = col, y = row;
		while(1){
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if(isWall(nx, ny, N))
				break;
			check[ny][nx]++;
			x = nx, y = ny;
		}
	}
}

void deleteQueen(int check[][MAX_N], int row, int col, int N)
{
	for(int dir=0; dir<8; dir++){
		int x = col, y = row;
		while(1){
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if(isWall(nx, ny, N))
				break;
			check[ny][nx]--;
			x = nx, y = ny;
		}
	}
}



void dfs(int cnt, int *ans, int check[][MAX_N], int N)
{
	if(cnt == N){
		(*ans)++;
		return;
	}
	//for(int row=cnt; row<N; row++){
	int row = cnt;
	for(int col=0; col<N; col++){
		if(!check[row][col]){
			putQueen(check, row, col, N);
			dfs(cnt+1, ans, check, N);
			deleteQueen(check, row, col, N);
		}
	}
	//}
}

int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for(int tc=1; tc<=t; tc++){
		int N;
		int check[MAX_N][MAX_N] = {0, };
		scanf("%d", &N);
		int ans = 0;
		dfs(0, &ans, check, N);
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
