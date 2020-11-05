
/**
 * @author : Jihoon Jang
 */

#include <stdio.h>
#include <math.h>

long long solve(int N, int P)
{
	long long res = 0;
	double div = N/P;
	double mod = N%P;
	return res = (long long)pow(div, P-mod) * (long long)pow(div+1, mod);
}


int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++){
		int N, P;
		scanf("%d %d", &N, &P);
		long long ans = solve(N, P);
		printf("#%d %lld\n", tc, ans);
	}

	return 0;
}
