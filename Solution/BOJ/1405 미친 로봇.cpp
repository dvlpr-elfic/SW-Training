
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 31

using namespace std;

double percent[4];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
bool visited[SIZE][SIZE];

void input(int &n)
{
	cin >> n;
	for(int i=0; i<4; i++){
		cin >> percent[i];
		percent[i] /= 100.0;
	}
}

double travel(int depth, int x, int y, int n)
{
	if(depth == n){
		// base case
		return 1.0;
	}
	double ret = 0.0;
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(!visited[ny][nx]){
			visited[ny][nx] = true;
			ret += percent[i] * travel(depth+1, nx, ny, n);		// 다음 스텝에 갈 방향의 확률을 곱해서 더하기
			visited[ny][nx] = false;
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n;
	input(n);
	cout.precision(12);	cout << fixed;			// 소수점 12자리까지 출력
	visited[15][15] = true;						// 처음 시작점 방문표시
	cout << travel(0, 15, 15, n) << '\n';		// 맵 중앙부터 시작
	return 0;
}

