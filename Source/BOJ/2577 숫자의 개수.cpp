
/**
  * @author Jihoon Jang
  */

#include <iostream>

using namespace std;

int table[10];

void setDigit(long n)
{
	if(n == 0)
		// base case
		return;
	table[n%10]++;
	setDigit(n/10);
}

void print(void)
{
	for(int i=0; i<10; i++){
		cout << table[i] << endl;
	}

}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	long a, b, c;
	cin >> a >> b >> c;
	long temp = a*b*c;
	setDigit(temp);
	print();
	return 0;
}
