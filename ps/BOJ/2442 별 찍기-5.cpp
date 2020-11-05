
/**
  * @author Jihoon Jang
  */

#include <iostream>

using namespace std;

void solve(int n)
{
	int blank = n-1;
	for(int i=0; i<n; i++){
		for(int j=0; j<blank; j++){
			cout << " ";
		}
		blank--;
		for(int k=0; k<2*i+1; k++){
			cout << '*';
		}
		cout << endl;
	}
}

int main(void)
{
	int n;
	cin >> n;
	solve(n);
	return 0;
}
