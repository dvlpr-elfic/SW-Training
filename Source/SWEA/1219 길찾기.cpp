
/**
  * @author Jihoon Jang
  */

/*
	< �ð����⵵ ��� >
	��Ʈ��ŷ�� ���� �����Ƿ� ��带 �湮�ϴ� Ƚ���� �ִ밪�� ����� ������ ����
	�� ���� 2���� ���� ����, ���� 99�� ����
	�� �ִ� 198���� ��带 �湮
	��Ž���� Ǯ �� �ִ�!!
*/

#include <iostream>
#include <vector>
#include <memory.h>

#define GRAPH_SIZE 100

using namespace std;

bool visited[GRAPH_SIZE];

void init(void)
{
	memset(visited, 0, sizeof(visited));
}

void input(int &n, vector<int> *g)
{
	int tc;
	cin >> tc >> n;							// test case number, input size
	for(int i=0; i<n; i++){
		int parent, child;
		cin >> parent >> child;				// get edge data
		g[parent].push_back(child);			// set graph
	}
}

bool search(vector<int> *g, int cur)
{
	if(cur == 0){
		// first case
		visited[0] = true;
	}
	if(cur == 99){
		// base case
		// find path success
		return true;
	}
	int len = g[cur].size();
	for(int i=0; i<len; i++){
		int next = g[cur][i];
		if(visited[next])
			continue;
		visited[next] = true;
		if(search(g, next))
			return true;
	}
	return false;
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){			// test case : 1 ~ 10
		init();
		vector<int> g[GRAPH_SIZE];
		int n;
		input(n, g);						// input func
		cout << "#" << tc << " ";
		if(search(g, 0))
			cout << 1 << endl;
		else
			cout << 0 << endl;
	}

	return 0;
}
