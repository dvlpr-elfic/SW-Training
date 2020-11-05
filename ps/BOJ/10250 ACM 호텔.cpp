
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>

using namespace std;

int map[100][100];

void init(int h, int w)
{
	for(int i=1; i<=h; i++){
		for(int j=1; j<=w; j++){
			map[i][j] = i*100+j;
		}
	}
}


void solve(void)
{
	int h, w, n;
	int cnt = 0;
	cin >> h >> w >> n;		// 높이, 너비, 몇번째 손님
	init(h, w);
	for(int x=1; x<=w; x++){
		for(int y=1; y<=h; y++){
			cnt++;
			if(cnt == n){
				cout << map[y][x] << endl;
			}
		}
	}
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while(t--){
		solve();
	}

	return 0;
}
