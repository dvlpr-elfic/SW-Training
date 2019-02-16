
/**
  * @author Jihoon Jang
  * 30min
  */

#include <iostream>
#include <algorithm>

#define SIZE 11
#define INF 0x3FFFFFFF

using namespace std;

int map[SIZE][SIZE];
bool check[SIZE][SIZE];
int dx[] = {0, 0, 0, -1, 1};
int dy[] = {0, 1, -1, 0, 0};

void input(int &n){
	cin >> n;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> map[y][x];
		}
	}
}

void marking(int x, int y, bool mark){
	for(int i=0; i<5; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		check[ny][nx] = mark;
	}
}

bool isMarked(int x, int y){
	for(int i=0; i<5; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(check[ny][nx])
			return true;
	}
	return false;
}

int getPrice(int x, int y){
	int ret = 0;
	for(int i=0; i<5; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		ret += map[ny][nx];
	}
	return ret;
}

int solve(int depth, int price, int n){
	if(depth == 3){
		return price;
	}
	int ret = INF;
	for(int y=1; y<n-1; y++){
		for(int x=1; x<n-1; x++){
			if(!isMarked(x, y)){
				marking(x, y, true);
				ret = min(ret, solve(depth+1, price+getPrice(x, y), n));
				marking(x, y, false);
			}
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	input(n);
	cout << solve(0, 0, n) << endl;
	return 0;
}

