
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct vnode
{
	int hp, weight;
	vnode(int h, int w):hp(h), weight(w){}
}vnode;

int ans;

void input(int &n, vector<vnode> &agg)
{
	cin >> n;
	for(int i=0; i<n; i++){
		int hp, weight;
		cin >> hp >> weight;
		agg.push_back(vnode(hp, weight));
	}
}

bool isCrashed(int idx, vector<vnode> &agg)
{
	return (agg[idx].hp <= 0);
}

int picking(int pre, int n, vector<vnode> &agg)
{
	for(int i=pre+1; i<n; i++){
		if(!isCrashed(i, agg))
			return i;
	}
	return -1;
}

bool isEnd(int cur, int n)
{
	return (cur < 0 || cur >= n);
}

void hit(int cur, int next, vector<vnode> &agg)
{
	agg[cur].hp -= agg[next].weight;
	agg[next].hp -= agg[cur].weight;
}

void unhit(int cur, int next, vector<vnode> &agg)
{
	agg[cur].hp += agg[next].weight;
	agg[next].hp += agg[cur].weight;
}

int counting(int n, vector<vnode> &agg)
{
	int ret = 0;
	for(int i=0; i<n; i++){
		if(isCrashed(i, agg))
			ret++;
	}
	return ret;
}

void solve(int n, int pre, vector<vnode> &agg, int &cnt)
{
	int cur = picking(pre, n, agg);
	if(isEnd(cur, n)){
		ans = max(ans, cnt);
		return;
	}
	for(int i=0; i<n; i++){
		if(cur == i)	continue;
		if(isCrashed(i, agg))	continue;
		hit(cur, i, agg);
		cnt = counting(n, agg);
		solve(n, cur, agg, cnt);
		unhit(cur, i, agg);
		cnt = counting(n, agg);
	}
	ans = max(ans, cnt);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, cnt = 0;
	vector<vnode> agg;
	input(n, agg);
	solve(n, -1, agg, cnt);
	cout << ans << '\n';
	return 0;
}

