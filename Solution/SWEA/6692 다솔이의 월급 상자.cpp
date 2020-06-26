
/**
  * @author Jihoon Jang
  */

#include <iostream>

using namespace std;

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n;
		double ans = 0.0;
		cin >> n;
		while(n--){
			double p;
			int x;
			cin >> p >> x;
			ans += p*x;
		}
		cout << fixed;
		cout.precision(7);
		cout <<"#" << tc << ' ' << ans << '\n';
	}
	return 0;
}
