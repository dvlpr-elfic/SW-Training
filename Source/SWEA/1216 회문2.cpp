
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 100
#define MAPSIZE 101

using namespace std;

char map[2][MAPSIZE][MAPSIZE];

void input(void)
{
	int tmp;
	cin >> tmp;
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
	char *head = str, *tail = str + (len-1);
	int limit = len/2;
	for(int i=0; i<limit; i++){
		if(*head != *tail)
			return false;
		head++, tail--;
	}
	return true;
}

int solve(void)
{
	for(int len=SIZE; len>=0; len--){
		for(int y=0; y<SIZE; y++){
			for(int x=0; x<=SIZE-len; x++){
				if(isPalindrome(&(map[0][y][x]), len))
					return len;
				if(isPalindrome(&(map[1][y][x]), len))
					return len;
			}
		}
	}
	return 0;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		input();
		cout << '#' << tc << ' ' << solve() << '\n';
	}
	return 0;
}
