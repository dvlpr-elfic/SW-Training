
/**
  * @author Jihoon Jang
  * 73 min
  */

#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>

#define SIZE 9
#define INF 0x3FFFFFFF

using namespace std;

typedef struct cnode
{
	int x, y, n;
	cnode(int x, int y, int n):x(x), y(y), n(n){}
}cnode;

bool wall[SIZE][SIZE];
bool visited[SIZE][SIZE];
int cctvmap[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void setLib(vector<vector<vector<int>>> &lib)
{
	int i;
	lib.resize(6);
	lib[1].resize(4);
	for(i=0; i<4; i++){
		lib[1][i].push_back(i);
	}
	lib[2].resize(2);
	for(i=0; i<2; i++){
		lib[2][i].resize(2);
		lib[2][i][0] = i;
		lib[2][i][1] = i+2;
	}
	lib[3].resize(4);
	for(i=0; i<4; i++){
		lib[3][i].resize(2);
		lib[3][i][0] = i;
		lib[3][i][1] = (i+1)%4;
	}
	lib[4].resize(4);
	for(i=0; i<4; i++){
		lib[4][i].resize(3);
		lib[4][i][0] = i;
		lib[4][i][1] = (i+1)%4;
		lib[4][i][2] = (i+2)%4;
	}
	lib[5].resize(1);
	for(i=0; i<4; i++)
		lib[5][0].push_back(i);
}

void input(int &h, int &w, int &cnt, vector<cnode> &cctv)
{
	cin >> h >> w;
	cnt = h*w;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			int temp;
			cin >> temp;
			if(temp >= 1 && temp <= 5){
				cctv.push_back(cnode(x, y, temp));
				cctvmap[y][x] = temp;
				cnt--;
			}
			else if(temp == 6){
				wall[y][x] = true;
				cnt--;
			}
		}
	}
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

bool isWall(int x, int y)
{
	return wall[y][x];
}

void _move(int &cnt, int dir, int x, int y, int h, int w)
{
	visited[y][x] = true;
	int nx = x, ny = y;
	while(1){
		nx += dx[dir];
		ny += dy[dir];
		if(isOut(nx, ny, h, w))
			break;
		if(isWall(nx, ny))
			break;
		if(!visited[ny][nx] && !cctvmap[ny][nx]){
			visited[ny][nx] = true;
			cnt--;
		}
	}
}

int simulation(int h, int w, vector<cnode> &cctv, vector<int> &type, int cnt, vector<vector<vector<int>>> &lib)
{
	memset(visited, 0, sizeof(visited));
	for(int i=0; i<cctv.size(); i++){
		int x = cctv[i].x, y = cctv[i].y, n = cctv[i].n, curtype = type[i];
		for(int j=0; j<lib[n][curtype].size(); j++){
			int dir = lib[n][curtype][j];
			_move(cnt, dir, x, y, h, w);
		}
	}
	return cnt;
}

int solve(int depth, int h, int w, int cnt, vector<cnode> &cctv, vector<int> &type, vector<vector<vector<int>>> &lib)
{
	if(depth == cctv.size()){
		return simulation(h, w, cctv, type, cnt, lib);
	}
	int ret = INF;
	for(int i=0; i<lib[cctv[depth].n].size(); i++){
		type.push_back(i);
		ret = min(ret, solve(depth+1, h, w, cnt, cctv, type, lib));
		type.pop_back();
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	vector<vector<vector<int>>> lib;
	setLib(lib);
	int h, w, cnt;
	vector<cnode> cctv;
	vector<int> type;
	input(h, w, cnt, cctv);
	cout << solve(0, h, w, cnt, cctv, type, lib);
	return 0;
}

