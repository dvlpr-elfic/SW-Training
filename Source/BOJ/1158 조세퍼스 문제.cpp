
/**
  * @author Jihoon Jang
  */

#include <iostream>

#define SIZE 6000

using namespace std;

int answer[SIZE];

typedef struct node
{
	struct node *front;
	struct node *back;
	int data;
	void init(struct node *f, struct node *b, int d)
	{
		front = f;
		back = b;
		data = d;
	}
}node;

typedef struct dll
{
	node* head;
	int size;
	node* temp;
	dll(void):head(NULL), size(0), temp(NULL){}
	void push_back(int data)
	{
		size++;
		if(head == NULL){
			node *newnode = new node;
			newnode->init(newnode, newnode, data);
			head = newnode;
		}
		else{
			node *ptr = head;
			while(ptr->back != head){
				ptr = ptr->back;
			}
			node *newnode = new node;
			newnode->init(ptr, head, data);
			head->front = newnode;
			ptr->back = newnode;
		}
	}
	int pop(int pos)
	{
		if(empty())
			return NULL;
		size--;
		node *ptr;
		if(temp){
			ptr = temp;
		}
		else{
			ptr = head;

		}
		while(pos--){
			ptr = ptr->back;
		}
		ptr->front->back = ptr->back;
		ptr->back->front = ptr->front;
		int ret = ptr->data;
		temp = ptr->back;
		delete ptr;
		return ret;
	}
	bool empty(void)
	{
		return (!size);
	}
}dll;

void input(int &n, int &m)
{
	cin >> n >> m;
}

void print(int limit)
{
	cout << '<';
	for(int i=0; i<limit; i++){
		cout << answer[i] << ", ";
	}
	cout << answer[limit] << ">\n";
}

void solve(int n, int m)
{
	dll list;
	for(int i=1; i<=n; i++){
		list.push_back(i);
	}
	int idx = 0;
	while(!list.empty()){
		answer[idx++] = list.pop(m-1);
	}
	print(idx-1);
}

int main(void)
{
	ios::sync_with_stdio(false);
	int n, m;
	input(n, m);
	solve(n, m);
	return 0;
}

