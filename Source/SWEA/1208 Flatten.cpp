
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 100
#define INF 987654321

using namespace std;

int box[SIZE];

void input(int &k)
{
	cin >> k;
	for(int i=0; i<SIZE; i++){
		cin >> box[i];
	}
}

void setMinMax(int &from, int &to)
{
	int maxx = 0, minn = INF;
	for(int i=0; i<SIZE; i++){
		if(maxx < box[i])
			maxx = box[i], from = i;
		if(minn > box[i])
			minn = box[i], to = i;
	}
}

int solve(int k)
{		
	int from, to;
	while(k--){
		setMinMax(from, to);
		box[from]--, box[to]++;
	}
	setMinMax(from, to);
	return box[from]-box[to];
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		int k;
		input(k);
		cout << "#" << tc << ' ' << solve(k) << '\n';
	}
	return 0;
}
