// WordCount Application
#include <stdio.h>
#include <stdlib.h>
// �����÷ο츦 �����ϱ� ���� ����� ũ�� ��´�
#define MAX_CHAR_PER_WORD 100
#define MAX_WORD_PER_TABLE 100000
#define MAX_STACK_SIZE 100000
#define MAX_HEAP_SIZE 100000
// �ܾ�� �ش� �ܾ��� �󵵼��� ������ ����ü ����
typedef struct WordCount
{
	char word[MAX_CHAR_PER_WORD];
	int weight;
}WordCount;
// �ܾ�� �󵵼��� ���հ� �ڷ��� ������ ������ ����ü ����
typedef struct DataTable
{
	WordCount wordcount[MAX_WORD_PER_TABLE];
	int count;
}DataTable;
// ���� �ڷ��� ����
typedef struct StackType
{
	WordCount stack[MAX_STACK_SIZE];
	int top;
}StackType;
// �� �ڷ��� ����
typedef struct HeapType
{
	WordCount heap[MAX_HEAP_SIZE];
	int size;
}HeapType;

// ���� ���� �Լ� ������Ÿ��
void InitStack(StackType*);
void Push(StackType*, WordCount);
WordCount Pop(StackType*);
int isEmpty(StackType*);
int isFull(StackType*);
WordCount Peek(StackType*);
// �� ���� �Լ� ������Ÿ��
void InitHeap(HeapType*);
int isHeapEmpty(HeapType*);
WordCount deleteMinHeapByWord(HeapType*);
void insertMinHeapByWord(HeapType*, WordCount);
void HeapSortByWeightAndWord(DataTable*, HeapType*);
void HeapSortByWeight(DataTable*, HeapType*);
void insertMinHeapByWeight(HeapType*, WordCount);
WordCount deleteMinHeapByWeight(HeapType*);
void HeapSortByWord(DataTable*, HeapType*);
// ���̺� �ʱ�ȭ ���� �Լ� ������Ÿ��
void InitDataTable(DataTable*);
void SetWeight(DataTable*, StackType*);
void GetString2Table(DataTable*);
void GetString2Table_SetWeight(DataTable*);
// ���̺� �Ű������� �Ѿ�� ���ڿ�(�ܾ�)�� �ִ��� Ȯ���ϴ� �Լ�
int isExistInTable(DataTable*, char*);
// ���ڿ��� ������ Ȯ���ϴ� �Լ�
int isSameString(char*, char*);
// Selection Sorting
void SelectionSortByWord(DataTable*, int, int);
void SelectionSortByWeight(DataTable*, int, int);
void SelectionSortByWeightAndWord(DataTable*, int);
// Shell Sorting
void ShellSort(DataTable*, int);
void inc_insertion_sort(DataTable*, int, int, int);
// Searching
void SearchWord(DataTable*, char*);
// Display
void DisplayTable(DataTable*);
// main function
int main(int argc, char * argv[])
{
	// ū �޸𸮸� ��� ���ؼ� �������� ��� �޸��Ҵ�
	DataTable* ptable = (DataTable*)malloc(sizeof(DataTable));
	StackType* pstack = (StackType*)malloc(sizeof(StackType));
	HeapType* heap = (HeapType*)malloc(sizeof(HeapType));
	char *cp;
	// ���̺� �ʱ�ȭ
	InitDataTable(ptable);
	// �͹̳�â���� ��ɾ �ޱ����� �۾� ����
	cp = argv[1];
	
	switch (*(++cp)){
		// Mode 1
		case '1':
			if ( argc != 2 ) {
				printf("�μ� ������ 2�� �ƴմϴ�.\n");
				printf("����: word_extract -d read_file_name | wordcount -2\n");
				exit(1);
			}
			// 
			GetString2Table(ptable);
			// Sorting
			SelectionSortByWord(ptable, 0, ptable->count);
			// Weight setting
			SetWeight(ptable, pstack);
			// Display
			DisplayTable(ptable);
			break;
		// Mode 2	
		case '2':
			if ( argc != 2 ) {
				printf("�μ� ������ 2�� �ƴմϴ�.\n");
				printf("����: word_extract -d read_file_name | wordcount -2\n");
				exit(1);
			}
			InitHeap(heap);
			GetString2Table(ptable);
			HeapSortByWord(ptable, heap);
			SetWeight(ptable, pstack);
			HeapSortByWeightAndWord(ptable, heap);
			DisplayTable(ptable);
			break;
			// Mode 3
		case '3':
			if ( argc != 3 ) {
				printf("�μ� ������ 3�� �ƴմϴ�.\n");
				printf("����: word_extract -d read_file_name | wordcount -3 word_to_search\n");
				exit(1);
			}
			GetString2Table(ptable);
			ShellSort(ptable, ptable->count);
			SetWeight(ptable, pstack);
			SearchWord(ptable, argv[2]);
			break;
		default:
			printf("������ �ɼ��� �������� �ʾ����ϴ�.\n");
			break;
	}
	free(ptable);
	free(pstack);
	free(heap);
	return 0;
}
// ���� ������� Ȯ��
int isHeapEmpty(HeapType* h)
{
	return (h->size == 0);
}
// �� �ʱ�ȭ
void InitHeap(HeapType* h)
{
	h->size = 0;
}
// �� ���� �˰���
void ShellSort(DataTable* ptable, int n)
{
	int i, gap;
	for( gap=n/2; gap>0; gap = gap/2 ) {
		if( (gap%2) == 0 ) gap++;
		for(i=0;i<gap;i++) 
			inc_insertion_sort(ptable, i, n-1, gap);
	}
}
// �� ���Ľ� gap�� ���� ��������
void inc_insertion_sort(DataTable *ptable, int first, int last, int gap)
{
	int i, j; 
	WordCount key;
	for(i=first+gap; i<=last; i=i+gap){ 	
		key = ptable->wordcount[i];
		for(j=i-gap; j>=first && strcmp(key.word, ptable->wordcount[j].word)<0; j=j-gap)
			ptable->wordcount[j+gap]=ptable->wordcount[j];
		ptable->wordcount[j+gap]=key;
	}
}
// ���������� �̿��ؼ� �ܾ� �������� ����
void SelectionSortByWord(DataTable* ptable, int start, int end)
{
	int i, j, least;
	WordCount temp;
	for(i=start; i<end-1; i++){
		least = i;
		for(j=i+1; j<end; j++){
			// Find Least Value
			if(strcmp(ptable->wordcount[j].word, ptable->wordcount[least].word)<0){
				least = j;
			}
		}
		// Swap
		temp = ptable->wordcount[i];
		ptable->wordcount[i] = ptable->wordcount[least];
		ptable->wordcount[least] = temp;

	}
}
// ���������� �̿��ؼ� �ܾ� �󵵼� ���� �������� ����
void SelectionSortByWeight(DataTable* ptable, int start, int end)
{
	int i, j, least;
	WordCount temp;
	for(i=start; i<end-1; i++){
		least = i;
		for(j=i+1; j<end; j++){
			if(ptable->wordcount[j].weight < ptable->wordcount[least].weight){
				least = j;
			}
		}
		temp = ptable->wordcount[i];
		ptable->wordcount[i] = ptable->wordcount[least];
		ptable->wordcount[least] = temp;
	}
}
// ���������� �̿��� �ܾ� �󵵼� ������������ ���� �� �󵵼��� ���� �� ���� �ܾ� ��������(�ƽ�Ű�ڵ尪) ����
void SelectionSortByWeightAndWord(DataTable* ptable, int size)
{
	int i, start = 0, pre_weight;
	SelectionSortByWeight(ptable, 0, size);
	pre_weight = ptable->wordcount[0].weight;
	for(i=0; i<=size; i++){
		if(ptable->wordcount[i].weight != pre_weight){
			pre_weight = ptable->wordcount[i].weight;
			SelectionSortByWord(ptable, start, i);
			start = i;
		}
	}
}
// �� ������ �̿��� �ܾ� �󵵼� ������������ ���� �� �󵵼��� ���� �� ���� �ܾ� ��������(�ƽ�Ű�ڵ尪) ����
void HeapSortByWeightAndWord(DataTable* ptable, HeapType* h)
{
	int i, preweight, index = 0;
	HeapSortByWeight(ptable, h);
	preweight = ptable->wordcount[0].weight;
	for(i=0; i<=ptable->count; i++){
		if(ptable->wordcount[i].weight != preweight){
			while(!isHeapEmpty(h)){
				ptable->wordcount[index++] = deleteMinHeapByWord(h);
			}
			preweight = ptable->wordcount[i].weight;
			insertMinHeapByWord(h, ptable->wordcount[i]);
		}
		else{
			insertMinHeapByWord(h, ptable->wordcount[i]);
		}
	}
}
// �ܾ� ������������ �ּ� �� ���� ����
void insertMinHeapByWord(HeapType* h, WordCount item)
{
	int i;
	i = ++(h->size);
	while((i != 1) && (strcmp(item.word, h->heap[i/2].word) <0)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}
// �ܾ� ������������ �ּ��� ���� ����
WordCount deleteMinHeapByWord(HeapType* h)
{
	int parent, child;
	WordCount item, temp;

	item = h->heap[1];
	temp = h->heap[(h->size)--];
	parent = 1;
	child = 2;

	while(child <= h->size){
		if((child < h->size) && (strcmp(h->heap[child].word, h->heap[child+1].word) > 0))
			child++;
		if(strcmp(temp.word, h->heap[child].word) <= 0)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	return item;
}
// �� ������ �̿��� �󵵼� ���� �������� ����
void HeapSortByWeight(DataTable* ptable, HeapType* h)
{
	int i;
	for(i=0; i<ptable->count; i++){
		insertMinHeapByWeight(h, ptable->wordcount[i]);
	}
	for(i=0; i<ptable->count; i++){
		ptable->wordcount[i] = deleteMinHeapByWeight(h);
	}
}
// �� ������ �̿��� �ܾ�(�ƽ�Ű�ڵ尪) ���� �������� ����
void HeapSortByWord(DataTable* ptable, HeapType* h)
{
	int i;
	for(i=0; i<ptable->count; i++){
		insertMinHeapByWord(h, ptable->wordcount[i]);
	}
	for(i=0; i<ptable->count; i++){
		ptable->wordcount[i] = deleteMinHeapByWord(h);
	}
}

// �󵵼� �������� ���� �ּ��� ���� ����
void insertMinHeapByWeight(HeapType* h, WordCount item)
{
	int i;
	i = ++(h->size);
	while((i != 1) && (item.weight < h->heap[i/2].weight)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}
// �󵵼� �������� ���� �ּ��� ���� ����
WordCount deleteMinHeapByWeight(HeapType* h)
{
	int parent, child;
	WordCount item, temp;
	item = h->heap[1];
	temp = h->heap[(h->size)--];
	parent = 1;
	child = 2;
	while(child <= h->size){
		if((child < h->size) && (h->heap[child].weight) > h->heap[child+1].weight)
			child++;
		if( temp.weight <= h->heap[child].weight ) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// �ܾ� ����Ž�� �˰���
void SearchWord(DataTable* ptable, char* str)
{
	int i;
	for(i=0; i<(ptable->count); i++){
		if(strcmp(str, ptable->wordcount[i].word) == 0){
			printf("%s %d\n", ptable->wordcount[i].word, ptable->wordcount[i].weight);
			return;
		}
	}
	// ��ã�� �� ���� �޼���
	printf("Cannot find the word in sample.txt\n");
}
// ������ �̿��ؼ� �󵵼� ó��
void SetWeight(DataTable* ptable, StackType* s)
{
	int i;
	WordCount temp;
	InitStack(s);
	Push(s, (ptable->wordcount[0]));
	for(i=1; i<ptable->count; i++){
		temp = Peek(s);
		if(isSameString(temp.word, ptable->wordcount[i].word))
			(s->stack[s->top]).weight++;
		else
			Push(s, (ptable->wordcount[i]));
	}
	memset(ptable, 0, sizeof(DataTable));
	ptable->count = s->top+1;
	for(i=s->top; i>=0; i--){
		temp = Pop(s);
		ptable->wordcount[i] = temp;
	}
	
}
// word_extract ���α׷��� ����� �ܾ���� ���̺� ����
void GetString2Table(DataTable* ptable)
{
	int i = 0;
	while(1){
		scanf("%s", ptable->wordcount[i].word);
		if(!(ptable->wordcount[i].word[0])){
			ptable->count = i;
			break;
		}
		i++;
	}
}
// ���̺��� ������ ȭ�鿡 ���
void DisplayTable(DataTable* ptable)
{
	int i;
	for(i=0; i<ptable->count; i++){
		printf("%4d: %2d %s\n", i, ptable->wordcount[i].weight, ptable->wordcount[i].word);
	}
}
// ���� �ܾ �ִ��� Ȯ���ϴ� �Լ�
int isSameString(char* str1, char* str2)
{
	return (strcmp(str1, str2)==0);

}
// ���� �ʱ�ȭ
void InitStack(StackType* s)
{
	s->top = -1;
}
// ���� Ǫ�� ����
void Push(StackType* s, WordCount item)
{
	if(isFull(s)){
		fprintf(stderr, "Stack OverFlow\n");
		exit(1);
	}
	else{
		s->stack[++(s->top)] = item;
	}
}
// ���ÿ��� ��ũ ����
WordCount Peek(StackType* s)
{
	if(isEmpty(s)){
		fprintf(stderr, "Cannot Peek, Stack is Empty\n");
		return;
	}
	else
		return s->stack[s->top];
}
// ���� �� ����
WordCount Pop(StackType* s)
{
	if(isEmpty(s)){
		fprintf(stderr, "Cannot Pop, Stack is Empty\n");
		exit(1);
	}
	else{
		return s->stack[(s->top)--];
	}
}
// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(StackType* s)
{
	return (s->top == -1);
}
// ������ ���� á���� Ȯ���ϴ� �Լ�
int isFull(StackType* s)
{
	return ((s->top)==MAX_STACK_SIZE-1);
}
// ���̺� �ʱ�ȭ
void InitDataTable(DataTable* ptable)
{
	int i;
	for(i=0; i<MAX_WORD_PER_TABLE; i++){
		ptable->wordcount[i].weight = 1;
	}
}

// word_extract ���α׷��� ����� �ܾ���� ���̺� ����, ������ ������ �ߺ��Ǵ� �ܾ ������ �󵵼� ó��
void GetString2Table_SetWeight(DataTable* ptable)
{
	int i = 0;
	while(1){
		int pos;
		char str[MAX_CHAR_PER_WORD] = {0, };
		scanf("%s", str);
		pos = isExistInTable(ptable, str);
		if(pos == -1){
			strcpy(ptable->wordcount[i].word, str);
			if(!str[0]){
				break;
			}
			ptable->count++;
			i++;
		}
		else{
			ptable->wordcount[pos].weight++;
		}
	}
}
// ���̺� �̹� �ܾ �ִ��� Ȯ���ϴ� �Լ�
int isExistInTable(DataTable* ptable, char* str)
{
	int i;
	for(i=0; i<(ptable->count); i++){
		if(isSameString(str, ptable->wordcount[i].word))
			return i;
	}
	return -1;
}
