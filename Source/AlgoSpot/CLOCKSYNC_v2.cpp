
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;

int numberOfwatch[] = {3, 4, 4, 5, 5, 4, 3, 5, 5, 5};
int switch_table[10][5] = {
	{0, 1, 2}, 
	{3, 7, 9, 11}, 
	{4, 10, 14, 15}, 
	{0, 4, 5, 6, 7}, 
	{6, 7, 8, 10, 12}, 
	{0, 2, 14, 15}, 
	{3, 14, 15}, 
	{4, 5, 7, 14, 15}, 
	{1, 2, 3, 4, 5}, 
	{3, 4, 5, 9, 13}
};

int watch[16] = {0, };
int cnt = 0;
int ans = 99999;

void init(void)
{
	ans = 99999;
	cnt = 0;
	memset(watch, 0, sizeof(watch));
}

void doPush(int switch_num)
{
	int len = numberOfwatch[switch_num];
	for(int i=0; i<len; i++){
		int watch_num = switch_table[switch_num][i];
		watch[watch_num] = (watch[watch_num] + 3);
		if(watch[watch_num] > 12)
			watch[watch_num] = 3;
	}
	cnt++;
}

bool isSync(void)
{
	for(int i=0; i<16; i++){
		if(watch[i] != 12)
			return false;
	}
	return true;
}

void dfs(int depth, int switch_num)
{
	if(depth == 10){
		// base case
		if(isSync())
			ans = min(ans, cnt);
		return;
	}
	dfs(depth+1, switch_num+1);
	for(int i=0; i<3; i++){
		doPush(switch_num);
		dfs(depth+1, switch_num+1);
	}
	doPush(switch_num);
	cnt -= 4;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		for(int i=0; i<16; i++){
			cin >> watch[i];
		}
		dfs(0, 0);
		if(ans == 99999)
			cout << -1 << endl;
		else
			cout << ans << endl;
	}
	return 0;
}
