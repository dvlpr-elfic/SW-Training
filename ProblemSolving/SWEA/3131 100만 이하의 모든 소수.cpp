
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>

#define MAX 1000001

using namespace std;

bool table[MAX];

void setting(vector<int> &v)
{
	for(int i=2; i<MAX; i++){
		if(!table[i]){
			v.push_back(i);
			table[i] = true;
			for(int j=2*i; j<MAX; j+=i){
				table[j] = true;
			}
		}
	}
}

void print(vector<int> &v)
{
	int len = v.size();
	for(int i=0; i<len; i++){
		cout << v[i] << ' ';
	}
	cout << '\n';
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	vector<int> v;
	setting(v);
	print(v);
	return 0;
}
