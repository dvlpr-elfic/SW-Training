
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 101
#define Q_SIZE 10001

using namespace std;

typedef struct qnode
{
	int x, y, speed, dir, size;
	qnode(int x, int y, int s, int d, int z):x(x), y(y), speed(s), dir(d), size(z){}
	qnode(void):x(0), y(0), speed(0), dir(0), size(0){}
}qnode;

typedef struct queue
{
	int head, tail, size;
	qnode arr[Q_SIZE];
	queue(void):head(0), tail(0), size(0){}
	void push(qnode input)
	{
		if(size == Q_SIZE){
			cout << "push error, queue is full\n";
			return;
		}
		arr[tail] = input;
		tail = (tail+1)%Q_SIZE;
		size++;
	}
	qnode front(void)
	{
		return arr[head];
	}
	void pop(void)
	{
		head = (head+1)%Q_SIZE;
		size--;
	}
	bool empty(void)
	{
		return (!size);
	}
}queue;

typedef struct mnode
{
	int speed, dir, size;
	mnode(void):speed(0), dir(0), size(0){}
	mnode(int s, int d, int z):speed(s), dir(d), size(z){}
}mnode;

mnode map[SIZE][SIZE];
int dx[] = {0, 0, 0, 1, -1};
int dy[] = {0, -1, 1, 0, 0};

void setMapNode(int x, int y, int speed, int dir, int size)
{
	mnode node(speed, dir, size);
	map[y][x] = node;
}

void input(int &h, int &w)
{
	int m;
	cin >> h >> w >> m;
	for(int i=0; i<m; i++){
		int x, y, speed, dir, size;
		cin >> y >> x >> speed >> dir >> size;
		setMapNode(x, y, speed, dir, size);
	}
}

bool isFisherArrive(int fisherPos, int w)
{
	return (fisherPos == w);
}

void erase(int x, int y)
{
	mnode clear;
	map[y][x] = clear;
}

bool isShark(int x, int y)
{
	return (map[y][x].size > 0);
}

int getPosTopSharkY(int h, int x)
{
	int ret = -1;
	for(int y=1; y<=h; y++){
		if(isShark(x, y)){
			ret = y;
			break;
		}
	}
	return ret;
}

int fishing(int &fisherPos, int h)
{
	fisherPos++;
	int ret = 0;
	int y = getPosTopSharkY(h, fisherPos);
	if(y>0){
		ret = map[y][fisherPos].size;
		erase(fisherPos, y);
	}
	return ret;
}

bool isOut(int x, int y, int h, int w)
{
	return (x<1 || y<1 || x>w || y>h);
}

void reverseDir(int &dir)
{
	int temp = dir;
	switch(temp){
	case 1:
		dir = 2;	break;
	case 2:
		dir = 1;	break;
	case 3:
		dir = 4;	break;
	case 4:
		dir = 3;	break;
	default:
		break;
	}
}

void setNextPos(int h, int w, int &x, int &y, int speed, int &dir)
{
	while(speed--){
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if(isOut(nx, ny, h, w)){
			reverseDir(dir);
			speed++;
			continue;
		}
		x = nx, y = ny;
	}
}

void moveShark(int h, int w)
{
	queue q;
	for(int y=1; y<=h; y++){
		for(int x=1; x<=w; x++){
			if(isShark(x, y)){
				int nx = x, ny = y;
				setNextPos(h, w, nx, ny, map[y][x].speed, map[y][x].dir);
				q.push(qnode(nx, ny, map[y][x].speed, map[y][x].dir, map[y][x].size));
				erase(x, y);
			}
		}
	}
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, speed = q.front().speed, dir = q.front().dir, size = q.front().size;	q.pop();
		if(map[y][x].size < size){
			setMapNode(x, y, speed, dir, size);
		}
	}
}

int solve(int h, int w)
{
	int fisherPos = 0;
	int ret = 0;
	while(!isFisherArrive(fisherPos, w)){
		ret += fishing(fisherPos, h);
		moveShark(h, w);
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int h, w;
	input(h, w);
	cout << solve(h, w) << '\n';
	return 0;
}

