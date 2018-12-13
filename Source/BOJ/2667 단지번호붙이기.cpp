
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <vector>
#include <algorithm>

#define SIZE 50

using namespace std;

int map[SIZE][SIZE];
int visited[SIZE][SIZE];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

bool isWall(int x, int y, int n)
{
	return (x<0 || y<0 || x>=n || y>=n);
}

bool compare(const int &n1, const int &n2)
{
	return (n1 < n2);
}

void dfs(int x, int y, int n, int group_number, int &cnt)
{
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(isWall(nx, ny, n))
			continue;
		if(!visited[ny][nx] && map[ny][nx]){
			visited[ny][nx] = group_number;
			cnt++;
			dfs(nx, ny, n, group_number, cnt);
		}
	}
}

void setComplex(vector<int> &complex, int n)
{
	int group_number = 1;
	for(int y=0; y<n; y++){
		for(int x=0; x<n; x++){
			if(map[y][x] && !visited[y][x]){
				int cnt = 1;
				visited[y][x] = group_number;
				dfs(x, y, n, group_number++, cnt);
				complex.push_back(cnt);
			}
		}
	}
}

void solve(int n)
{
	vector<int> complex;
	setComplex(complex, n);
	sort(complex.begin(), complex.end(), compare);
	cout << complex.size() << endl;
	for(int i=0; i<complex.size(); i++){
		cout << complex[i] << endl;
	}
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			char ch;
			cin >> ch;
			map[i][j] = ch - '0';
		}
	}
	solve(n);
	return 0;
}