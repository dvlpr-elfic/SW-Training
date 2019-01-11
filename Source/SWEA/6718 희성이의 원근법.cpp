
/**
  * @author Jihoon Jang
  */

#include <stdio.h>

int main(void)
{
	//freopen("input.txt", "r", stdin);
	int t, input, ans;
	scanf("%d", &t);
	for(int tc=1; tc<=t; tc++){
		scanf("%d", &input);
		if(input < 100)
			ans = 0;
		else if(input >= 100 && input <= 999)
			ans = 1;
		else if(input >= 1000 && input <= 9999)
			ans = 2;
		else if(input >= 10000 && input <= 99999)
			ans = 3;
		else if(input >= 100000 && input <= 999999)
			ans = 4;
		else
			ans = 5;
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}
