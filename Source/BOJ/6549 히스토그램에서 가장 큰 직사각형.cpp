
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long solve(long left, long right, vector<long> &h)
{
	if(left == right){
		// base case
		return h[left];
	}
	long mid = (left+right)/2;
	long ret = max(solve(left, mid, h), solve(mid+1, right, h));
	long low = mid, high = mid+1;
	long height = min(h[low], h[high]);
	ret = max(ret, height*2);
	while(left < low || right > high){
		if(right > high && ((low == left) || (h[low-1] < h[high+1]))){
			high++;
			height = min(height, h[high]);
		}
		else{
			low--;
			height = min(height, h[low]);
		}
		ret = max(ret, height*(high-low+1));
	}
	return ret;
}

bool input(vector<long> &h)
{
	long n;
	cin >> n;
	if(!n)
		return false;
	for(long i=0; i<n; i++){
		long temp;
		cin >> temp;
		h.push_back(temp);
	}
	return true;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	while(1){
		vector<long> h;
		if(!input(h))
			return 0;
		cout << solve(0, h.size()-1, h) << endl;
	}
	return 0;
}
