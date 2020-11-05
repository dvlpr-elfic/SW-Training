
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define Q_SIZE 1000001
#define SIZE 1001

using namespace std;

typedef struct qnode
{
	int x, y, date;
	qnode(void):x(0), y(0), date(0){}
	qnode(int x, int y, int d):x(x), y(y), date(d){}
}qnode;

typedef struct queue
{
	int head, tail;
	qnode arr[Q_SIZE];
	queue(void):head(0), tail(0){}
	void push(qnode item)
	{
		arr[++tail] = item;
	}
	void pop(void)
	{
		head++;
	}
	qnode front(void)
	{
		return arr[head+1];
	}
	bool empty(void)
	{
		return (head == tail);
	}
	int size(void)
	{
		return (tail-head);
	}
}queue;

int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void input(int &w, int &h, int &cnt, queue &q)
{
	cin >> w >> h;
	cnt = w*h;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			cin >> map[y][x];
			if(map[y][x] == 1){
				q.push(qnode(x, y, 0));
				visited[y][x] = true;
			}
			else if(map[y][x] == -1){
				cnt--;
			}
		}
	}
}

bool isOut(int x, int y, int h, int w)
{
	return (x<0 || y<0 || x>=w || y>=h);
}

bool isEmpty(int x, int y)
{
	return (map[y][x] == -1);
}

int maxx(int n1, int n2)
{
	int flag = n1 - n2;
	if(flag > 0)
		return n1;
	else
		return n2;
}

int solve(int h, int w, int cnt, queue &q)
{
	int ret = 0;
	if(q.size() == cnt){
		return ret;
	}
	while(!q.empty()){
		int len = q.size();
		while(len--){
			int x = q.front().x, y = q.front().y, date = q.front().date;	q.pop();
			cnt--;
			ret = maxx(ret, date);
			int ndate = date+1;
			for(int dir=0; dir<4; dir++){
				int nx = x + dx[dir];
				int ny = y + dy[dir];
				if(isOut(nx, ny, h, w))	continue;
				if(isEmpty(nx, ny))	continue;
				if(visited[ny][nx])	continue;
				visited[ny][nx] = true;
				q.push(qnode(nx, ny, ndate));
			}
		}
	}
	if(cnt){
		ret = -1;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int h, w, cnt;
	queue q;
	input(w, h, cnt, q);
	cout << solve(h, w, cnt, q) << '\n';
	return 0;
}

