
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define SIZE 101

using namespace std;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

int max(int a, int b)
{
	if(a>b)
		return a;
	else
		return b;
}

void input(int &n, int &max_height)
{
	cin >> n;
	max_height = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> map[y][x];
			max_height = max(max_height, map[y][x]);
		}
	}
}

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void floodfill(int x, int y, int h, int n)
{
	visited[y][x] = true;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny, n))	continue;
		if(!visited[ny][nx] && map[ny][nx] > h){
			floodfill(nx, ny, h, n);
		}
	}
}

int counting(int n, int h)
{
	int ret = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(!visited[y][x] && map[y][x] > h){
				floodfill(x, y, h, n);
				ret++;
			}
		}
	}
	return ret;
}

void memsett(void* ptr, int val, int size)
{
	char *p = (char*)ptr;
	for(int i=0; i<size; i++){
		p[i] = val;
	}
}

int solve(int n, int max_height)
{
	int ret = 0;
	for(int h=max_height; h>=0; h--){
		memsett(visited, 0, sizeof(visited));
		ret = max(ret, counting(n, h));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, max_height;
	input(n, max_height);
	cout << solve(n, max_height) << '\n';
	return 0;
}

