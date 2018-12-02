
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 3000

using namespace std;

int map[SIZE][SIZE] = {0, };
int cnt[3] = {0, };
int call;

bool isCanUse(int x, int y, int size)
{
	int val = map[y][x];
	for(int c=x; c<x+size; c++){
		for(int r=y; r<y+size; r++){
			if(val != map[r][c])
				return false;
		}
	}
	return true;
}

void divide(int x, int y, int size)
{
	if(isCanUse(x, y, size)){
		int type = map[y][x]+1;
		cnt[type]++;
		return;
	}
	int delta[3] = {0, size/3, (size/3)*2};
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			divide(x+delta[j], y+delta[i], size/3);
		}
	}
}

int main(void)
{
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> map[i][j];
		}
	}
	divide(0, 0, n);
	for(int i=0; i<3; i++){
		cout << cnt[i] << '\n';
	}

	return 0;
}
