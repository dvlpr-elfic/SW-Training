

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_GRAPH_SIZE 120

using namespace std;

typedef struct element
{
	int num;
	int step;
}element;


void input(vector<vector<int>> &g, int n)
{
	for(int i=0; i<n; i++){
		int parent, child;
		scanf("%d %d", &parent, &child);
		g[parent].push_back(child);
	}
}

void bfs(queue<element> &q, vector<vector<int>> &g, bool *visited, vector<element> &route)
{
	while(!q.empty()){
		element cur = q.front();
		q.pop();
		visited[cur.num] = true;
		route.push_back(cur);
		while(!g[cur.num].empty()){
			element next = {g[cur.num].back(), cur.step+1};
			if(!visited[next.num])
				q.push(next);
			g[cur.num].pop_back();
		}
	}
}

bool compare(const element &a, const element &b)
{
	if(a.step == b.step)
		return a.num > b.num;
	return a.step > b.step;
}


int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		queue<element> q;
		vector<vector<int>> g(MAX_GRAPH_SIZE);
		bool visited[MAX_GRAPH_SIZE] = {0, };
		vector<element> route;
		int data_len;
		element start = {0, };
		scanf("%d %d", &data_len, &(start.num));
		input(g, data_len/2);
		q.push(start);							// 큐 초기화
		bfs(q, g, visited, route);
		sort(route.begin(), route.begin() + route.size(), compare);
		int ans = route[0].num;
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}