
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 1000001

using namespace std;

int table[SIZE];

void input(int &n, int &b, int &c)
{
	cin >> n;
	for(int i=0; i<n; ++i){
		cin >> table[i];
	}
	cin >> b >> c;
}

long long solve(int n, int b, int c)
{
	long long ret = 0;
	for(int i=0; i<n; i++){
		table[i] -= b;
		if(table[i] <= 0){
			ret++;
			continue;
		}
		ret++;
		int temp = table[i]/c;
		if(temp*c == table[i]){
			ret+=temp;
		}
		else if(temp*c > table[i]){
			ret++;
		}
		else if(temp*c < table[i]){
			ret+=(temp+1);
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, b, c;
	input(n, b, c);
	cout << solve(n, b, c) << '\n';
	return 0;
}

