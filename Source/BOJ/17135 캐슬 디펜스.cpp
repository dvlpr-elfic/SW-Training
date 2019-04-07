
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>
#include <queue>
#include <algorithm>

#define SIZE 20

using namespace std;

typedef struct node
{
	int x, y, dist;
	node(int x, int y, int d):x(x), y(y), dist(d){}
}node;

int map[SIZE][SIZE];
int board[SIZE][SIZE];
bool visited[SIZE][SIZE];
int hunter[3];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &h, int &w, int &d, int &cnt)
{
	cin >> h >> w >> d;
	cnt = 0;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			cin >> map[y][x];
			if(map[y][x])
				cnt++;
		}
	}
}

void _copy(void)
{
	memcpy(board, map, sizeof(map));
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || y>=h || x>=w);
}

bool compare(const node &n1, const node &n2)
{
	if(n1.dist == n2.dist){
		return (n1.x < n2.x);
	}
	else
		return (n1.dist < n2.dist);
}

int attack(int &cnt, int h, int w, int d)
{
	int ret = 0;
	vector<node> victim[3];
	for(int i=0; i<3; i++){
		queue<node> q;
		visited[h-1][hunter[i]] = true;
		q.push(node(hunter[i], h-1, 1));
		while(!q.empty()){
			int x = q.front().x, y = q.front().y, dist = q.front().dist;	q.pop();
			if(board[y][x])
				victim[i].push_back(node(x, y, dist));
			for(int dir=0; dir<4; dir++){
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				if(isOut(nx, ny, h, w))	continue;
				if(!visited[ny][nx] && (d >= dist+1)){
					visited[ny][nx] = true;
					q.push(node(nx, ny, dist+1));
				}
			}
		}
		memset(visited, 0, sizeof(visited));
		sort(victim[i].begin(), victim[i].end(), compare);
	}
	for(int i=0; i<3; i++){
		if(victim[i].empty())
			continue;
		int x = victim[i][0].x, y = victim[i][0].y;
		if(board[y][x]){
			board[y][x] = 0;
			cnt--, ret++;
		}
	}
	return ret;
}

void _move(int h, int w, int &cnt)
{
	for(int x=0; x<w; x++){
		if(board[h-1][x]){
			cnt--;
			board[h-1][x] = 0;
		}
	}
	for(int y=h-2; y>=0; y--){
		for(int x=0; x<w; x++){
			if(board[y][x]){
				board[y][x] = 0;
				board[y+1][x] = 1;
			}
		}
	}
}

int simulation(int cnt, int h, int w, int d)
{
	_copy();
	int ret = 0;
	while(cnt){
		ret += attack(cnt, h, w, d);
		_move(h, w, cnt);
	}
	return ret;
}

int solve(int depth, int n, int r, int s, int cnt, int h, int w, int d)
{
	if(depth == r){
		// base case
		return simulation(cnt, h, w, d);
	}
	int ret = 0;
	int limit = (n-1) - (r-1-depth);
	for(int i=s; i<=limit; i++){
		hunter[depth] = i;
		ret = max(ret, solve(depth+1, n, r, i+1, cnt, h, w, d));
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int h, w, d, cnt;
	input(h, w, d, cnt);
	cout << solve(0, w, 3, 0, cnt, h, w, d);
	return 0;
}

