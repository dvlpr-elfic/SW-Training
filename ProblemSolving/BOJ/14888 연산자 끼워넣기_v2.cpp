
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <algorithm>

#define INF 0x7FFFFFFF

using namespace std;

void input(int &n, vector<int> &operand, vector<int> &operatorr)
{
	cin >> n;
	int temp;
	for(int i=0; i<n; i++){
		cin >> temp;
		operand.push_back(temp);
	}
	for(int i=0; i<4; i++){
		cin >> temp;
		operatorr.push_back(temp);
	}
}

void solve(int depth, int n, vector<int> &operand, vector<int> &operatorr, int &minn, int &maxx, int cur)
{
	if(depth == n-1){
		minn = min(minn, cur);
		maxx = max(maxx, cur);
		return;
	}
	if(operatorr[0]){
		operatorr[0]--;
		solve(depth+1, n, operand, operatorr, minn, maxx, cur+operand[depth+1]);
		operatorr[0]++;
	}
	if(operatorr[1]){
		operatorr[1]--;
		solve(depth+1, n, operand, operatorr, minn, maxx, cur-operand[depth+1]);
		operatorr[1]++;
	}
	if(operatorr[2]){
		operatorr[2]--;
		solve(depth+1, n, operand, operatorr, minn, maxx, cur*operand[depth+1]);
		operatorr[2]++;
	}
	if(operatorr[3]){
		operatorr[3]--;
		solve(depth+1, n, operand, operatorr, minn, maxx, cur/operand[depth+1]);
		operatorr[3]++;
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	vector<int> operand, operatorr;
	input(n, operand, operatorr);
	int minn = INF, maxx = -INF;
	solve(0, n, operand, operatorr, minn, maxx, operand[0]);
	cout << maxx << '\n' << minn << '\n';
	return 0;
}

