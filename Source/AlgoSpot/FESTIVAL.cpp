
/**
 * @author Jihoon Jang
 */

#include <iostream>
#include <algorithm>

#define MAX_SIZE 1001

using namespace std;

void calPay(int *arr, int size, int n, double &ans)
{
	for(int s=0; s<=size-n; s++){
		int temp = 0;
		for(int i=s; i<s+n; i++){
			temp += arr[i];
		}
		double avg = (double)temp/(double)n;
		ans = min(ans, avg);
	}
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n, l;
		double ans = 987654321.0;
		int arr[MAX_SIZE] = {0, };
		cin >> n >> l;
		for(int i=0; i<n; i++)
			cin >> arr[i];
		for(int i=l; i<=n; i++){
			calPay(arr, n, i, ans);
		}
		cout << fixed;
		cout.precision(20);
		cout << ans << endl;
		
	}

	return 0;
}
