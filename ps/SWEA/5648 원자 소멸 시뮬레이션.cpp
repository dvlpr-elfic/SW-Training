
/**
  * @author Jihoon Jang
  * 88 minutes
  */

#include <iostream>
#include <vector>
#include <memory.h>

#define SIZE 4001

using namespace std;

typedef struct atomtype
{
	int x, y, d, k;
	atomtype(int x, int y, int d, int k):x(x), y(y), d(d), k(k){}
}atomtype;

typedef struct crashtype
{
	int x, y;
	crashtype(int x, int y):x(x), y(y){}
}crashtype;

int map[SIZE][SIZE];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};		// »óÇÏÁÂ¿ì
int energy = 0;

void init(void)
{
	memset(map, 0, sizeof(map));
	energy = 0;
}

void input(int &n, vector<atomtype> &atom)
{
	cin >> n;
	for(int i=0; i<n; i++){
		int x, y, d, k;
		cin >> x >> y >> d >> k;
		x *= 2, y *= (-2);
		x += 2000, y += 2000;
		atom.push_back(atomtype(x, y, d, k));
		map[y][x]++;		
	}
}

bool isWall(int x, int y)
{
	return (x<0 || y<0 || x>=SIZE || y >= SIZE);
}

void killAtom(vector<atomtype> &atom, int idx)
{
	vector<atomtype>::iterator it = atom.begin() + idx;
	atom.erase(it);
}

void goHalfStep(vector<atomtype> &atom, vector<crashtype> &crashlist)
{
	for(int i=0; i<atom.size(); i++){
		int x = atom[i].x, y = atom[i].y, d = atom[i].d;
		int nx = x + dx[d];
		int ny = y + dy[d];
		if(isWall(nx, ny)){
			killAtom(atom, i);
			i--;
			map[y][x]--;
			continue;
		}
		if(map[ny][nx] == 1){
			crashlist.push_back(crashtype(nx, ny));
		}
		map[ny][nx]++, map[y][x]--;
		atom[i].x = nx, atom[i].y = ny;
	}
}

void crash(vector<crashtype> &crashlist, vector<atomtype> &atom)
{
	for(int i=0; i<crashlist.size(); i++){
		int x = crashlist[i].x, y = crashlist[i].y;
		if(map[y][x] > 0){
			for(int j=0; j<atom.size(); j++){
				if(atom[j].x == x && atom[j].y == y){
					energy += atom[j].k;
					killAtom(atom, j);
					j--;
					map[y][x]--;
				}
			}
		}
		else
			cout << "crash error\n";
	}
}

void solve(vector<atomtype> &atom)
{
	while(!atom.empty()){
		vector<crashtype> crashlist;
		goHalfStep(atom, crashlist);
		crash(crashlist, atom);
		crashlist.clear();
		goHalfStep(atom, crashlist);
		crash(crashlist, atom);
	}
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		int n;
		vector<atomtype> atom;
		input(n, atom);
		solve(atom);
		cout << "#" << tc << " " << energy << endl;
	}
	return 0;
}
