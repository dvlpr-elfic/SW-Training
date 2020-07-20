
/**
  * @author Jihoon Jang
  * 138 min
  */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 0x3FFFFFFF

using namespace std;

typedef struct pnode
{
	int x, y;
	pnode(int x, int y):x(x), y(y){}
}pnode;

typedef struct snode
{
	int x, y, len;
	snode(int x, int y, int l):x(x), y(y), len(l){}
}snode;

typedef struct qnode
{
	int num, pos;
	qnode(int n, int p):num(n), pos(p){}
}qnode;

void input(int &n, vector<pnode> &person, vector<snode> &stair, int &cnt)
{
	cin >> n;
	cnt = 0;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			int tmp;
			cin >> tmp;
			if(!tmp)
				continue;
			if(tmp == 1){
				person.push_back(pnode(x, y));
			}
			else{
				stair.push_back(snode(x, y, tmp));
			}
		}
	}
	cnt = person.size();
}

void setDistance(vector<pnode> &person, vector<snode> &stair, vector<int> &target, vector<int> &dist)
{
	int len = person.size();
	for(int i=0; i<len; i++){
		dist.push_back(abs(person[i].x - stair[target[i]].x) + abs(person[i].y - stair[target[i]].y));
	}
}

void _move(vector<snode> &stair, vector<int> &target, vector<int> &dist, int time, int &cnt, queue<qnode> *q)
{
	for(int i=0; i<2; i++){
		int len = q[i].size();
		for(int j=0; j<len; j++){
			int num = q[i].front().num, pos = q[i].front().pos+1;	q[i].pop();
			if(pos > stair[target[num]].len){
				cnt--;
			}
			else{
				q[i].push(qnode(num, pos));
			}
		}
	}
	int len = target.size();
	for(int i=0; i<len; i++){
		if(!dist[i])
			continue;
		if(dist[i] == time){
			if(q[target[i]].size() < 3){
				dist[i] = 0;
				q[target[i]].push(qnode(i, 0));
			}
		}
		else if(dist[i] < time){
			if(q[target[i]].size() < 3){
				dist[i] = 0;
				q[target[i]].push(qnode(i, 1));
			}
		}
	}
}

bool isComplete(int cnt, queue<qnode> *q)
{
	return (!cnt && q[0].empty() && q[1].empty());
}

int simulation(vector<int> &target, vector<pnode> &person, vector<snode> &stair, int cnt)
{
	int ret = 2;
	vector<int> dist;
	queue<qnode> q[2];
	setDistance(person, stair, target, dist);
	while(!isComplete(cnt, q)){
		_move(stair, target, dist, ret++, cnt, q);
	}
	return ret-1;
}

int solve(int depth, vector<int> &target, vector<pnode> &person, int &cnt, vector<snode> &stair)
{
	if(depth == person.size()){
		return simulation(target, person, stair, cnt);
	}
	int ret = INF;
	for(int i=0; i<2; i++){
		target.push_back(i);
		ret = min(ret, solve(depth+1, target, person, cnt, stair));
		target.pop_back();
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		int n, cnt;
		vector<pnode> person;
		vector<snode> stair;
		vector<int> target;
		input(n, person, stair, cnt);
		cout << '#' << tc << ' ' << solve(0, target, person, cnt, stair) << '\n';
	}
	return 0;
}

