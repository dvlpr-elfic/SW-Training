
/**
 * @author Jihoon Jang
 * 45 Minutes
 */

#include <iostream>
#include <algorithm>

#define MAP_SIZE 10

using namespace std;

int map[MAP_SIZE][MAP_SIZE];
bool visited[MAP_SIZE][MAP_SIZE];
int peak;
int ans;
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void travel(int depth, int x, int y, int n);
bool isWall(int x, int y, int n);
void solve(int n, int k);
void init(void);
void input(int &n, int &k);

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		int n, k;
		input(n, k);
		solve(n, k);
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void solve(int n, int k)
{
	for(int h=1; h<=k; h++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				map[i][j] -= h;
				for(int y=0; y<n; y++){
					for(int x=0; x<n; x++){
						if(map[y][x] == peak)
							travel(0, x, y, n);
					}
				}
				map[i][j] += h;
			}
		}
	}
}

void init(void)
{
	peak = ans = 0;
}


void travel(int depth, int x, int y, int n)
{
	bool base_case = true;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!isWall(nx, ny, n)){
			if(!visited[ny][nx] &&(map[y][x] > map[ny][nx])){
				base_case = false;
				visited[ny][nx] = true;
				travel(depth+1, nx, ny, n);
				visited[ny][nx] = false;				
			}
		}
	}
	if(base_case){
		// base case
		// 사방으로 갈 수 있는 곳이 없을 경우
		ans = max(ans, depth+1);
	}
}

void input(int &n, int &k)
{
	cin >> n >> k;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> map[i][j];
			if(peak < map[i][j])
				peak = map[i][j];
		}
	}
}