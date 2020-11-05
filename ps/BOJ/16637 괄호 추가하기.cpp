
/**
 * @author Jihoon Jang
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define INF 0x7FFFFFFF
#define SIZE 30

using namespace std;

bool check[SIZE];

bool isNum(char ch)
{
	return (ch >= '0' && ch <= '9');
}

void input(int &len, vector<int> &operand, vector<int> &operatorr)
{
	cin >> len;
	for(int i=0; i<len; i++){
		char ch;
		cin >> ch;
		if(isNum(ch)){
			operand.push_back(ch-'0');
		}
		else{
			operatorr.push_back(ch);
		}
	}
}

void erase(vector<int> &v, int pos)
{
	vector<int>::iterator it = v.begin()+pos;
	v.erase(it);
}

int cal(int op1, int op2, char operatorr)
{
	int ret = 0;
	switch(operatorr){
	case '+':
		ret = op1 + op2;
		break;
	case '-':
		ret = op1 - op2;
		break;
	case '*':
		ret = op1 * op2;
		break;
	default:
		break;
	}
	return ret;
}

int simulation(vector<int> operand, vector<int> operatorr, int n)
{
	for(int i=n-1; i>=0; i--){
		if(check[i]){
			operand[i] = cal(operand[i], operand[i+1], (char)operatorr[i]);
			erase(operand, i+1);
			erase(operatorr, i);
		}
	}
	int ret = operand[0];
	for(int i=0; i<operatorr.size(); i++){
		ret = cal(ret, operand[i+1], operatorr[i]);
	}
	return ret;
}

int solve(int depth, int n, int s, vector<int> &operand, vector<int> &operatorr)
{
	if(depth == n){
		// base case
		return simulation(operand, operatorr, n);
	}
	int ret = -INF;
	for(int i=s; i<n; i++){
		int next = i+1;
		for(int tf=0; tf<2; tf++){
			if(i>0 && check[i-1]){
				check[i] = false;
			}
			else{
				check[i] = tf;
			}
			ret = max(ret, solve(depth+1, n, next, operand, operatorr));
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int len;
	vector<int> operand, operatorr;
	input(len, operand, operatorr);
	cout << solve(0, len/2, 0, operand, operatorr) << '\n';
	
	return 0;
}

