
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <deque>
#include <queue>

using namespace std;

typedef struct anode
{
	char ch, dir;
	anode(int c, int d):ch(c), dir(d){}
}anode;

deque<anode> ant;

void input(int &n, int &t)
{
	int n1, n2;
	cin >> n1 >> n2;
	n = n1 + n2;
	while(n1--){
		char ch;
		cin >> ch;
		ant.push_front(anode(ch, 0));
	}
	while(n2--){
		char ch;
		cin >> ch;
		ant.push_back(anode(ch, 1));
	}
	cin >> t;
}

void jump(int p1, int p2)
{
	anode temp = ant[p1];
	ant[p1] = ant[p2];
	ant[p2] = temp;
}

void simul(int n)
{
	queue<int> q;
	for(int i=1; i<n; i++){
		if(ant[i].dir && !ant[i-1].dir){
			q.push(i);
		}
	}
	while(!q.empty()){
		int idx = q.front();	q.pop();
		jump(idx, idx-1);
	}

}

void solve(int t, int n)
{
	while(t--){
		simul(n);
	}
}

void print(int n)
{
	for(int i=0; i<n; i++){
		cout << ant[i].ch;
	}
	cout << endl;
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int n, t;
	input(n, t);
	solve(t, n);
	print(n);
	return 0;
}
