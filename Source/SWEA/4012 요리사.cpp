
/**
 * @author : Jihoon Jang
 */

#include <stdio.h>
#include <vector>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX_N 20
#define INF 0x7FFFFFFF

using namespace std;

typedef struct vectornode
{
	int fp;
	int sp;
	vectornode(int a, int b)
	{
		fp = a;
		sp = b;
	}
}vectornode;

int map[MAX_N][MAX_N];
int ans;

int cal(vector<int> &v)
{
	return 0;
}

void init(void)
{
	ans = INF;
	memset(map, 0, sizeof(map));
}


void pick(int depth, int n, bool *check, vector<int> *v)
{
	if(depth == n/2){			// base case
		for(int i=0; i<v[0].size(); i++){
			printf("%d ", v[0][i]);
		}
		printf("\n");
		return;
	}
	for(int i=1; i<=n; i++){
		if(!check[i]){
			check[i] = true;
			v[0].push_back(i);
			pick(depth+1, n, check, v);
			v[0].pop_back();
			check[i] = false;
		}
	}
}

int calSynergy(int* recipe, int size)
{
	int res = 0;
	for(int i=1; i<=size; i++)
		for(int j=i+1; j<=size; j++)
			res += map[recipe[i]][recipe[j]] + map[recipe[j]][recipe[i]];
	return res;
}

void combination(int* A, int index, int n, int r, int target, int* B, bool* check)
{
	if(r==0){			// base case
		/*printf("A : ");
		for(int i=1; i<index; i++){
			printf("%d ", A[i]);
		}*/
		int k=1;
		for(int i=1; i<=n; i++){
			if(!check[i]){
				B[k++] = i;
			}
		}
		/*printf("B : ");
		for(int i=1; i<index; i++){
			printf("%d ", B[i]);
		}
		printf("\n");*/
		int tasteA = calSynergy(A, n/2);
		int tasteB = calSynergy(B, n/2);
		int difference = abs((tasteA - tasteB));
		ans = MIN(ans, difference);
		return;
	}
	else if(target > n)
		return;			// ¹«½Ã
	else{
		A[index] = target;
		check[target] = true;
		combination(A, index+1, n, r-1, target+1, B, check);
		check[target] = false;
		combination(A, index, n, r, target+1, B, check);
	}
}



int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for(int tc=1; tc<=t; tc++){
		init();						// init variables
		int n;
		scanf("%d", &n);
		bool check[MAX_N] = {0, };
		vector<int> v[2];
		int A[MAX_N] = {0, };
		int B[MAX_N] = {0, };
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				scanf("%d", &(map[i][j]));
			}
		}

		//pick(0, n, check, v);
		combination(A, 1, n, n/2, 1, B, check);
		printf("#%d %d\n", tc, ans);
	}


	return 0;
}