
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>

#define MAX 1000001

using namespace std;

bool not_prime[MAX] = {true, true, };

void setting(void)
{
	for(int i=2; i<MAX; i++){
		if(!not_prime[i]){
			for(int j=2*i; j<MAX; j+=i){
				not_prime[j] = true;
			}
		}
	}
}

void input(int &d, int &a, int &b)
{
	cin >> d >> a >> b;
}

bool isSpecial(int input, int d)
{
	while(input){
		if(input % 10 == d)
			return true;
		input /= 10;
	}
	return false;
}

int solve(int d, int a, int b)
{
	int ret = 0;
	for(int i=a; i<=b; i++){
		if(not_prime[i])
			continue;
		if(isSpecial(i, d))
			ret++;
	}
	return ret;
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	setting();
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int d, a, b;
		input(d, a, b);
		cout << "#" << tc << " " << solve(d, a, b) << '\n';
	}
	return 0;
}
