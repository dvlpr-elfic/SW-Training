
/**
  * @author Jihoon Jang
  */

#include <iostream>
#define SIZE 16

using namespace std;

int check[SIZE][SIZE];
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void marking(int delta, int x, int y, int n)
{
	check[y][x] += delta;
	for(int i=0; i<8; i++){
		int xx = x, yy = y;
		while(1){
			xx += dx[i];
			yy += dy[i];
			if(isOut(xx, yy, n))
				break;
			check[yy][xx] += delta;
		}
	}
}

int solve(int depth, int n)
{
	if(depth == n){
		// base case
		return 1;
	}
	int ret = 0;
	int y = depth;
	for(int x=0; x<n; x++){
		if(check[y][x])
			continue;
		marking(1, x, y, n);
		ret += solve(depth+1, n);
		marking(-1, x, y, n);
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	cout << solve(0, n);
	return 0;
}

