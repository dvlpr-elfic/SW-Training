
#include <stdio.h>
#include <algorithm>

#define SWITCH 10
#define CLOCK 16
#define INF 0x7FFFFFF7
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

using namespace std;

int link [10][6] = {
	{0, 1, 2, -1}, 
	{3, 7, 9, 11, -1}, 
	{4, 10, 14, 15, -1}, 
	{0, 4, 5, 6, 7, -1}, 
	{6, 7, 8, 10, 12, -1}, 
	{0, 2, 14, 15, -1}, 
	{3, 14, 15, -1}, 
	{4, 5, 7, 14, 15, -1}, 
	{1, 2, 3, 4, 5, -1}, 
	{3, 4, 5, 9, 13, -1}
};

bool isSync(int* clocks)
{
	for(int i=0; i<CLOCK; i++){
		if(clocks[i] != 12)
			return false;
	}
	return true;
}

void switchPush(int* clocks, int sw)
{
	for(int i=0; (link[sw][i] != -1); i++){
		clocks[link[sw][i]] += 3;
		if(clocks[link[sw][i]] > 12)
			clocks[link[sw][i]] = 3;
	}
}


int dfs(int sw, int* clocks)
{
	if(sw == SWITCH){
		if(isSync(clocks))
			return 0;
		else
			return INF;
	}
	int res = INF;
	for(int cnt=0; cnt<4; cnt++){
		res = MIN(res, (cnt + dfs(sw+1, clocks)));
		switchPush(clocks, sw);
	}
	return res;
}


int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for(int tc=1; tc<=t; tc++){
		int clocks[CLOCK] = {0, };
		for(int i=0; i<CLOCK; i++)
			scanf("%d", clocks+i);
		int ans = dfs(0, clocks);
		if(ans > 9999)
			ans = -1;
		printf("%d\n", ans);
	}

	return 0;
}
