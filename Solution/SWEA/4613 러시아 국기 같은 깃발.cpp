
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>
#include <algorithm>

#define SIZE 51
#define INF 987654321

#define CHANGE(x) ((x == 'W') ? (x = 'B') : ((x == 'B') ? (x = 'R') : (x = 0)))

using namespace std;

char map[SIZE][SIZE];
int color[3];
int ans;

void init(void)
{
	ans = INF;
}

void input(int &n, int &m)
{
	cin >> n >> m;
	for(int i=0; i<n; i++){
		cin >> map[i];
	}
}

void setColorNumber(int index, int number)
{
	color[index] = number;
}

int coloring(int n, int m)
{
	int ret = 0;
	int color_index = 0;
	char current = 'W';
	for(int y=0, cnt = 0; y<n; y++, cnt++){
		if(cnt == color[color_index]){
			CHANGE(current);
			color_index++;
			cnt = 0;
		}
		for(int x=0; x<m; x++){
			if(map[y][x] != current)
				ret++;
		}
	}
	return ret;
}

void createColor(int depth, int remain, int n, int m)
{
	if(depth == 2){
		// base case
		setColorNumber(depth, remain);
		ans = min(ans, coloring(n, m));
		return;
	}
	int limit = remain + depth - 2;
	for(int i=1; i<=limit; i++){
		setColorNumber(depth, i);
		createColor(depth+1, remain-i, n, m);
	}
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n, m;
		init();
		input(n, m);
		createColor(0, n, n, m);
		cout << "#" << tc << " " << ans << '\n';
	}
	return 0;
}
