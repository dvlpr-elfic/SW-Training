
/**
  * @author Jihoon Jang
  * 40min
  */

#include <iostream>
#include <string>
#include <algorithm>

#define SIZE 256

using namespace std;

int table[SIZE];

bool cmp(const int& n1, const int& n2)
{
	return (n1>n2);
}

void input(int &n)
{
	cin >> n;
	for(int i=0; i<n; i++){
		string str;
		cin >> str;
		reverse(str.begin(), str.end());
		int len = str.size();
		for(int idx=0, weight = 1; idx<len; idx++, weight*=10){
			table[str[idx]] += weight;
		}
	}
}

int solve(void)
{
	int weight = 9;
	sort(table, table+SIZE, cmp);
	int i=0, ret=0;
	while(table[i]){
		table[i] *= weight;
		ret += table[i];
		weight--, i++;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	input(n);
	cout << solve() << endl;
	return 0;
}

