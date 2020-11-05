
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define SIZE 100005

using namespace std;

typedef char element;

typedef struct node
{
	element data;
	node *prev, *next;
	node(void):data(0), prev(NULL), next(NULL){}
}node;

typedef struct list_t
{
	node *head, *tail, *cursor;
	node *create_node(element input)
	{
		node *ret = new node;
		ret->data = input;
		return ret;
	}
	list_t(void)
	{
		node *newnode = create_node(-1);
		newnode->prev = newnode->next = newnode;
		head = tail = cursor = newnode;
	}
	void push_prev_to_cursor(element input)
	{
		node *newnode = create_node(input);
		if(cursor == head){
			newnode->prev = tail, newnode->next = head;
			head->prev = newnode, head = newnode;
			tail->next = newnode;
		}
		else{
			node *prev = cursor->prev, *next = cursor;
			newnode->prev = prev, newnode->next = next;
			prev->next = next->prev = newnode;
		}
	}

	void move_cursor(bool dir)
	{
		if(dir){
			node *prev = cursor->prev, *next = cursor->next;
			if(cursor == head)
				head = next;
			prev->next = next, next->prev = prev;
			cursor->next = next->next, cursor->prev = next;
			next->next->prev = cursor, next->next = cursor;
			if(cursor->next == head)
				tail = cursor;
		}
		else{
			node *prev = cursor->prev, *next = cursor->next;
			if(cursor == tail)
				tail = prev;
			prev->next = next, next->prev = prev;
			cursor->next = prev, cursor->prev = prev->prev;
			prev->prev->next = cursor, prev->prev = cursor;
			if(cursor->prev == tail)
				head = cursor;
		}
	}

	void delete_prev_to_cursor(void)
	{
		node *victim = cursor->prev, *prev = cursor->prev->prev, *next = cursor;
		if(victim == head){
			head = cursor;
		}
		prev->next = next, next->prev = prev;
		delete[] victim;
	}

	node *get_cursor_pointer(void)
	{
		return cursor;
	}
	
	bool isHead(node *ptr)
	{
		return (head != NULL && head == ptr);
	}

	bool isTail(node *ptr)
	{
		return (tail != NULL && tail == ptr);
	}
}list_t;

void setUpList(list_t &list, char *str)
{
	for(int i=0; str[i]; i++){
		list.push_prev_to_cursor(str[i]);
	}
}

void moveLeftCursor(list_t &list)
{
	list.move_cursor(false);
}

void moveRightCursor(list_t &list)
{
	list.move_cursor(true);
}

void deleteLeftCursor(list_t &list)
{
	list.delete_prev_to_cursor();
}

void addLeftCursor(list_t &list, char input)
{
	list.push_prev_to_cursor(input);
}

void print(list_t &list)
{
	node *ptr = list.head;
	do{
		if(ptr == list.get_cursor_pointer()){
			ptr = ptr->next;
			continue;
		}
		cout << ptr->data;
		ptr = ptr->next;
	}while(ptr != list.head);
}

void solve(void)
{
	char str[SIZE];
	cin >> str;
	list_t list;
	setUpList(list, str);
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		char ch;
		cin >> ch;
		if(ch == 'L'){
			if(!list.isHead(list.get_cursor_pointer())){
				moveLeftCursor(list);
			}
		}
		else if(ch == 'D'){
			if(!list.isTail(list.get_cursor_pointer())){
				moveRightCursor(list);
			}
		}
		else if(ch == 'B'){
			if(!list.isHead(list.get_cursor_pointer())){
				deleteLeftCursor(list);
			}
		}
		else if(ch == 'P'){
			char input;
			cin >> input;
			addLeftCursor(list, input);
		}
	}
	print(list);
}

int main(void)
{
	ios::sync_with_stdio(false);
	solve();
	return 0;
}

