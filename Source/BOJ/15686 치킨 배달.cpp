
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <algorithm>

#define INF 0x7FFFFFFF
#define SIZE 15

using namespace std;

typedef struct node
{
	int x, y;
	node(int x, int y):x(x), y(y){}
}node;

void input(int &n, int &m, vector<node> &house, vector<node> &chicken)
{
	cin >> n >> m;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			int temp;
			cin >> temp;
			if(temp == 1){
				house.push_back(node(x, y));
			}
			else if(temp == 2){
				chicken.push_back(node(x, y));
			}
		}
	}
}

int getDist(int x1, int x2, int y1, int y2)
{
	return (abs(x1-x2)+abs(y1-y2));
}

int cal(vector<node> &house, vector<node> &alive)
{
	int ret = 0;
	for(int i=0; i<house.size(); i++){
		int dist = INF;
		for(int j=0; j<alive.size(); j++){
			dist = min(dist, getDist(house[i].x, alive[j].x, house[i].y, alive[j].y));
		}
		ret += dist;
	}
	return ret;
}

int solve(int depth, int m, int s, vector<node> &house, vector<node> &alive, vector<node> &chicken)
{
	if(depth == m){
		// base case
		return cal(house, alive);
	}
	int ret = INF;
	int limit = (chicken.size()-1) - (m-1-depth);
	for(int i=s; i<=limit; i++){
		alive.push_back(chicken[i]);
		ret = min(ret, solve(depth+1, m, i+1, house, alive, chicken));
		alive.pop_back();
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n, m;
	vector<node> house, chicken, alive;
	input(n, m, house, chicken);
	cout << solve(0, m, 0, house, alive, chicken);
	return 0;
}

