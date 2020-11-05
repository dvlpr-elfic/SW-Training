
/**
  * @author Jihoon Jang
  * 75min
  */

#include <iostream>
#include <queue>

#define SIZE 101

using namespace std;

typedef struct mnode
{
	int time, turn;
	mnode(int time, int turn):time(time), turn(turn){}
}mnode;

typedef struct snode
{
	int x, y;
	snode(int x, int y):x(x), y(y){}
}snode;

bool apple[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void input(int &n, queue<mnode> &manual)
{
	int k, l;
	cin >> n >> k;
	while(k--){
		int x, y;
		cin >> y >> x;
		apple[y-1][x-1] = true;
	}
	cin >> l;
	int pre = 0;
	while(l--){
		int t, turn;
		char ch;
		cin >> t >> ch;
		(ch == 'L') ? (turn = 3) : (turn = 1);
		manual.push(mnode(t-pre, turn));
		pre = t;
	}
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

bool oneStep(deque<snode> &snake, int dir, int n)
{
	snode head = snake.front();
	int nx = head.x + dx[dir];
	int ny = head.y + dy[dir];
	if(isWall(nx, ny, n))
		return false;
	if(visited[ny][nx])
		return false;
	snake.push_front(snode(nx, ny));
	visited[ny][nx] = true;
	if(!apple[ny][nx]){
		snode tail = snake.back();
		snake.pop_back();
		visited[tail.y][tail.x] = false;
	}
	else
		apple[ny][nx] = false;
	return true;
}

int solve(queue<mnode> &manual, int n)
{
	int ret = 1;
	int dir = 1;
	deque<snode> snake;
	snake.push_front(snode(0, 0));
	while(!manual.empty()){
		int time = manual.front().time, turn = manual.front().turn;	manual.pop();
		int t = 1;
		while(1){
			if(t++ > time)
				break;
			if(!oneStep(snake, dir, n)){
				return ret;
			}
			ret++;
		}
		dir = (dir+turn)%4;
	}
	while(oneStep(snake, dir, n)){
		ret++;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n;
	queue<mnode> manual;
	input(n, manual);
	cout << solve(manual, n) << '\n';
	return 0;
}

