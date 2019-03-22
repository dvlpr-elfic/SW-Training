
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <algorithm>

#define SIZE 101

using namespace std;

typedef struct qnode
{
	int x, y;
	qnode(int x, int y):x(x), y(y){}
}qnode;

int map[2][SIZE][SIZE];
bool road[2][SIZE][SIZE];

void input(int &n, int &len)
{
	cin >> n >> len;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			int temp;
			cin >> temp;
			map[0][y][x] = map[1][x][y] = temp;
		}
	}
}

bool isCannotContinue(int type, int x, int y)
{
	return (map[type][y][x+1] != map[type][y][x]);
}

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

bool isCanPutRoad(int type, int x, int y, int len, int n, queue<qnode> &q)
{
	int next = map[type][y][x+1], prev = map[type][y][x];
	if(abs(next - prev) != 1)
		return false;
	if(next > prev){
		int end = x-len+1;
		for( ; x>=end; x--){
			if(isOut(x, y, n))	return false;
			if(prev != map[type][y][x])	return false;
			if(road[type][y][x])	return false;
			q.push(qnode(x, y));
		}
		return true;
	}
	else if(next < prev){
		int end = x+len;
		for(x=x+1; x<=end; x++){
			if(isOut(x, y, n))	return false;
			if(next != map[type][y][x])	return false;
			if(road[type][y][x])	return false;
			q.push(qnode(x, y));
		}
		return true;
	}
	else{	cout << "error";	return false;	}
}

void putRoad(int type, queue<qnode> &q)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y;	q.pop();
		road[type][y][x] = true;
	}
}

int solve(int n, int len)
{
	int ret = 0;
	for(int type=0; type<2; type++){
		for(int y=0; y<n; y++){
			int success = 1;
			for(int x=0; x<n-1; x++){
				if(isCannotContinue(type, x, y)){
					queue<qnode> q;
					if(isCanPutRoad(type, x, y, len, n, q)){
						putRoad(type, q);
						continue;
					}
					success = 0;
					break;
				}
			}
			ret += success;
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, len;
	input(n, len);
	cout << solve(n, len);
	return 0;
}

