
/**
  * @author Jihoon Jang
  * 67min
  */

#include <iostream>
#include <queue>
#include <memory.h>
#include <algorithm>

#define SIZE 1001
#define INF 0x7FFFFFFF

using namespace std;

typedef struct qnode
{
	int x, y, level;
	qnode(int x, int y, int l):x(x), y(y), level(l){}
}qnode;

bool visited[SIZE][SIZE];
bool wall[SIZE][SIZE];
int fire[SIZE][SIZE];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void input(int &h, int &w, queue<qnode> &jhq, queue<qnode> &fireq)
{
	cin >> h >> w;
	memset(fire, 0x7F, sizeof(fire));
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			char ch;
			cin >> ch;
			if(ch == '#'){
				wall[y][x] = true;
			}
			else if(ch == 'J'){
				jhq.push(qnode(x, y, 0));
			}
			else if(ch == 'F'){
				fireq.push(qnode(x, y, 0));
			}
		}
	}
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

void setFireRoute(queue<qnode> &q, int h, int w)
{
	if(!q.empty())
		visited[q.front().y][q.front().x] = true;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, level = q.front().level;	q.pop();
		fire[y][x] = level;
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isOut(nx, ny, h, w))
				continue;
			if(!wall[ny][nx] && !visited[ny][nx]){
				visited[ny][nx] = true;
				q.push(qnode(nx, ny, level+1));
			}
		}
	}
}

void escape(int h, int w, queue<qnode> &q)
{
	memset(visited, 0, sizeof(visited));
	if(!q.empty())
		visited[q.front().y][q.front().x] = true;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, level = q.front().level;	q.pop();
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isOut(nx, ny, h, w)){
				cout << level+1 << endl;
				return;
			}
			if(!wall[ny][nx] && !visited[ny][nx]){
				visited[ny][nx] = true;
				if((level+1) < fire[ny][nx]){
					q.push(qnode(nx, ny, level+1));
				}
			}
		}
	}
	cout << "IMPOSSIBLE\n";
}

void solve(int h, int w, queue<qnode> &fireq, queue<qnode> &jhq)
{
	setFireRoute(fireq, h, w);
	escape(h, w, jhq);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int h, w;
	queue<qnode> jhq, fireq;
	input(h, w, jhq, fireq);
	solve(h, w, fireq, jhq);
	return 0;
}

