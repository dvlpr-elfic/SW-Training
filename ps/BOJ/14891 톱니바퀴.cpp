
/**
  * @author Jihoon Jang
  * 60min
  */

#include <iostream>
#include <queue>
#include <memory.h>

#define SIZE 101
#define right 2
#define left 6

using namespace std;

typedef struct cnode
{
	int idx, dir;
}cnode;

int delta[] = {-1, 1};
bool visited[6];

void input(deque<int> *gear, int &k, cnode *command)
{
	for(int i=1; i<=4; i++){
		for(int j=0; j<8; j++){
			char ch;
			cin >> ch;
			gear[i].push_back(ch-'0');
		}
	}
	cin >> k;
	for(int i=0; i<k; i++){
		int idx, dir;
		cin >> idx >> dir;
		command[i].idx = idx, command[i].dir = ++dir;
	}
}

bool isOut(int i)
{
	return (i < 1 || i > 4);
}

void cw(deque<int> &g)
{
	int tmp = g.back();	g.pop_back();
	g.push_front(tmp);
}

void ccw(deque<int> &g)
{
	int tmp = g.front();	g.pop_front();
	g.push_back(tmp);
}

void turn(int dir, deque<int> &g)
{
	dir ? cw(g) : ccw(g);
}

void execute(int cur, int dir, deque<int> *gear)
{
	visited[cur] = true;
	for(int i=0; i<2; i++){
		int next = cur + delta[i];
		if(isOut(next))
			continue;
		if(visited[next])
			continue;
		if(next < cur){
			if(gear[next][right] != gear[cur][left])
				execute(next, !dir, gear);
		}
		else{
			if(gear[next][left] != gear[cur][right])
				execute(next, !dir, gear);
		}
	}
	turn(dir, gear[cur]);
}

int getScore(deque<int> *gear)
{
	int ret = 0;
	for(int i=1, s=1; i<=4; i++, s<<=1){
		if(gear[i].front())
			ret += s;
	}
	return ret;
}

int solve(deque<int> *gear, cnode *command, int k)
{
	for(int i=0; i<k; i++){
		memset(visited, 0, sizeof(visited));
		execute(command[i].idx, command[i].dir, gear);
	}
	return getScore(gear);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	deque<int> gear[6];
	int k;
	cnode command[SIZE];
	input(gear, k, command);
	cout << solve(gear, command, k);
	return 0;
}

