
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define Q_SIZE 1000001

using namespace std;

template <class type>

class queue
{
	int head, tail, _size;
	type arr[Q_SIZE];
public:
	int size(void){
		return _size;
	}
	void clear(void){
		head = tail = _size = 0;
	}
	queue(void){
		this->clear();
	}
	~queue(void){
		this->clear();
	}
	void push(type item){
		arr[tail++] = item;
		_size++;
	}
	void pop(void){
		head++, _size--;
	}
	type front(void){
		return arr[head];
	}
	bool empty(void){
		return (_size==0);
	}
	type& operator[](int index){
		return arr[head+index];
	}
};

typedef struct qnode
{
	int num, priority;
	qnode(int n, int p):num(n), priority(p){}
	qnode(void):num(0), priority(0){}	
}qnode;

queue<qnode> q;

void input(int &n, int &target)
{
	cin >> n >> target;
	q.clear();
	for(int i=0; i<n; i++){
		int priority;
		cin >> priority;
		q.push(qnode(i, priority));
	}
}

int solve(int target)
{
	int ret = 0;
	while(!q.empty()){
		int cnum = q.front().num, priority = q.front().priority;	q.pop();
		int len = q.size();
		bool success = true;
		for(int i=0; i<len; i++){
			if(priority < q[i].priority){
				q.push(qnode(cnum, priority));
				success = false;
				break;
			}
		}
		if(success){
			ret++;
			if(target == cnum){
				break;
			}
		}
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--){
		int n, target;
		input(n, target);
		cout << solve(target) << '\n';
	}
	return 0;
}

