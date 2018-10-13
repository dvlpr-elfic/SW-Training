

#include <iostream>
#include <memory.h>

#define MAP_SIZE 21

using namespace std;

int map[MAP_SIZE][MAP_SIZE];
bool check[MAP_SIZE];
int A[MAP_SIZE] = {0, };
int B[MAP_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int ans = 0;

void init(void)
{
	ans = 0;
	memset(map, 0, sizeof(map));
	memset(check, 0, sizeof(check));
}

bool isPass(int k, int w, int d)
{
	bool result;
	for(int x=0; x<w; x++){
		int cnt = 0;
		int old = map[0][x];
		result = false;
		for(int y=1; y<d; y++){
			if(old == map[y][x]){
				cnt++;
				if(cnt == k-1)
					result = true;
			}
			else{
				old = map[y][x];
				cnt = 0;
			}
		}
		if(!result)
			return false;
	}
	return true;
}

void dfs(int depth, int n, int r, int s, int k, int w)		// s : -1, depth : 0
{
	if(depth == r){
		// base case
		if(isPass(k, w, n))
			ans = r;
		return;
	}
	for(int i=s+1; i<n && !ans; i++){
		if(!check[i]){
			int *temp_arr = new int[w];
			check[i] = true;
			memcpy(temp_arr, map[i], sizeof(int)*w);
			memset(map[i], 0, sizeof(int)*w);
			dfs(depth+1, n, r, i, k, w);
			memcpy(map[i], B, sizeof(int)*w);
			dfs(depth+1, n, r, i, k, w);
			check[i] = false;
			memcpy(map[i], temp_arr, sizeof(int)*w);
			delete[] temp_arr;
		}
	}
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
		int d, w, k;
		cin >> d >> w >> k;			// set parameter
		for(int i=0; i<d; i++)		// set map
			for(int j=0; j<w; j++)
				cin >> map[i][j];
		if(isPass(k, w, d)){
			cout << "#" << tc << " " << 0 << endl;
			continue;
		}
		for(int i=1; i<=d && !ans; i++){
			dfs(0, d, i, -1, k, w);
		}
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
