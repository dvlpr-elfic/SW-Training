
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <algorithm>

#define SIZE 100

using namespace std;

int map[SIZE][SIZE];

void input(void)
{
	int tmp;
	cin >> tmp;
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			cin >> map[i][j];
		}
	}
}

int solve(void)
{
	int ret = 0;
	for(int y=0; y<SIZE; y++){
		int tmp = 0;
		for(int x=0; x<SIZE; x++){
			tmp += map[y][x];
		}
		ret = max(ret, tmp);
	}
	for(int x=0; x<SIZE; x++){
		int tmp = 0;
		for(int y=0; y<SIZE; y++){
			tmp += map[y][x];
		}
		ret = max(ret, tmp);
	}
	int tmp = 0;
	for(int x=0, y=0; x<SIZE; x++, y++){
		tmp += map[y][x];
	}
	ret = max(ret, tmp);
	tmp = 0;
	for(int x=99, y=99; x>=0; x--, y--){
		tmp += map[y][x];
	}
	ret = max(ret, tmp);
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		input();
		cout << '#' << tc << ' ' << solve() << '\n';
	}
	return 0;
}
