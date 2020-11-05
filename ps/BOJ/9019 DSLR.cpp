
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <queue>
#include <string>
#include <memory.h>

#define SIZE 10000

using namespace std;

bool visited[SIZE];
string command[4] = {"D", "S", "L", "R"};

typedef struct qnode
{
	string str;
	int n;
	qnode(string s, int n):str(s), n(n){}
}qnode;

void init(void)
{
	memset(visited, 0, sizeof(visited));
}

int execute(int n, int com)
{
	int ret = n;
	if(com == 0){
		ret = ret<<1;
		if(ret > 9999)
			ret %= 10000;
	}
	else if(com == 1){
		if(!ret)
			ret = 9999;
		else
			ret--;
	}
	else if(com == 2){
		ret *= 10;
		ret += (ret/10000);
		ret %= 10000;
	}
	else if(com == 3){
		ret += ((ret%10)*10000);
		ret /= 10;
	}
	return ret;
}

void bfs(int a, int b)
{
	queue<qnode> q;
	q.push(qnode("", a));
	visited[a] = true;
	while(!q.empty()){
		string str = q.front().str;	int n = q.front().n;	q.pop();
		if(n == b){
			cout << (str+"\n");
			return;
		}
		for(int i=0; i<4; i++){
			int next = execute(n, i);
			if(!visited[next]){
				visited[next] = true;
				q.push(qnode(str + command[i], next));
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		init();
		int a, b;
		cin >> a >> b;
		bfs(a, b);
	}
	return 0;
}

