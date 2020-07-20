
#include <iostream>
#include <memory.h>
#include <queue>

#define MAP_SIZE 12
#define MAX_AGE 500

using namespace std;

typedef struct qnode
{
	int x, y, age, n;
	qnode(int x, int y, int age, int n):x(x), y(y), age(age), n(n){}
}qnode;

long long map[MAX_AGE][MAP_SIZE][MAP_SIZE];		// ���̺��� 2�����迭
int refill[MAP_SIZE][MAP_SIZE];				// �ܿ￡ ����� �����ϴ� ��
int energy[MAP_SIZE][MAP_SIZE];				// ���� ����� ��

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};		// ��, ���, ��, ����, ��, ����, ��, �»�
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

void init(void)
{
	for(int y=1; y<MAP_SIZE; y++)
		for(int x=1; x<MAP_SIZE; x++)
			energy[y][x] = 5;
	memset(refill, 0, sizeof(refill));
	memset(map, 0, sizeof(map));
}


void input(int &n, int &m, int &k)
{
	cin >> n >> m >> k;				// nxn �迭, m���� �ʱ� ���� ����, k��
	for(int y=1; y<=n; y++)
		for(int x=1; x<=n; x++)
			cin >> refill[y][x];
	while(m--){						// ������ ������ ����
		int y, x, age;
		cin >> y >> x >> age;
		map[age][y][x]++;
		map[0][y][x]++;				// ��ġ���� ���� �� ����
	}
}

bool isScarce(int x, int y, int age)
{
	return (map[age][y][x]*age > energy[y][x]);
}

int getAlive(int x, int y, int age)
{
	return ((int)(energy[y][x] / age));
}

int getDie(int x, int y, int age, int alive)
{
	return (map[age][y][x] - alive);
}

void alivehandle(queue<qnode> &q)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, age = q.front().age, n = q.front().n;	q.pop();
		map[age+1][y][x] += n;
	}
}

void spring(queue<qnode> &dieq, queue<qnode> &aliveq, int n)
{
	for(int age=1; age<MAX_AGE; age++){
		for(int y=1; y<=n; y++){
			for(int x=1; x<=n; x++){
				if(!map[age][y][x])					// �ش� ����, ��ġ�� ������ ���� ����
					continue;
				int alive, die;
				if(isScarce(x, y, age)){					// ����� �����ϸ�
					alive = getAlive(x, y, age);			// ��Ƴ��� ���� ���
					die = getDie(x, y, age, alive);			// �״� ���� ���
					dieq.push(qnode(x, y, age, die));		// queue�� �ְ� ���߿� ó��
					aliveq.push(qnode(x, y, age, alive));	// queue�� �ְ� summer���� ó��
				}
				else{										// ����� ����ϸ�
					alive = map[age][y][x];					// �ش� ����, ��ġ�� �������� ��� ��Ƴ��� ����
					die = 0;								// �״� ������ ����
					aliveq.push(qnode(x, y, age, alive));	// ��Ƴ��� ������ queue�� �ְ� ���߿� ó��
				}
				energy[y][x] -= age*alive;
				map[age][y][x] = 0;							// ��Ƴ��� ������ �״� ���� ��� ó�������Ƿ� �ش� ����, ��ġ�� ���� �� ����
			}
		}
	}
	alivehandle(aliveq);									// queue�� �־��� ��Ƴ��� ���� ó��(���� ����)
}

void summer(queue<qnode> &q)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, age = q.front().age, n = q.front().n;	q.pop();
		int add = age/2;									// ������ ���ݸ�ŭ ����� �ȴ�
		energy[y][x] += add*n;								// ���� �� ��ŭ ���ؼ� ��п� ���ϱ�
		map[0][y][x] -= n;									// �ش� ��ġ�� �� ���� �� ����
	}
}

void spread(int x, int y, int age)
{
	for(int i=0; i<8; i++){				// ������ ������� ����(1��1������ �����ϹǷ� 0���̳� 0���� ���� �־ ������� ����)
		int nx = x + dx[i];				// 8�������� ������
		int ny = y + dy[i];
		map[1][ny][nx] += map[age][y][x];				// 1�� ���� ����
		map[0][ny][nx] += map[age][y][x];							// �ش� ��ġ�� �� ���� �� ���ϱ�
	}
}

void fall(int n)
{
	for(int age=5; age<MAX_AGE; age+=5){				// ���̰� 5�� ����̸� ����
		for(int y=1; y<=n; y++){
			for(int x=1; x<=n; x++){
				if(map[age][y][x]){						// �ش� ����, ��ġ�� ������ ������ �н�
					spread(x, y, age);
				}
			}
		}
	}
}

void winter(int n)
{
	for(int y=1; y<=n; y++){							// ��� ����
		for(int x=1; x<=n; x++){
			energy[y][x] += refill[y][x];
		}
	}
}

int counting(int n)
{
	int ret = 0;
	for(int y=1; y<=n; y++){
		for(int x=1; x<=n; x++){
			ret += map[0][y][x];					// 0�ε����� �� ��ġ�� �� ���� ���� �����صξ���
		}
	}
	return ret;
}

int solve(int n, int k)
{
	while(k--){
		queue<qnode> dieq;					// �״� ������ ó���ϱ� ���� queue
		queue<qnode> aliveq;				// ��Ƴ��� ������ ó���ϱ� ���� queue
		spring(dieq, aliveq, n);
		summer(dieq);
		fall(n);
		winter(n);
	}
	return counting(n);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, k;
	init();
	input(n, m, k);
	cout << solve(n, k) << endl;
	return 0;
}
