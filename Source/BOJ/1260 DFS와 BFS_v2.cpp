
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define Q_SIZE 100001
#define SIZE 1001

using namespace std;

typedef int qnode;

typedef struct queue
{
	int head, tail, size;
	qnode arr[Q_SIZE];
	queue(void):head(0), tail(0), size(0)
	{
		qnode temp = 0;
		for(int i=0; i<Q_SIZE; ++i){
			arr[i] = 0;
		}
	}
	bool full(void)
	{
		return size == Q_SIZE;
	}
	bool empty(void)
	{
		return !size;
	}
	void push(qnode &input)
	{
		if(full()){
			cout << "push error, queue is full\n";
			exit(0);
		}
		arr[tail] = input;
		tail = (tail+1)%Q_SIZE;
		size++;
	}
	void pop(void)
	{
		head = (head+1)%Q_SIZE;
		size--;
	}
	qnode front(void)
	{
		return arr[head];
	}
}queue;

bool g[SIZE][SIZE];
bool visited[SIZE];

void memory_set(void *ptr, char val, int size)
{
	char *p = (char*)ptr;
	for(int i=0; i<size; i++){
		p[i] = val;
	}
}


void input(int &n, int &m, int &v)
{
	cin >> n >> m >> v;
	for(int i=0; i<m; i++){
		int cur, next;
		cin >> cur >> next;
		g[cur][next] = g[next][cur] = true;
	}
}

void bfs(int v, int n, int *vector, int &idx)
{
	queue q;
	q.push(v);
	visited[v] = true;
	while(!q.empty()){
		int cur = q.front();	q.pop();
		vector[idx++] = cur;
		for(int i=0; i<=n; i++){
			if(g[cur][i] && !visited[i]){
				q.push(i);
				visited[i] = true;
			}
		}
	}
	for(int i=0; i<idx; i++){
		cout << vector[i] << ' ';
	}
	cout << endl;
}

void dfs(int cur, int n, int *vector, int &idx)
{
	vector[idx++] = cur;
	visited[cur] = true;
	for(int i=0; i<=n; i++){
		if(g[cur][i] && !visited[i]){
			visited[i] = true;
			dfs(i, n, vector, idx);
		}
	}
}

int main(void)
{
	int n, m, v;
	int vector[SIZE] = {0, };
	int idx = 0;
	input(n, m, v);
	dfs(v, n, vector, idx);
	for(int i=0; i<idx; i++){
		cout << vector[i] << ' ';
	}
	cout << endl;
	idx = 0;
	memory_set(visited, 0, sizeof(visited));
	bfs(v, n, vector, idx);
	return 0;
}

