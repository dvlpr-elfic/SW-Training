
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <algorithm>
#include <memory.h>

#define SIZE 21

using namespace std;

int score[SIZE];

void input(int &n, int &m)
{
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int temp;
			cin >> temp;
			if(temp){
				score[i]++;
			}
		}
	}
}

bool compare(const int &n1, const int &n2)
{
	return (n1>n2);
}

void solve(int &cnt, int &maxx, int n)
{
	sort(score, score+n, compare);
	cnt = 1;
	maxx = score[0];
	for(int i=1; i<n; i++){
		if(maxx > score[i])
			break;
		cnt++;
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n, m, cnt, maxx;
		input(n, m);
		solve(cnt, maxx, n);
		memset(score, 0, sizeof(score));
		cout << '#' << tc << ' ' << cnt << ' ' << maxx << '\n';
	}
	return 0;
}

