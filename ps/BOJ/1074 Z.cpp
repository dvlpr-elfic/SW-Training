
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <math.h>

using namespace std;

typedef struct Flag
{
	bool find_ans;
}Flag;

Flag flag = {0};
int ans = 0, cnt = 0;

bool isInArea(int x, int y, int size, int r, int c)
{
	return (r >= y && r <= y+size && c >= x && c <= x+size);
}


void divide(int x, int y, int size, int r, int c)
{
	if(!isInArea(x, y, size, r, c)){
		cnt += size*size;
		return;
	}
	if(flag.find_ans)
		return;
	if(size == 1){
		// base case
		if(x == c && y == r){
			ans = cnt;
			flag.find_ans = true;
		}
		cnt++;
		return;
	}
	int half = size/2;
	divide(x, y, half, r, c);
	divide(x+half, y, half, r, c);
	divide(x, y+half, half, r, c);
	divide(x+half, y+half, half, r, c);
}


int main(void)
{
	int n, r, c;
	cin >> n >> r >> c;
	divide(0, 0, (int)pow(2, n), r, c);
	cout << ans << endl;
	return 0;
}
