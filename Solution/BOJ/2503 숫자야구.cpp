
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

typedef struct vnode
{
	int arr[3];
	int strike, ball;
	vnode(int* a, int s, int b):strike(s), ball(b){memcpy(arr, a, sizeof(int)*3);}
}vnode;

bool visited[10];

void input(int &n, vector<vnode> &v)
{
	cin >> n;
	int arr[3];
	for(int i=0; i<n; i++){
		for(int k=0; k<3; k++){
			char ch;
			cin >> ch;
			arr[k] = ch - '0';
		}
		int strike, ball;
		cin >> strike >> ball;
		v.push_back(vnode(arr, strike, ball));
	}
}

int getStrike(int *arr, vnode &node, bool *check)
{
	int ret = 0;
	for(int i=0; i<3; i++){
		if(arr[i] == node.arr[i]){
			ret++;
			check[i] = true;
		}
	}
	return ret;
}

int getBall(int *arr, vnode &node, bool *check)
{
	int ret = 0;
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(i==j)	continue;
			if(check[i] || check[j])	continue;
			if(arr[i] == node.arr[j])
				ret++;
		}
	}
	return ret;
}

bool isCorrect(vector<vnode> &v, int *arr)
{
	int len = v.size();
	bool ret = true;
	for(int i=0; i<len; i++){
		bool check[3] = {0, };
		int strike = getStrike(arr, v[i], check);
		int ball = getBall(arr, v[i], check);
		if(strike != v[i].strike || ball != v[i].ball){
			ret = false;
			break;
		}
	}
	return ret;
}

int solve(int depth, int start, int n, int *arr, vector<vnode> &v)
{
	if(depth == n){
		// base case
		if(isCorrect(v, arr))
			return 1;
		else
			return 0;
	}
	int ret = 0;
	for(int val=1; val<=9; val++){
		if(visited[val])
			continue;
		visited[val] = true;
		arr[depth] = val;
		ret += solve(depth+1, val+1, n, arr, v);
		visited[val] = false;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	vector<vnode> v;
	input(n, v);
	int arr[3];
	cout << solve(0, 1, 3, arr, v) << '\n';
	return 0;
}
