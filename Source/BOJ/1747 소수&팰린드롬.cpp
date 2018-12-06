
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <string.h>

#define MAX 1003002

using namespace std;

bool isPalinedrome(int n)
{
	char str[10];
	sprintf(str, "%d", n);
	int front = 0, back = strlen(str)-1;
	while(front < back){
		if(str[front] != str[back]){
			return false;
		}
		front++, back--;
	}
	return true;
}

bool isPrimeNumber(int n)
{
	if(n == 1)
		return false;
	if(n == 2)
		return true;
	for(int i=2; i<n; i++){
		if(!(n%i)){
			return false;
		}
	}
	return true;
}

void solve(int n)
{
	for(int i=n; i<MAX; i++){
		if(isPalinedrome(i)){
			if(isPrimeNumber(i)){
				cout << i << endl;
				return;
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n;
	cin >> n;
	solve(n);
	return 0;
}
