
/**
  * @author Jihoon Jang
  * 44 min
  */

#include <iostream>
#include <algorithm>
#include <memory.h>

#define SIZE 21
#define INF 0x7FFFFFFF

using namespace std;

int ability[SIZE][SIZE];
int picked[SIZE];
int team[2][SIZE];

void init(void)
{
	memset(picked, -1, sizeof(picked));
}

void input(int &n)
{
	cin >> n;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			cin >> ability[y][x];
		}
	}
}

void setLinkTeam(int n)
{
	int idx = 0;
	for(int i=0; i<n; i++){
		if(picked[i] == -1){
			team[1][idx++] = i;
			picked[i] = 1;
		}
	}
}

int cal(int n, int limit)
{
	setLinkTeam(n);
	int sinergy[2] = {0, };
	for(int i=0; i<2; i++){
		for(int j=0; j<limit; j++){
			int cur = team[i][j];
			for(int target=0; target<n; target++){
				if(picked[target] == i){
					sinergy[i] += ability[cur][target];
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		if(picked[i] == 1)
			picked[i] = -1;
	}
	return abs(sinergy[0]-sinergy[1]);
}

int solve(int depth, int r, int s, int n)
{
	if(depth == r){
		return cal(n, r);
	}
	int ret = INF;
	int limit = (n-1)-(r-1-depth);
	for(int i=s; i<limit; i++){
		team[0][depth] = i;
		picked[i] = 0;
		ret = min(ret, solve(depth+1, r, i+1, n));
		picked[i] = -1;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	input(n);
	init();
	cout << solve(0, n/2, 0, n);
	return 0;
}

