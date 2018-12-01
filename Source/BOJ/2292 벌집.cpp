
/**
  * @author Jihoon Jang
  */

#include <iostream>

using namespace std;

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n;
	cin >> n;
	int temp = 1;
	int delta = 6;
	int idx = 0;
	while(temp < n){
		temp += delta;
		delta += 6;
		idx++;
	}
	cout << idx+1 << '\n';
	return 0;
}
