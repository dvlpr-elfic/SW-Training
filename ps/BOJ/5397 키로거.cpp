
/**
 * @author Jihoon Jang
 */

#include <iostream>

#define SIZE 1000001
#define LEFT 10
#define RIGHT 20

using namespace std;

typedef char element;

typedef struct node
{
	element data;
	struct node *prev, *next;
	node(void):data((element)NULL), prev(NULL), next(NULL){}
}node;

class dll
{
public:
	node *head, *tail, *cursor;
	dll(void)
	{
		cursor = new node;
		head = tail = cursor;
	}
	node* push_left(node* pos, element data)
	{
		if(pos == NULL){
			return NULL;
		}
		node *new_node = new node;
		new_node->data = data;
		new_node->prev = pos->prev;
		new_node->next = pos;
		if(pos->prev != NULL){
			pos->prev->next = new_node;
		}
		else{
			head = new_node;
		}
		pos->prev = new_node;
		return new_node;
	}

	node* push_right(node* pos, element data)
	{
		if(pos == NULL){
			return NULL;
		}
		node* new_node = new node;
		new_node->data = data;
		new_node->prev = pos;
		new_node->next = pos->next;
		if(pos->next != NULL){
			pos->next->prev = new_node;
		}
		else{
			tail = new_node;
		}
		pos->next = new_node;
		return new_node;
	}

	bool pop(node* pos)
	{
		if(pos == NULL){
			return false;
		}
		if(pos->prev != NULL){
			pos->prev->next = pos->next;
		}
		else{
			head = pos->next;
		}
		if(pos->next != NULL){
			pos->next->prev = pos->prev;
		}
		else{
			tail = pos->prev;
		}
		delete[] pos;
		return true;
	}
	void destroy(node* pos)
	{
		if(pos == NULL)
			return;
		destroy(pos->next);
		delete[] pos;
	}

	~dll(void)
	{
		destroy(head);
	}
};

int strlenn(char* str)
{
	int ret = 0;
	for(int i=0; str[i]; i++){
		ret++;
	}
	return ret;
}

void input(char *str)
{
	cin >> str;
}

void cursor_move(int dir, dll &list)
{
	node *pos;
	node* new_cursor;
	switch(dir){
	case LEFT:
		pos = list.cursor->prev;
		new_cursor = list.push_left(pos, NULL);
		break;
	case RIGHT:
		pos = list.cursor->next;
		new_cursor = list.push_right(pos, NULL);
		break;
	}
	if(new_cursor != NULL){
		list.pop(list.cursor);
		list.cursor = new_cursor;
	}
}

void back_space(dll &list)
{
	node* pos = list.cursor->prev;
	list.pop(pos);
}

void push_char(element input, dll &list)
{
	node* pos = list.cursor;
	list.push_left(pos, input);
}

void print(dll &list)
{
	for(node* ptr = list.head; ptr!=NULL; ptr = ptr->next){
		if(ptr->data)
			cout << ptr->data;
	}
	cout << '\n';
}

void solve(char *str)
{
	int len = strlenn(str);
	dll list;
	for(int i=0; i<len; i++){
		char command = str[i];
		if(command == '<')
			cursor_move(LEFT, list);
		else if(command == '>')
			cursor_move(RIGHT, list);
		else if(command == '-')
			back_space(list);
		else
			push_char(command, list);
	}
	print(list);
}

int main(void)
{
	ios::sync_with_stdio(false);
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while(t--){
		char str[SIZE];
		input(str);
		solve(str);
	}
	return 0;
}

