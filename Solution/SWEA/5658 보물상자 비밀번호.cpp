
/**
 * @author : Jihoon Jang
 */

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string.h>

using namespace std;

char hex2dec[256];

bool compare(const int &n1, const int &n2)
{
	return n1 > n2;
}


bool isNotFound(vector<int> &list, int target)
{
	int size = list.size();
	for(int i=0; i<size; i++){
		if(list[i] == target)
			return false;
	}
	return true;
}

void rotate(deque<char> &dq)
{
	dq.push_front(dq.back());
	dq.pop_back();
}

void makeList(deque<char> &dq, vector<int> &list, int n)
{
	int start = 0;
	int limit = n/4;
	for(int k=0; k<4; k++){
		int weight = 1;
		int temp = 0;
		for(int i=limit-1; i>=start; i--){
			temp += hex2dec[dq[i]] * weight;
			weight *= 16;
		}
		if(isNotFound(list, temp))
			list.push_back(temp);
		start = limit, limit += n/4;
	}
}

void solve(deque<char> &dq, vector<int> &list, int n, int k)
{
	int len = n/4;
	do{
		makeList(dq, list, n);
		rotate(dq);
	}while(len--);
	sort(list.begin(), list.end(), compare);
	cout << list[k-1] << endl;
}

int main(void)
{
	for(int i=0; i<10; i++){
		hex2dec[i+'0'] = i;
	}
	for(int i=0; i<6; i++){
		hex2dec[i+'A'] = i+10;
	}

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		deque<char> dq;
		vector<int> list;
		int n, k;
		cin >> n >> k;
		for(int i=0; i<n; i++){
			char temp;
			cin >> temp;
			dq.push_back(temp);
		}
		cout << "#" << tc << " ";
		solve(dq, list, n, k);
	}

	return 0;
}
