
/**
 * @author : Jihoon Jang
 */

#include <iostream>
#include <string.h>
#include <stdio.h>

#define MAX_STR 100
#define MAX_CHAR 16

using namespace std;

typedef struct STRING
{
	char arr[MAX_STR];
	int index;
	STRING(void)
	{
		index = 0;
		memset(arr, 0, sizeof(arr));
	}
	bool push_back(char item)
	{
		if(index >= MAX_STR){
			cout << "string object overflow" << endl;
			return false;
		}
		arr[index++] = item;
		return true;
	}
}STRING;

void solve(char map[][MAX_CHAR], int max)
{
	STRING str;
	for(int col=0; col<max; col++){
		for(int row=0; row<5; row++){
			if(map[row][col])
				str.push_back(map[row][col]);
		}
	}
	cout << str.arr << endl;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		char map[5][MAX_CHAR] = {0, };
		int max = 0;
		for(int i=0; i<5; i++){
			cin >> map[i];
			int len = strlen(map[i]);
			if(max < len)
				max = len;
		}
		cout << "#" << tc << " ";
		solve(map, max);
	}

	return 0;
}
