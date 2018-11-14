
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <memory.h>

#define MAX 20

using namespace std;

bool picked[MAX];
bool couple[MAX][MAX];

int ans = 0;

void init(void)
{
	ans = 0;
	memset(couple, 0, sizeof(couple));
	memset(picked, 0, sizeof(picked));
}


void pick(int depth, int n)
{
	if(depth == n/2){
		// base case
		ans++;
		return;
	}
	int first;
	for(first=0; first<n; first++){
		if(!picked[first])
			break;
	}
	for(int second=0; second<n; second++){
		if(!picked[second]){
			if(couple[first][second]){
				picked[first] = picked[second] = true;
				pick(depth+1, n);
				picked[first] = picked[second] = false;
			}
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
		int n, m;
		cin >> n >> m;
		for(int i=0; i<m; i++){
			int n1, n2;
			cin >> n1 >> n2;
			couple[n1][n2] = couple[n2][n1] = true;
		}
		pick(0, n);
		cout << ans << endl;
	}
	return 0;
}
