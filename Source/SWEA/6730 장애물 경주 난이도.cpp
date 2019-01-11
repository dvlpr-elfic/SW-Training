
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 100

using namespace std;

void input(int &n, int *arr)
{
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> arr[i];
	}
}

void solve(int &up, int &down, int n, int *arr)
{
	n--;
	for(int i=0; i<n; i++){
		up = max(up, arr[i+1] - arr[i]);
		down = max(down, arr[i] - arr[i+1]);
	}
}

int main(void)
{
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n, up=0, down=0;
		int arr[SIZE];
		input(n, arr);
		solve(up, down, n, arr);
		cout << '#' << tc << ' ' << up << ' ' << down << '\n';
	}
	return 0;
}
