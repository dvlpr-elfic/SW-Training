
/**
  * @author Jihoon Jang
  * 40 min
  */

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <memory.h>

#define SIZE 21

using namespace std;

typedef struct shark
{
	int x, y, level, eated;
}shark;

typedef struct node
{
	int x, y, d;
	node(int x, int y, int d):x(x), y(y), d(d){}
}node;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

void input(int &n, shark &s)
{
	cin >> n;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			int tmp;
			cin >> tmp;
			if(tmp == 9)
				s.x = x, s.y = y, s.level = 2, s.eated = 0;
			else
				map[y][x] = tmp;
		}
	}
}

bool compare(const node &arg1, const node &arg2)
{
	if(arg1.d == arg2.d){
		if(arg1.y == arg2.y){
			return (arg1.x < arg2.x);
		}
		else
			return (arg1.y < arg2.y);
	}
	else
		return (arg1.d < arg2.d);
}

bool isOut(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void setFishList(int n, shark &s, vector<node> &fishList)
{
	queue<node> q;
	q.push(node(s.x, s.y, 0));
	visited[s.y][s.x] = true;
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, d = q.front().d;	q.pop();
		if(map[y][x] && map[y][x] < s.level){
			fishList.push_back(node(x, y, d));
		}
		for(int i=0; i<4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(isOut(nx, ny, n))
				continue;
			if(!visited[ny][nx] && map[ny][nx] <= s.level){
				visited[ny][nx] = true;
				q.push(node(nx, ny, d+1));
			}
		}
	}
	sort(fishList.begin(), fishList.end(), compare);
}

void _move(shark &s, node &fish)
{
	s.x = fish.x, s.y = fish.y;
}

void levelUp(shark &s)
{
	s.eated++;
	if(s.eated == s.level){
		s.eated = 0;
		s.level++;
	}
}

void die(node &fish)
{
	map[fish.y][fish.x] = 0;
}

void eat(node &fish, shark &s)
{
	_move(s, fish);
	levelUp(s);
	die(fish);
}

int getTime(int n, shark &s)
{
	vector<node> fishList;
	memset(visited, 0, sizeof(visited));
	setFishList(n, s, fishList);
	if(fishList.empty())
		return 0;
	eat(fishList[0], s);
	return fishList[0].d;
}

int solve(int n, shark &s)
{
	int ret = 0;
	while(1){
		int t = getTime(n, s);
		if(!t)
			break;
		ret += t;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	shark s;
	input(n, s);
	cout << solve(n, s) << '\n';
	return 0;
}

