
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

long long map[MAX_AGE][MAP_SIZE][MAP_SIZE];		// 나이별로 2차원배열
int refill[MAP_SIZE][MAP_SIZE];				// 겨울에 양분을 충전하는 양
int energy[MAP_SIZE][MAP_SIZE];				// 현재 양분의 양

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};		// 상, 우상, 우, 우하, 하, 좌하, 좌, 좌상
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
	cin >> n >> m >> k;				// nxn 배열, m개의 초기 나무 정보, k년
	for(int y=1; y<=n; y++)
		for(int x=1; x<=n; x++)
			cin >> refill[y][x];
	while(m--){						// 나무의 정보를 저장
		int y, x, age;
		cin >> y >> x >> age;
		map[age][y][x]++;
		map[0][y][x]++;				// 위치마다 나무 총 개수
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
				if(!map[age][y][x])					// 해당 나이, 위치에 나무가 없는 상태
					continue;
				int alive, die;
				if(isScarce(x, y, age)){					// 양분이 부족하면
					alive = getAlive(x, y, age);			// 살아남는 나무 계산
					die = getDie(x, y, age, alive);			// 죽는 나무 계산
					dieq.push(qnode(x, y, age, die));		// queue에 넣고 나중에 처리
					aliveq.push(qnode(x, y, age, alive));	// queue에 넣고 summer에서 처리
				}
				else{										// 양분이 충분하면
					alive = map[age][y][x];					// 해당 나이, 위치의 나무들은 모두 살아남는 나무
					die = 0;								// 죽는 나무는 없음
					aliveq.push(qnode(x, y, age, alive));	// 살아남는 나무들 queue에 넣고 나중에 처리
				}
				energy[y][x] -= age*alive;
				map[age][y][x] = 0;							// 살아남는 나무와 죽는 나무 모두 처리했으므로 해당 나이, 위치에 나무 수 삭제
			}
		}
	}
	alivehandle(aliveq);									// queue에 넣었던 살아남는 나무 처리(나이 증가)
}

void summer(queue<qnode> &q)
{
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, age = q.front().age, n = q.front().n;	q.pop();
		int add = age/2;									// 나이의 절반만큼 양분이 된다
		energy[y][x] += add*n;								// 나무 수 만큼 곱해서 양분에 더하기
		map[0][y][x] -= n;									// 해당 위치의 총 나무 수 빼기
	}
}

void spread(int x, int y, int age)
{
	for(int i=0; i<8; i++){				// 영역은 고려하지 않음(1행1열부터 시작하므로 0행이나 0열의 값이 있어도 사용하지 않음)
		int nx = x + dx[i];				// 8방향으로 퍼지기
		int ny = y + dy[i];
		map[1][ny][nx] += map[age][y][x];				// 1살 나무 생성
		map[0][ny][nx] += map[age][y][x];							// 해당 위치의 총 나무 수 더하기
	}
}

void fall(int n)
{
	for(int age=5; age<MAX_AGE; age+=5){				// 나이가 5의 배수이면 번식
		for(int y=1; y<=n; y++){
			for(int x=1; x<=n; x++){
				if(map[age][y][x]){						// 해당 나이, 위치에 나무가 없으면 패스
					spread(x, y, age);
				}
			}
		}
	}
}

void winter(int n)
{
	for(int y=1; y<=n; y++){							// 양분 충전
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
			ret += map[0][y][x];					// 0인덱스에 각 위치의 총 나무 수를 저장해두었음
		}
	}
	return ret;
}

int solve(int n, int k)
{
	while(k--){
		queue<qnode> dieq;					// 죽는 나무를 처리하기 위한 queue
		queue<qnode> aliveq;				// 살아남는 나무를 처리하기 위한 queue
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
