

#include <stdio.h>
#include <string.h>

#define MAX_MAP_SIZE 50
#define COVERED 'c'
#define UNCOVERED '.'

using namespace std;

char map[MAX_MAP_SIZE][MAX_MAP_SIZE];

int cover[4][3][2] = {
	{{0, 0}, {0, 1}, {1, 0}}, 
	{{0, 0}, {1, 0}, {1, -1}}, 
	{{0, 0}, {1, 0}, {1, 1}}, 
	{{0, 0}, {0, 1}, {1, 1}}};

void init(void)
{
	memset(map, 0, sizeof(map));
}

bool isWall(int x, int y, int max_row, int max_col)
{
	return (x<0 || y<0 || x>=max_row || y>=max_col);
}

void doCover(int cover[][2], int x, int y)
{
	for(int i=0; i<3; i++){
		int cx = cover[i][1] + x;
		int cy = cover[i][0] + y;
		map[cy][cx] = COVERED;
	}
}

void unCover(int cover[][2], int x, int y)
{
	for(int i=0; i<3; i++){
		int cx = cover[i][1] + x;
		int cy = cover[i][0] + y;
		map[cy][cx] = UNCOVERED;
	}
}

bool isCanCover(int cover[][2], int x, int y)
{
	for(int i=0; i<3; i ++){
		int cx = cover[i][1] + x;
		int cy = cover[i][0] + y;
		if(map[cy][cx] != '.')
			return false;
	}
	return true;
}

int dfs(int n_cover, int max_cover, int max_row, int max_col, int x, int y)
{
	if(n_cover == max_cover)
		return 1;
	bool dofor = true;
	int res = 0;
	for(int i=0; i<max_row && dofor; i++){
		for(int j=0; j<max_col && dofor; j++){
			if(map[i][j] == '.'){
				x = j, y = i;
				dofor = false;
			}
		}
	}
	for(int type=0; type<4; type++){
		if(isCanCover(cover[type], x, y)){
			doCover(cover[type], x, y);
			res += dfs(n_cover + 1, max_cover, max_row, max_col, x, y);
			unCover(cover[type], x, y);
		}
	}
	return res;
}


int main(void)
{
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);
	int C;
	scanf("%d", &C);
	for(int tc=1; tc<=C; tc++){
		init();
		int max_row, max_col, max_cover = 0;
		int ans;
		scanf("%d %d\n", &max_row, &max_col);
		for(int i=0; i<max_row; i++){
			for(int j=0; j<max_col; j++){
				char ch;
				while(1){
					ch = getchar();
					if(ch == '.' || ch == '#')
						break;
				}
				map[i][j] = ch;
				if(map[i][j] == '.')
					max_cover++;
			}
		}
		if(max_cover % 3){
			ans = 0;
		}
		else{
			max_cover /= 3;
			ans = dfs(0, max_cover, max_row, max_col, 0, 0);
		}
		//max_cover /= 3;
		//ans = dfs(0, max_cover, max_row, max_col, 0, 0);
		printf("%d\n", ans);
	}

	return 0;
}
