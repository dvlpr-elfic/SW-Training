
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>

#define MAX 50

using namespace std;

bool picked[MAX];
int table[MAX];

void printAns(vector<int> &v)
{
	int n = v.size();
	for(int i=0; i<n; i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

void dfs(int depth, int k, vector<int> &v, int s)
{
	if(depth == 6){
		// base case
		printAns(v);
		return;
	}
	for(int i=s; i<k; i++){
		if(!picked[i]){
			picked[i] = true;
			v.push_back(table[i]);
			dfs(depth+1, k, v, i+1);
			picked[i] = false;
			v.pop_back();
		}
	}
}

void solve(void)
{
	while(1){
		int k;
		cin >> k;
		if(!k)
			return;
		for(int i=0; i<k; i++){
			cin >> table[i];
		}
		vector<int> v;
		dfs(0, k, v, 0);
		cout << endl;
	}
}



int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	solve();
	return 0;
}
