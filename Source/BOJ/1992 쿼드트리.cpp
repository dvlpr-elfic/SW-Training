
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <string>

#define SIZE 100

using namespace std;

int map[SIZE][SIZE];

int getColor(int x, int y, int size)
{
	if(size == 1)
		return map[y][x];
	int val = map[y][x];
	for(int i=y; i<size+y; i++){
		for(int j=x; j<size+x; j++){
			if(val != map[i][j])
				return -1;
		}
	}
	return val;
}

string zip(int x, int y, int size)
{
	int color = getColor(x, y, size);

	if(color >= 0){
		if(color == 1)
			return string("1");
		else
			return string("0");
	}
	int half = size/2;
	string ul = zip(x, y, half);
	string ur = zip(x+half, y, half);
	string ll = zip(x, y+half, half);
	string lr = zip(x+half, y+half, half);
	return string("(" + ul + ur + ll + lr + ")");
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			char ch;
			cin >> ch;
			map[i][j] = ch-'0';
		}
	}
	string ans = zip(0, 0, n);
	cout << ans << endl;
	return 0;
}
