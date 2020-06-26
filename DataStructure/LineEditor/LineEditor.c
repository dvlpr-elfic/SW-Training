//
//	���� ������ ���α׷�
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR_PER_LINE	1000
// Change Start
//#define MAX_CHAR_PER_LINE 1000
// Change End
#define MAX_NAME	256
void warning(char *);   
void error(char *); 

#define FALSE 0
#define TRUE 1

typedef struct {
	char a[MAX_CHAR_PER_LINE];
} element;
typedef struct ListNode { 
	element data;
	struct ListNode *link;   	
} ListNode;
typedef struct {
	ListNode *head;     // ��� ������
	int length;		// ����� ����
} ListType;
// phead: ����Ʈ�� ��� �������� ������
// p : ���� ���
// new_node : ���Ե� ��� 
void insert_node(ListNode **phead, ListNode *p, 
					ListNode *new_node) 
{
	if( *phead == NULL ){	// ���鸮��Ʈ�� ���
		new_node->link = NULL; 
		*phead = new_node; 
	}
	else if( p == NULL ){ // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {			 // p ������ ����
		new_node->link = p->link; 
		p->link = new_node; 
	}
}
// phead : ��� �����Ϳ� ���� ������ 
// p: ������ ����� ���� ���
// removed: ������ ��� 
void remove_node(ListNode **phead, ListNode *p, ListNode *removed) 
{
	if( p == NULL )
		*phead = (*phead)->link;
	else
		p->link = removed->link;
	free(removed);
}
// ����Ʈ�� �ʱ�ȭ�Ѵ�.
void init(ListType *list)
{
	if( list == NULL ) return;
	list->length = 0;
	list->head = NULL;
}
// ����Ʈ�ȿ��� pos ��ġ�� ��带 ��ȯ�Ѵ�.
ListNode *get_node_at(ListType *list, int pos)
{
	int i;
	ListNode *tmp_node = list->head;
	if( pos < 0 ) return NULL;
	else if(tmp_node == NULL) return NULL;
	for (i=0; i<pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
} 
// ����Ʈ�� �׸��� ������ ��ȯ�Ѵ�.
int get_length(ListType *list)
{
	return list->length;
}

// �־��� ��ġ�� �����͸� �����Ѵ�.
void add(ListType *list, int position, element data) 
{
	ListNode *p;
	if ((position >= 0) && (position <= list->length)){
		ListNode*node=	(ListNode *)malloc(sizeof(ListNode)); 
		if( node == NULL ) error("�޸� �Ҵ翡��");
		node->data = data;
		p = get_node_at(list, position-1);
		insert_node(&(list->head), p, node); 
		list->length++;
	}
} 
// ����Ʈ�� ���� �����͸� �����Ѵ�.
void add_last(ListType *list, element data)
{
	add(list, get_length(list), data);
}  
// ����Ʈ�� ���� �����͸� �����Ѵ�.
void add_first(ListType *list, element data)
{
	add(list, 0, data);
}  
//
int is_empty(ListType *list)
{
	if( list->head == NULL ) return 1;
	else return 0;
}

// �־��� ��ġ�� �����͸� �����Ѵ�.
void Delete(ListType *list, int pos)
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)){
	 ListNode *p = get_node_at(list, pos-1);
	 remove_node(&(list->head),p,(p!=NULL)?p->link:NULL);
	 list->length--;
	}
}  
//
element get_entry(ListType *list, int pos)
{
	ListNode *p;
	if( pos >= list->length ) error("��ġ ����");
	p = get_node_at(list, pos);
	return p->data;
}
// This Routine Error
void clear(ListType *list)
{
	//int i;
	//for(i=0;i<list->length;i++)
	//	Delete(list, i);
	while(list->head != (ListNode*)NULL){
		Delete(list, get_length(list)-1);
	}
}
// ������ ������ ����Ѵ�. 
void display(ListType *buffer)
{
	int i;
	ListNode *tmp_node;
	tmp_node = buffer->head;

	printf("**************\n");
	for(i=0;i<buffer->length;i++){
		//printf("%d %s", i, tmp_node->data.a);
		printf("%s",tmp_node->data.a);
		tmp_node = tmp_node->link;
	}
	printf("**************\n");
}
// 
void warning(char *message)
{
	fprintf(stderr,"%s\n",message);
}
//
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
//
void help()
{
   printf("**************\n");
   printf("i: �Է�\n");
   printf("d: ����\n");
   printf("r: �����б�\n");
   printf("w: ���Ͼ���\n");
   printf("q: ����\n");
   printf("**************\n");
}

// ��ũ ���Ϸκ��� �����͸� �д´�.
void read_file(ListType *buffer)
{
	char fname[MAX_NAME];

	FILE *fd;
	element p;

	printf("���� �̸�: ");
	scanf("%s", fname);
	if( (fd = fopen(fname,"r")) == NULL ){
		warning("������ ���������ϴ�.");
		return;
	}
	if( !is_empty(buffer) ){
		clear(buffer);
	}
	init(buffer);
	while(fgets(p.a, MAX_CHAR_PER_LINE, fd)){
	    add_last(buffer, p);
	}
	fclose(fd);
	display(buffer);
}
// ���ۿ� �ִ� �����͸� ��ũ ���Ͽ� ����.
void write_file(ListType *buffer)
{
	FILE *fd;
	char fname[MAX_NAME];
	element p;
	int i;

	printf("���� �̸�: ");
	scanf("%s", fname);
	if( (fd = fopen(fname,"w")) == NULL ){
		printf("������ ���������ϴ�.\n");
		return;
	}
	for(i=0;i<get_length(buffer);i++){
		p = get_entry(buffer, i);
		fputs(p.a, fd);
	}
	fclose(fd);
	display(buffer);
}
// �ϳ��� ������ �����
void Delete_line(ListType *buffer)
{
    int position;
    // Add Variable 
    char temp_string[MAX_CHAR_PER_LINE]; 
    if(is_empty(buffer))
        printf("���� ������ �����ϴ�.\n");
    else
    {
        printf("����� ���� ���ι�ȣ�� �Է��ϼ���:\n");
	scanf("%s", temp_string);
	if(temp_string[0] < '0' || temp_string[0] > '9'){
		printf("Please Enter Only Positive Integers Or Zero\n");
		display(buffer);
		return;	
	}
	// Change From scanf to atoi
	position = atoi(temp_string);
        Delete(buffer, position);
	}
	display(buffer);
}
// �ϳ��� ������ �����Ѵ�.
void insert_line(ListType *buffer)
{
	int position;
	char line[MAX_CHAR_PER_LINE];
	element p;
	// Should Clear Input Buffer
	// Because get string
	//fflush(stdin);    
	printf("�Է����ȣ�� �Է��ϼ���: \n");
	// Change Start
	scanf("%s", line); 
	if(line[0] > '9' || line[0] < '0'){  
		printf("Please Enter Only Positive Integers Or Zero\n");
		display(buffer);
	    	return;
	}
	position = atoi(line); 
	// Change End 
	printf("������ �Է��ϼ���: ");
    	fflush(stdin);
	fgets(line, MAX_CHAR_PER_LINE, stdin);
	strcpy(p.a, line);
	if(position > buffer->length){
		int i;
		element Empty_Element;
		Empty_Element.a[0] = '\n';
		Empty_Element.a[1] = (char)NULL;
		for(i=buffer->length; i<position; i++){
			add_last(buffer, Empty_Element);
		}
	}
	add(buffer, position, p);
	display(buffer);
}
//
void do_command(ListType *buffer, char command)
{
    switch(command)
    {
        case 'd':                   
            Delete_line(buffer);
            break;
        case 'i':                   
            insert_line(buffer);     
            break;
        case 'r':                   
            read_file(buffer);     
	    break;
        case 'w':                   
            write_file(buffer);     
            break;
        case 'q': 
            break;
    }
}
// ���� ������ ���� ���α׷�
int main()
{
	char command;
	ListType buffer;

	init(&buffer);
	do{
		help();
	       	command = getchar();
		// Should Clear I/O stream Buffer
		fflush(stdin);
	        do_command(&buffer, command);
		fflush(stdin);
	} while(command != 'q');
	// Should Clear Memory
	clear(&buffer);
	return 0;
}
