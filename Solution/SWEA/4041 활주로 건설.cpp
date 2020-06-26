
/**
 * @author : Jihoon Jang
 */

#include <iostream>
#include <memory.h>
#include <stdlib.h>

#define MAP_SIZE 21

using namespace std;

int map[2][MAP_SIZE][MAP_SIZE];
bool check[MAP_SIZE];

void init(void)
{
	memset(map, 0, sizeof(map));
	memset(check, 0, sizeof(check));
}

void input(int n)
{
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			int val;
			cin >> val;
			map[0][i][j] = val;
			map[1][j][i] = val;
		}
	}
}

int install(int* arr, int n, int x)
{
	int old = arr[0];
	memset(check, 0, sizeof(bool)*n);
	for(int i=1; i<n; i++){
		if(check[i]){
			old = arr[i];
			continue;
		}
		if(old == arr[i])
			continue;
		if(abs(old - arr[i]) > 1)
			return 0;
		if(old - arr[i] == 1){
			for(int c=i+1; c<x+i; c++){
				if(c >= n)						// 범위 벗어난 경우
					return 0;
				if(arr[c] != arr[i] || check[c])
					return 0;
			}
			memset(check+i, 1, x*sizeof(bool));
			
		}
		else if(old - arr[i] == -1){
			for(int c=i-1; c>=i-x; c--){
				if(c < 0)						// 범위를 벗어난 경우
					return 0;
				if(arr[c] != arr[i-1] || check[c])
					return 0;
			}
			memset(check+i-x, 1, x*sizeof(bool));
		}
		old = arr[i];
	}
	return 1;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n, x;
		int ans = 0;
		cin >> n >> x;
		input(n);
		for(int i=0; i<n; i++){
			ans += install(map[0][i], n, x);
			ans += install(map[1][i], n, x);
		}
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
