
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <queue>

#define SIZE 4001

using namespace std;

typedef struct anode
{
	int x, y, dir, k;
	anode(int x, int y, int d, int k):x(x), y(y), dir(d), k(k){}
}anode;

typedef struct qnode
{
	int x, y;
	qnode(int x, int y):x(x), y(y){}
}qnode;

int map[SIZE][SIZE];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void input(int &n, vector<anode> &atom)
{
	cin >> n;
	for(int i=0; i<n; i++){
		int x, y, dir, k;
		cin >> x >> y >> dir >> k;
		x = 2*x+2000;
		y = (-2)*y+2000;
		atom.push_back(anode(x, y, dir, k));
		map[y][x]++;
	}
}

bool isCrash(int x, int y)
{
	return (map[y][x] == 1);
}

bool isOut(int x, int y)
{
	return (x<0 || y<0 || x>=SIZE || y>=SIZE);
}

void setNextPos(int &nx, int &ny, int x, int y, int dir)
{
	nx = x + dx[dir], ny = y + dy[dir];
}

void kill(int &idx, vector<anode> &atom)
{
	int x = atom[idx].x, y = atom[idx].y;
	map[y][x]--;
	vector<anode>::iterator it = atom.begin()+idx;
	atom.erase(it);
	idx--;
}

void simulation(vector<anode> &atom, queue<qnode> &crashq)
{
	for(int i=0; i<atom.size(); i++){
		int nx, ny;
		setNextPos(nx, ny, atom[i].x, atom[i].y, atom[i].dir);
		if(isOut(nx, ny)){
			kill(i, atom);
			continue;
		}
		if(isCrash(nx, ny)){
			crashq.push(qnode(nx, ny));
		}
		map[atom[i].y][atom[i].x]--, map[ny][nx]++;
		atom[i].x = nx, atom[i].y = ny;
	}
}

bool isSamePos(int x1, int x2, int y1, int y2)
{
	return (x1 == x2 && y1 == y2);
}

int crash(queue<qnode> &q, vector<anode> &atom)
{
	int ret = 0;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y;	q.pop();
		for(int i=0; i<atom.size(); i++){
			if(isSamePos(x, atom[i].x, y, atom[i].y)){
				ret += atom[i].k;
				kill(i, atom);
			}
		}
	}
	return ret;
}

int solve(vector<anode> &atom)
{
	int ret = 0;
	while(!atom.empty()){
		queue<qnode> crashq;
		simulation(atom, crashq);
		ret += crash(crashq, atom);
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
		int n;
		vector<anode> atom;
		input(n, atom);
		cout << '#' << tc << ' ' << solve(atom) << '\n';
	}
	return 0;
}

