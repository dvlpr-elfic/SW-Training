

#include <stdio.h>

#define MAX_DATE 32
#define MAX_MONTH 13

int max_date[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int solve(int arr[][MAX_DATE], int m, int d)
{
	d = arr[m][d];
	return (((d%7)+4)%7);
}

void init(int arr[][MAX_DATE])
{
	int count = 0;
	for(int i=1; i<=12; i++){
		for(int j=1; j<=max_date[i]; j++){
			arr[i][j] = count++;
		}
	}
}


int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	int arr[MAX_MONTH][MAX_DATE] = {0, };
	init(arr);
	scanf("%d", &t);
	for(int tc=1; tc<=t; tc++){
		int m, d;
		scanf("%d %d", &m, &d);
		int ans = solve(arr, m, d);
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
