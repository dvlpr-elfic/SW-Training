
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define SIZE 1000001

using namespace std;

int d[SIZE];

void input(int &n)
{
	cin >> n;
}

static int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}

int solve(int n)
{
	d[1] = 0;
	for(int i=2; i<=n; i++){
		d[i] = d[i-1] + 1;
		if(!(i % 2))
			d[i] = min(d[i], d[i/2] + 1);
		if(!(i % 3))
			d[i] = min(d[i], d[i/3] + 1);
	}
	return d[n];
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n;
	input(n);
	cout << solve(n) << '\n';
	return 0;
}

