
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <memory.h>

using namespace std;

typedef struct qnode
{
	int x, y;
	qnode(int x, int y):x(x), y(y){}
}qnode;

char map[12][6];
bool visited[12][6];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(void)
{
	for(int y=0; y<12; y++){
		for(int x=0; x<6; x++){
			char ch;
			cin >> ch;
			if(ch == '.') continue;
			map[y][x] = ch;
		}
	}
}

bool isOut(int x, int y)
{
	return (x<0 || y<0 || x>=6 || y>=12);
}

int dfs(int x, int y, char color, queue<qnode> &tq)
{
	visited[y][x] = true;
	tq.push(qnode(x, y));
	int ret = 1;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isOut(nx, ny))	continue;
		if(!visited[ny][nx] && map[ny][nx] == color){
			ret += dfs(nx, ny, color, tq);
		}
	}
	return ret;
}

void temp2crash(queue<qnode> &tq, queue<qnode> &crashq)
{
	while(!tq.empty()){
		crashq.push(tq.front());	tq.pop();
	}
}

void floodfill(queue<qnode> &crashq)
{
	for(int y=0; y<12; y++){
		for(int x=0; x<6; x++){
			if(!visited[y][x] && map[y][x]){
				queue<qnode> tq;
				if(dfs(x, y, map[y][x], tq) >= 4){
					temp2crash(tq, crashq);
				}
			}
		}
	}
	memset(visited, 0, sizeof(visited));
}

void crash(queue<qnode> &q)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y;	q.pop();
		map[y][x] = 0;
	}
}

void sorting(void)
{
	for(int x=0; x<6; x++){
		int low = 11;
		for(int y=11; y>=0; y--){
			if(map[y][x]){
				char temp = map[y][x];
				map[y][x] = 0;
				map[low][x] = temp;
				low--;
			}
		}
	}
}

int solve(void)
{
	int ret = 0;
	while(1){
		queue<qnode> crashq;
		floodfill(crashq);
		if(crashq.empty())
			break;
		crash(crashq);
		sorting();
		ret++;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	input();
	cout << solve() << endl;
	return 0;
}

