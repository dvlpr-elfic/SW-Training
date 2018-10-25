
#include <stdio.h>
#include <queue>

#define MAP_SIZE 16

using namespace std;

void DeleteBuffer(void);
void input(char [][MAP_SIZE+1]);
bool isExistPath(char [][MAP_SIZE+1]);
bool bfs(char [][MAP_SIZE+1], pair<int, int>);

int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		DeleteBuffer();							/* 각 테스트케이스 번호는 쓸모없다 */
		char map[MAP_SIZE][MAP_SIZE+1] = {0, };
		input(map);
		int answer = isExistPath(map);
		printf("#%d %d\n", tc, answer);
	}
	return 0;
}

void DeleteBuffer(void)
{
	int tmp;
	scanf("%d", &tmp);
}

void input(char map[][MAP_SIZE+1])
{
	for(int i=0; i<MAP_SIZE; i++){
		scanf("%s", map[i]);
	}
}

bool isExistPath(char map[][MAP_SIZE+1])
{
	pair<int, int> start_point;
	for(int i=0; i<MAP_SIZE; i++){					/* 시작점 찾기 */
		for(int j=0; j<MAP_SIZE; j++){
			if(map[i][j] == '2'){
				map[i][j] = '1';
				start_point.first = i, start_point.second = j;
				break;
			}
		}
	}
	
	return bfs(map, start_point);
}

bool bfs(char map[][MAP_SIZE+1], pair<int, int> start)
{
	queue<pair<int, int>> q;
	q.push(start);
	char visited[MAP_SIZE][MAP_SIZE] = {0, };
	while(1){
		if(q.empty()){
			return false;
		}
		int i = q.front().first, j = q.front().second;
		q.pop();
		visited[i][j] = '.';
		if(map[i][j] == '3'){
			return true;
		}
		if(map[i+1][j] != '1' && !visited[i+1][j]){
			pair<int, int> temp(i+1, j);
			q.push(temp);
		}
		if(map[i-1][j] != '1' && !visited[i-1][j]){
			pair<int, int> temp(i-1, j);
			q.push(temp);
		}
		if(map[i][j+1] != '1' && !visited[i][j+1]){
			pair<int, int> temp(i, j+1);
			q.push(temp);
		}
		if(map[i][j-1] != '1' && !visited[i][j-1]){
			pair<int, int> temp(i, j-1);
			q.push(temp);
		}
	}
}
