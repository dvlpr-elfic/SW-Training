
/**
  * @author Jihoon Jang
  * time : 59min
  */

#include <iostream>
#include <memory.h>
#include <algorithm>

#define SIZE 11

using namespace std;

typedef struct node
{
	double x, m;
}node;

node table[SIZE];
double ans[SIZE];

void init(void)
{
	memset(table, 0, sizeof(table));
	memset(ans, 0, sizeof(ans));
}

void input(int &n)
{
	cin >> n;
	for(int i=0; i<n; i++){
		double x;
		cin >> x;
		table[i].x = x;
	}
	for(int i=0; i<n; i++){
		double m;
		cin >> m;
		table[i].m = m;
	}

}

bool err(double low, double high)
{
	return (abs(low-high) > 1e-12);
}

double find_balance(double left, double right, double m1, double m2, int n, int pos)
{
	double low = left, high = right;
	double mid;
	while(err(low, high)){
		mid = (low+high)/2.0;
		double f1=0, f2=0, d1, d2;
		for(int i=0; i<pos; i++){
			d1 = table[i].x - mid;
			f1 += table[i].m/(d1*d1);
		}
		for(int i=pos; i<n; i++){
			d2 = table[i].x - mid;
			f2 += table[i].m/(d2*d2);
		}
		if(f1 > f2)
			low = mid;
		else if(f1 < f2)
			high = mid;
		else
			break;
	}
	return mid;
}

void solve(int &n)
{
	init();
	input(n);
	for(int i=1; i<n; i++){
		ans[i-1] = find_balance(table[i-1].x, table[i].x, table[i].x, table[i].m, n, i);
	}
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n;
		solve(n);
		cout << "#" << tc << " ";
		for(int i=0; i<n-1; i++){
			cout << fixed;
			cout.precision(10);
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
