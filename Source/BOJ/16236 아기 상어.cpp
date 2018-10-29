
/**
 * @author : Jihoon Jang
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>

#define MAP_SIZE 21

using namespace std;

typedef struct Shark
{
	int x, y, time, eated, size;
	Shark(void):x(0), y(0), time(0), eated(0), size(2){}
}Shark;

typedef struct vnode
{
	int x, y, t;
	vnode(int x, int y, int t):x(x), y(y), t(t){}
	vnode(void):x(0), y(0), t(0){}
}vnode;

typedef struct qnode
{
	int x, y, t;
	qnode(int x, int y, int t):x(x), y(y), t(t){}
}qnode;

int map[MAP_SIZE][MAP_SIZE];
bool visited[MAP_SIZE][MAP_SIZE];
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

void print(int n)
{
	cout << "----------------------------------------------------------------------------" << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout.width(3);
			visited[i][j] ? cout << 1 : cout << 0;
		}
		cout << endl;
	}
	cout << "----------------------------------------------------------------------------" << endl;
}


bool cmp_upper(const vnode& n1, const vnode& n2)
{
	if(n1.y == n2.y){
		return n1.x < n2.x;
	}
	return n1.y < n2.y;
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void pick(int &x, int &y, int &t, vector<vnode> &v)
{
	sort(v.begin(), v.end(), cmp_upper);
	x = v[0].x, y = v[0].y, t = v[0].t;
}

void moveShark(int x, int y, int nx, int ny, int t, Shark &shark)
{
	map[ny][nx] = 0;
	shark.time += t;
	shark.x = nx, shark.y = ny;
}

void searchFish(vector<vnode> &v, int sx, int sy, int n, Shark &shark)
{
	queue<qnode> q;
	q.push(qnode(sx, sy, 0));
	visited[sy][sx] = true;
	while(v.empty() && !q.empty()){
		int len = q.size();
		for(int i=0; i<len; i++){
			int x = q.front().x, y = q.front().y, t = q.front().t;	q.pop();
			if(map[y][x] < shark.size && map[y][x]){
				v.push_back(vnode(x, y, t));
			}
			for(int i=0; i<4; i++){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if(!isWall(nx, ny, n)){
					if((map[ny][nx] <= shark.size || !map[ny][nx]) && !visited[ny][nx]){
						visited[ny][nx] = true;
						q.push(qnode(nx, ny, t+1));
					}
				}
			}
		}
	}
	memset(visited, 0, sizeof(visited));
}

void eating(Shark &shark, int n)
{
	int sx = shark.x, sy = shark.y;
	while(1){
		vector<vnode> v;
		searchFish(v, sx, sy, n, shark);
		if(v.empty()){
			break;
		}
		int x, y, t;
		pick(x, y, t, v);
		moveShark(sx, sy, x, y, t, shark);
		shark.eated++;
		if(shark.eated >= shark.size)
			shark.eated = 0, shark.size++;
		sx = shark.x, sy = shark.y;
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	Shark shark;
	for(int i=0; i<n; i++){				// input
		for(int j=0; j<n; j++){
			cin >> map[i][j];
			if(map[i][j] == 9){
				shark.x = j, shark.y = i;
				map[i][j] = 0;
			}
		}
	}
	eating(shark, n);
	cout << shark.time << endl;
	return 0;
}
