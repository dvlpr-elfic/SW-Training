
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define SIZE 1000001

using namespace std;

void input(int &len1, int &len2, int *arr1, int *arr2)
{
	cin >> len1 >> len2;
	for(int i=0; i<len1; i++)
		cin >> arr1[i];
	for(int i=0; i<len2; i++)
		cin >> arr2[i];
}

bool isOver(int p1, int p2, int len1, int len2)
{
	return (p1 >= len1 || p2 >= len2);
}

void print(int len, int* ans)
{
	for(int i=0; i<len; i++)
		cout << ans[i] << ' ';
	cout << '\n';
}

void solve(int len1, int len2, int *arr1, int *arr2)
{
	int *ans = new int[len1+len2];
	int p1=0, p2=0, idx=0;
	while(!isOver(p1, p2, len1, len2)){
		if(arr1[p1] <= arr2[p2])
			ans[idx++] = arr1[p1++];
		else
			ans[idx++] = arr2[p2++];
	}
	if(p2 < len2)
		for( ; p2 < len2; p2++)
			ans[idx++] = arr2[p2];
	else if(p1 < len1)
		for( ; p1 < len1; p1++)
			ans[idx++] = arr1[p1];
	print(idx, ans);
	delete[] ans;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int len1, len2;
	int arr1[SIZE];
	int arr2[SIZE];
	input(len1, len2, arr1, arr2);
	solve(len1, len2, arr1, arr2);
	return 0;
}

