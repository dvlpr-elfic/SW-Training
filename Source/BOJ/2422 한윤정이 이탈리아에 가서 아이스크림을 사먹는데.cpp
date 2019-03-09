
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 201

using namespace std;

bool graph[SIZE][SIZE];
int candy[3];

void input(int &n)
{
	int m;
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int p,c;
		cin >> p >> c;
		graph[p][c] = graph[c][p] = true;
	}
}

bool isInPickedCandy(int input, int r)
{
	for(int i=0; i<r; i++){
		if(input == candy[i]){
			return true;
		}
	}
	return false;
}

bool isCanMix(int r)
{
	for(int i=0; i<r; i++){
		int cur = candy[i];
		for(int target=0; target<SIZE; target++){
			if(graph[cur][target]){
				if(isInPickedCandy(target, r)){
					return false;
				}
			}
		}
	}
	return true;
}

int solve(int depth, int n, int r, int start)
{
	if(depth == r){
		if(isCanMix(r))
			return 1;
		else
			return 0;
	}
	int ret = 0;
	int limit = n-(r-depth-1);
	for(int i=start; i<=limit; i++){
		candy[depth] = i;
		ret += solve(depth+1, n, r, i+1);
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	input(n);
	cout << solve(0, n, 3, 1) << '\n';
	return 0;
}

