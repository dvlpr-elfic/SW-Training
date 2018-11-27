
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <algorithm>

using namespace std;

int table[4] = {0, };
int operand[20] = {0, };
int maximum = -10000000001;
int minimum = 10000000001;

void input(int &n){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> operand[i];
	}
	for(int i=0; i<4; i++){
		cin >> table[i];
	}
}

void dfs(int depth, int n, int cur){
	if(depth == n){
		// base case
		maximum = max(maximum, cur);
		minimum = min(minimum, cur);
		return;
	}
	for(int i=0; i<4; i++){
		int op = table[i];
		if(op){
			table[i]--;
			if(i==0)
				dfs(depth+1, n, cur+operand[depth]);
			else if(i==1)
				dfs(depth+1, n, cur-operand[depth]);
			else if(i==2)
				dfs(depth+1, n, cur*operand[depth]);
			else if(i==3)
				dfs(depth+1, n, cur/operand[depth]);
			table[i]++;
		}
	}
}



int main(void){
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n;
	input(n);
	dfs(1, n, operand[0]);
	cout << maximum << '\n' << minimum << '\n';
	return 0;
}
