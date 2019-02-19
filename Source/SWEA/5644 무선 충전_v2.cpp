
/**
  * @author Jihoon Jang
  * 77min
  */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct cnode
{
	int x, y, coverage, performance;
	cnode(int x, int y, int c, int p):x(x), y(y), coverage(c), performance(p){}
}cnode;

typedef struct pos
{
	int x, y;
}pos;

int dx[] = {0, 0, 1, 0, -1};
int dy[] = {0, -1, 0, 1, 0};

void input(int &m, int &n, queue<int> *route, vector<cnode> &charger, pos *user)
{
	cin >> m >> n;
	route[0].push(0);
	route[1].push(0);
	for(int i=0; i<2; i++){
		for(int j=0; j<m; j++){
			int dir;
			cin >> dir;
			route[i].push(dir);
		}
	}
	for(int i=0; i<n; i++){
		int x, y, c, p;
		cin >> x >> y >> c >> p;
		charger.push_back(cnode(x-1, y-1, c, p));
	}
	user[0].x = user[0].y = 0;
	user[1].x = user[1].y = 9;
}

void _move(pos *user, queue<int> *route)
{
	for(int i=0; i<2; i++){
		int dir = route[i].front();	route[i].pop();
		user[i].x += dx[dir];
		user[i].y += dy[dir];
	}
}

bool isInArea(pos &upos, cnode &bc)
{
	return ((abs(upos.x - bc.x) + abs(upos.y - bc.y)) <= bc.coverage);
}

void setChargerList(vector<int> *chargerList, int n, pos *user, vector<cnode> &charger)
{
	for(int i=0; i<2; i++){
		for(int j=0; j<n; j++){
			if(isInArea(user[i], charger[j])){
				chargerList[i].push_back(j);
			}
		}
	}
}

int getMax(vector<int> *chargerList, vector<cnode> &charger)
{
	int ret = 0;
	if(!chargerList[0].size() || !chargerList[1].size()){
		int maxx[2] = {0, };
		for(int i=0; i<2; i++){
			for(int j=0; j<chargerList[i].size(); j++){
				maxx[i] = max(maxx[i], charger[chargerList[i][j]].performance);
			}
		}
		ret = maxx[0]+maxx[1];
	}
	else{
		for(int i=0; i<chargerList[0].size(); i++){
			for(int j=0; j<chargerList[1].size(); j++){
				if(chargerList[0][i] == chargerList[1][j]){
					ret = max(ret, charger[chargerList[0][i]].performance);
				}
				else{
					ret = max(ret, charger[chargerList[0][i]].performance + charger[chargerList[1][j]].performance);
				}
			}
		}
	}
	return ret;
}

int getCharge(int n, pos *user, vector<cnode> &charger)
{
	vector<int> chargerList[2];
	setChargerList(chargerList, n, user, charger);
	return getMax(chargerList, charger);
}

int solve(int m, pos *user, queue<int> *route, int n, vector<cnode> &charger)
{
	int ret = 0;
	for(int i=0; i<=m; i++){
		_move(user, route);
		ret += getCharge(n, user, charger);
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
		int m, n;
		queue<int> route[2];
		vector<cnode> charger;
		pos user[2];
		input(m, n, route, charger, user);
		cout << '#' << tc << ' ' << solve(m, user, route, n, charger) << '\n';
	}
	return 0;
}

