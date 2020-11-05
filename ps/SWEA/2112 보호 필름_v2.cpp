
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>

#define B (-1)
#define A 0
#define SIZE 21

using namespace std;

int map[SIZE][SIZE];
bool marked[SIZE];

void input(int &h, int &w, int &k)
{
	cin >> h >> w >> k;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			int tmp;
			cin >> tmp;
			if(tmp)
				map[y][x] = B;
			else
				map[y][x] = A;
		}
	}
}

bool isPass(int h, int w, int k)
{
	for(int x=0; x<w; x++){
		bool res = false;
		int base = 0, cnt = 0;
		for(int y=0; y<h; y++){
			if(map[base][x] == map[y][x]){
				cnt++;
			}
			else{
				base = y, cnt = 1;
			}
			if(cnt >= k){
				res = true;
				break;
			}
		}
		if(!res)	return false;
	}
	return true;
}

bool combination(int depth, int n, int r, int h, int w, int k, int s)
{
	if(depth == r){
		// base case
		return isPass(h, w, k);
	}
	bool ret = false;
	int limit = (n-1)-(r-1-depth);
	for(int i=s; i<=limit; i++){
		if(marked[i])	continue;
		marked[i] = true;
		for(int ab=B; ab<=A; ab++){
			int temp[SIZE];
			memcpy(temp, map[i], sizeof(temp));
			memset(map[i], ab, sizeof(map[i]));
			ret |= combination(depth+1, n, r, h, w, k, i+1);
			memcpy(map[i], temp, sizeof(temp));
		}
		marked[i] = false;
	}
	return ret;
}

int solve(int h, int w, int k)
{
	for(int ret=0; ret<=h; ret++){
		if(combination(0, h, ret, h, w, k, 0))
			return ret;
	}
	return -1;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int h, w, k;
		input(h, w, k);
		cout << '#' << tc << ' ' << solve(h, w, k) << '\n';
	}
	return 0;
}

