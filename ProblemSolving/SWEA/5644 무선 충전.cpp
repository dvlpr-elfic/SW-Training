
/**
 * @author : Jihoon Jang
 */

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>

#define MAX_M 110
#define MAP_SIZE 11
#define MAX_CHARGER 8
#define MAX(x, y) ((x) > (y) ? (x) : (y))

using namespace std;

int map[MAX_CHARGER][MAP_SIZE][MAP_SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

typedef struct CUS
{
	long charge;
	int x, y;
}CUS;

typedef struct DIR
{
	int dx;
	int dy;
}DIR;

typedef struct BC
{
	int performance, coverage;	// 번호, 성능, 범위
	int x, y;					// 충전기 위치
}BC;

typedef struct qnode
{
	int x, y, count;
}qnode;

bool isWall(int x, int y)
{
	return (x<=0 || y<=0 || x>=MAP_SIZE || y>=MAP_SIZE);
}

bool isOverLap(CUS *cus, int A)
{
	unsigned int base = 0x01;
	int a = 0, b = 0;
	for(int i=0; i<A; i++){
		if(map[i][cus[0].y][cus[0].x])
			a |= base;
		if(map[i][cus[1].y][cus[1].x])
			b |= base;
		base = base << 1;
	}
	return a&b;
}



void setChargeArea(BC *bc, int A)
{
	queue<qnode> q;
	for(int i=0; i<A; i++){
		queue<qnode> q;
		qnode first = {bc[i].x, bc[i].y, 0};
		q.push(first);
		while(!q.empty()){
			qnode item = q.front(); q.pop();
			map[i][item.y][item.x] = bc[i].performance;
			for(int dir=0; dir<4; dir++){
				int nx = item.x + dx[dir];
				int ny = item.y + dy[dir];
				if((!isWall(nx, ny)) && (item.count < bc[i].coverage)){
					if(!map[i][ny][nx]){
						qnode temp = {nx, ny, item.count+1};
						q.push(temp);
					}
				}
			}
		}
	}
}

long travel(CUS *cus, DIR route[][MAX_M], int M, int A)
{
	long charge = 0;
	for(int i=0; i<=M; i++){
		int res1 = 0, res2 = 0;
		if(isOverLap(cus, A)){
			for(int a=0; a<A; a++){
				for(int b=0; b<A; b++){
					if(a==b)
						res1 = MAX(res1, map[a][cus[0].y][cus[0].x]);
					else
						res1 = MAX(res1, map[a][cus[0].y][cus[0].x] + map[b][cus[1].y][cus[1].x]);
				}
			}
		}
		else{
			for(int j=0; j<A; j++){
				res1 = MAX(res1, map[j][cus[0].y][cus[0].x]);
				res2 = MAX(res2, map[j][cus[1].y][cus[1].x]);
			}
		}
		charge += res1 + res2;
		for(int k=0; k<2; k++){
			cus[k].x += route[k][i].dx;
			cus[k].y += route[k][i].dy;
		}
	}
	return charge;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		memset(map, 0, sizeof(map));
		int M, A;
		cin >> M >> A;
		DIR route[2][MAX_M] = {0, };
		for(int row=0; row<2; row++){						// 이동경로 입력
			for(int i=0; i<M; i++){
				int temp;
				cin >> temp;
				if(temp == 0)
					route[row][i].dx = 0, route[row][i].dy = 0;
				else if(temp == 1)
					route[row][i].dx = 0, route[row][i].dy = -1;
				else if(temp == 2)
					route[row][i].dx = 1, route[row][i].dy = 0;
				else if(temp == 3)
					route[row][i].dx = 0, route[row][i].dy = 1;
				else if(temp == 4)
					route[row][i].dx = -1, route[row][i].dy = 0;
			}
		}
		CUS cus[2] = {{0, 1, 1}, {0, 10, 10}};
		BC bc[MAX_CHARGER] = {0, };
		for(int i=0; i<A; i++){
			cin >> bc[i].x >> bc[i].y >> bc[i].coverage >> bc[i].performance;
		}
		setChargeArea(bc, A);
		long ans = travel(cus, route, M, A);
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
