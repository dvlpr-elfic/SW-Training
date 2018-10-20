
/**
 * @author : Jihoon Jang
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

#define MAP_SIZE 101

using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};		// 상 하 좌 우

int map[MAP_SIZE][MAP_SIZE];
int visited[MAP_SIZE][MAP_SIZE];

typedef struct Swarm
{
	int x, y, n, dir, number;
	Swarm(int _x, int _y, int _n, int _dir, int _number)
	{
		x = _x, y = _y, n = _n, dir = _dir, number = _number;
	}
	Swarm(void)
	{
		x = y = n = dir = number = 0;
	}
}Swarm;

int counting(vector<Swarm> &list)
{
	int res = 0;
	for(int i=0; i<list.size(); i++){
		res += list[i].n;
	}
	return res;
}

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

void die(vector<Swarm> &list, int p)
{
	map[list[p].y][list[p].x] -= list[p].number;
	visited[list[p].y][list[p].x]--;
	vector<Swarm>::iterator pos = list.begin() + p;
	list.erase(pos);
}

void Scan(vector<Swarm> &list, int n)
{
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(visited[y][x] > 1){
				int maximum = 0, max_index = 0, temp = 0;
				for(int i=0; i<list.size(); i++){
					if(list[i].n){
						if(list[i].x == x && list[i].y == y){
							temp += list[i].n;
							if(list[i].n > maximum)						// 최대값 갱신
								maximum = list[i].n, max_index = i;
						}
					}
				}
				list[max_index].n = temp;
				for(int i=0; i<list.size(); i++){
					if(list[i].x == x && list[i].y == y && list[i].n != temp){
						die(list, i--);
					}
				}
			}
		}
	}
}

bool isInDrug(Swarm& swarm, int n)
{
	int nx = swarm.x + dx[swarm.dir];
	int ny = swarm.y + dy[swarm.dir];
	if(isWall(nx, ny, n))
		return true;
	return false;
}

void eatDrug(vector<Swarm> &list, int &p)
{

	switch(list[p].dir){
	case 0:	list[p].dir = 1;	break;
	case 1:	list[p].dir = 0;	break;
	case 2:	list[p].dir = 3;	break;
	case 3:	list[p].dir = 2;	break;
	default:
		break;
	}
	list[p].n /= 2;
	if(list[p].n == 0){
		die(list, p--);
	}
}

void Go(Swarm &swarm)
{
	int nx = swarm.x + dx[swarm.dir];
	int ny = swarm.y + dy[swarm.dir];
	map[swarm.y][swarm.x] -= swarm.number;
	visited[swarm.y][swarm.x]--;
	map[ny][nx] += swarm.number;
	visited[ny][nx]++;
	swarm.x = nx, swarm.y = ny;
}

void print(vector<Swarm> &list, int n)
{
	cout << "----------------------------------------------------------------------------" << endl;
	int temp[MAP_SIZE][MAP_SIZE] = {0, };
	for(int i=0; i<list.size(); i++){
		temp[list[i].y][list[i].x] = list[i].number+1;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout.width(3);
			cout << temp[i][j];
		}
		cout << endl;
	}
	cout << "----------------------------------------------------------------------------" << endl;
}


void Move(vector<Swarm> &list, int m, int n)
{
	while(m--){
		int len = list.size();
		for(int i=0; i<len; i++){
			if(list[i].n == 0){
				die(list, i);
				continue;
			}
			Go(list[i]);
			if(isInDrug(list[i], n)){
				eatDrug(list, i);
			}
		}
		Scan(list, n);
	}
}

void init(void)
{
	memset(map, 0, sizeof(map));
	memset(visited, 0, sizeof(visited));
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		int n, m, k;
		cin >> n >> m >> k;
		int ans = 0;
		vector<Swarm> list;
		for(int i=0; i<k; i++){
			int x, y, n, dir;
			cin >> y >> x >> n >> dir;
			list.push_back(Swarm(x, y, n, dir-1, i));
			visited[y][x]++;
			map[y][x] += i;
		}
		Scan(list, n);
		Move(list, m, n);
		ans = counting(list);
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
