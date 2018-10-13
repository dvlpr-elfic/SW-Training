

#include <iostream>
#include <vector>

#define INF 100000000

using namespace std;

long maximum;
long minimum;

void dfs(int depth, vector<int> &op, vector<int> &operand, long value, int n)
{
	if(depth == n){
		if(value > maximum)
			maximum = value;
		if(value < minimum)
			minimum = value;
		return;
	}
	if(op[0]){
		op[0]--;
		dfs(depth+1, op, operand, value + operand[depth+1], n);
		op[0]++;
	}
	if(op[1]){
		op[1]--;
		dfs(depth+1, op, operand, value - operand[depth+1], n);
		op[1]++;
	}
	if(op[2]){
		op[2]--;
		dfs(depth+1, op, operand, value * operand[depth+1], n);
		op[2]++;
	}
	if(op[3]){
		op[3]--;
		dfs(depth+1, op, operand, value / operand[depth+1], n);
		op[3]++;
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
		minimum = INF;
		maximum = -INF;
		vector<int> op;
		vector<int> operand;
		int n;
		cin >> n;
		for(int i=0; i<4; i++){
			int temp;
			cin >> temp;
			op.push_back(temp);
		}
		for(int i=0; i<n; i++){
			int temp;
			cin >> temp;
			operand.push_back(temp);
		}
		dfs(0, op, operand, operand[0], n-1);
		cout << "#" << tc << " " << maximum - minimum << endl;
	}

	return 0;
}
