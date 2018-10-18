

/*
 * @author : Jihoon Jang
 * 115 Minuites
 */

#include <iostream>

#define MAP_SIZE 31

using namespace std;

int ladder[MAP_SIZE][MAP_SIZE] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, }, };

int ans = -1;

bool isCorrect(int n, int h)
{
	for(int i=1; i<=n; i++){
		int v = i, j = 1;
		while(j<=h+1){
			if(!ladder[v][j]){
				j++;
				continue;
			}
			else{
				v = ladder[v][j];
				j++;
			}
		}
		if(v != i)
			return false;
	}
	return true;
}

void select(int depth, int n, int r, int start_line, int start_h, int max_h)
{
	if(depth == r){
		// base case
		if(isCorrect(n, max_h))
			ans = depth;
		return;
	}
	int i = start_h+1;
	for(int line = start_line; line<=n-1; line++){
		for( ; i<=max_h; i++){
			if((!ladder[line][i]) && (!ladder[line+1][i])){
				ladder[line][i] = line+1;
				ladder[line+1][i] = line;
				select(depth+1, n, r, line, i, max_h);
				ladder[line][i] = 0;
				ladder[line+1][i] = 0;
			}
		}
		i = 1;
	}
}

void solve(int n, int h)
{
	for(int i=1; i<4; i++){
		select(0, n, i, 1, 0, h);
		if(ans != -1)
			return;
	}
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int n, m, h;
	cin >> n >> m >> h;
	for(int i=0; i<m; i++){
		int a, b;
		cin >> a >> b;
		ladder[b][a] = b+1;
		ladder[b+1][a] = b;
	}
	if(isCorrect(n, h)){
		cout << 0 << endl;
		return 0;
	}
	solve(n, h);
	cout << ans << endl;
	return 0;
}
