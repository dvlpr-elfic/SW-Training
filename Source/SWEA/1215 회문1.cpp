
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define MAPSIZE 9
#define SIZE 8

using namespace std;

char map[2][MAPSIZE][MAPSIZE];

void input(int &n)
{
	cin >> n;
	for(int i=0; i<SIZE; i++){
		cin >> map[0][i];
	}
	for(int y=0; y<SIZE; y++){
		for(int x=0; x<SIZE; x++){
			map[1][x][y] = map[0][y][x];
		}
	}
}

bool isPalindrome(char *str, int len)
{
	char *head = str, *tail = str+(len-1);
	int limit = len/2;
	for(int i=0; i<limit; i++){
		if(*head != *tail)
			return false;
		head++, tail--;
	}
	return true;
}

int solve(int n)
{
	int ret = 0;
	for(int y=0; y<SIZE; y++){
		for(int x=0; x<=SIZE-n; x++){
			if(isPalindrome(&(map[0][y][x]), n))
				ret++;
			if(isPalindrome(&(map[1][y][x]), n))
				ret++;
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		int n;
		input(n);
		cout << '#' << tc << ' ' << solve(n) << '\n';
	}
	return 0;
}
