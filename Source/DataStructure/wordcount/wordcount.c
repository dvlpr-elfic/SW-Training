// WordCount Application
#include <stdio.h>
#include <stdlib.h>
// 오버플로우를 방지하기 위해 사이즈를 크게 잡는다
#define MAX_CHAR_PER_WORD 100
#define MAX_WORD_PER_TABLE 100000
#define MAX_STACK_SIZE 100000
#define MAX_HEAP_SIZE 100000
// 단어와 해당 단어의 빈도수를 저장할 구조체 정의
typedef struct WordCount
{
	char word[MAX_CHAR_PER_WORD];
	int weight;
}WordCount;
// 단어와 빈도수의 집합과 자료의 개수를 저장할 구조체 정의
typedef struct DataTable
{
	WordCount wordcount[MAX_WORD_PER_TABLE];
	int count;
}DataTable;
// 스택 자료형 정의
typedef struct StackType
{
	WordCount stack[MAX_STACK_SIZE];
	int top;
}StackType;
// 힙 자료형 정의
typedef struct HeapType
{
	WordCount heap[MAX_HEAP_SIZE];
	int size;
}HeapType;

// 스택 관련 함수 프로토타입
void InitStack(StackType*);
void Push(StackType*, WordCount);
WordCount Pop(StackType*);
int isEmpty(StackType*);
int isFull(StackType*);
WordCount Peek(StackType*);
// 힙 관련 함수 프로토타입
void InitHeap(HeapType*);
int isHeapEmpty(HeapType*);
WordCount deleteMinHeapByWord(HeapType*);
void insertMinHeapByWord(HeapType*, WordCount);
void HeapSortByWeightAndWord(DataTable*, HeapType*);
void HeapSortByWeight(DataTable*, HeapType*);
void insertMinHeapByWeight(HeapType*, WordCount);
WordCount deleteMinHeapByWeight(HeapType*);
void HeapSortByWord(DataTable*, HeapType*);
// 테이블 초기화 관련 함수 프로토타입
void InitDataTable(DataTable*);
void SetWeight(DataTable*, StackType*);
void GetString2Table(DataTable*);
void GetString2Table_SetWeight(DataTable*);
// 테이블에 매개변수로 넘어가는 문자열(단어)이 있는지 확인하는 함수
int isExistInTable(DataTable*, char*);
// 문자열이 같은지 확인하는 함수
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
	// 큰 메모리를 잡기 위해서 지역변수 대신 메모리할당
	DataTable* ptable = (DataTable*)malloc(sizeof(DataTable));
	StackType* pstack = (StackType*)malloc(sizeof(StackType));
	HeapType* heap = (HeapType*)malloc(sizeof(HeapType));
	char *cp;
	// 테이블 초기화
	InitDataTable(ptable);
	// 터미널창에서 명령어를 받기위해 작업 실행
	cp = argv[1];
	
	switch (*(++cp)){
		// Mode 1
		case '1':
			if ( argc != 2 ) {
				printf("인수 갯수가 2이 아닙니다.\n");
				printf("사용법: word_extract -d read_file_name | wordcount -2\n");
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
				printf("인수 갯수가 2이 아닙니다.\n");
				printf("사용법: word_extract -d read_file_name | wordcount -2\n");
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
				printf("인수 갯수가 3이 아닙니다.\n");
				printf("사용법: word_extract -d read_file_name | wordcount -3 word_to_search\n");
				exit(1);
			}
			GetString2Table(ptable);
			ShellSort(ptable, ptable->count);
			SetWeight(ptable, pstack);
			SearchWord(ptable, argv[2]);
			break;
		default:
			printf("적합한 옵션이 설정되지 않았읍니다.\n");
			break;
	}
	free(ptable);
	free(pstack);
	free(heap);
	return 0;
}
// 힙이 비었는지 확인
int isHeapEmpty(HeapType* h)
{
	return (h->size == 0);
}
// 힙 초기화
void InitHeap(HeapType* h)
{
	h->size = 0;
}
// 쉘 정렬 알고리즘
void ShellSort(DataTable* ptable, int n)
{
	int i, gap;
	for( gap=n/2; gap>0; gap = gap/2 ) {
		if( (gap%2) == 0 ) gap++;
		for(i=0;i<gap;i++) 
			inc_insertion_sort(ptable, i, n-1, gap);
	}
}
// 쉘 정렬시 gap에 따라 삽입정렬
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
// 선택정렬을 이용해서 단어 오름차순 정렬
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
// 선택정렬을 이용해서 단어 빈도수 기준 오름차순 정렬
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
// 선택정렬을 이용해 단어 빈도수 오름차순으로 정렬 후 빈도수가 같은 것 끼리 단어 오름차순(아스키코드값) 정렬
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
// 힙 정렬을 이용해 단어 빈도수 오름차순으로 정렬 후 빈도수가 같은 것 끼리 단어 오름차순(아스키코드값) 정렬
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
// 단어 오름차순으로 최소 힙 삽입 연산
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
// 단어 오름차순으로 최소힙 삭제 연산
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
// 힙 정렬을 이용해 빈도수 기준 오름차순 정렬
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
// 힙 정렬을 이용해 단어(아스키코드값) 기준 오름차순 정렬
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

// 빈도수 오름차순 기준 최소힙 삽입 연산
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
// 빈도수 오름차순 기준 최소힙 삭제 연산
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
// 단어 순차탐색 알고리즘
void SearchWord(DataTable* ptable, char* str)
{
	int i;
	for(i=0; i<(ptable->count); i++){
		if(strcmp(str, ptable->wordcount[i].word) == 0){
			printf("%s %d\n", ptable->wordcount[i].word, ptable->wordcount[i].weight);
			return;
		}
	}
	// 못찾을 시 실패 메세지
	printf("Cannot find the word in sample.txt\n");
}
// 스택을 이용해서 빈도수 처리
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
// word_extract 프로그램이 출력한 단어들을 테이블에 저장
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
// 테이블의 내용을 화면에 출력
void DisplayTable(DataTable* ptable)
{
	int i;
	for(i=0; i<ptable->count; i++){
		printf("%4d: %2d %s\n", i, ptable->wordcount[i].weight, ptable->wordcount[i].word);
	}
}
// 같은 단어가 있는지 확인하는 함수
int isSameString(char* str1, char* str2)
{
	return (strcmp(str1, str2)==0);

}
// 스택 초기화
void InitStack(StackType* s)
{
	s->top = -1;
}
// 스택 푸시 연산
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
// 스택에서 피크 연산
WordCount Peek(StackType* s)
{
	if(isEmpty(s)){
		fprintf(stderr, "Cannot Peek, Stack is Empty\n");
		return;
	}
	else
		return s->stack[s->top];
}
// 스택 팝 연산
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
// 스택이 비어있는지 확인하는 함수
int isEmpty(StackType* s)
{
	return (s->top == -1);
}
// 스택이 가득 찼는지 확인하는 함수
int isFull(StackType* s)
{
	return ((s->top)==MAX_STACK_SIZE-1);
}
// 테이블 초기화
void InitDataTable(DataTable* ptable)
{
	int i;
	for(i=0; i<MAX_WORD_PER_TABLE; i++){
		ptable->wordcount[i].weight = 1;
	}
}

// word_extract 프로그램이 출력한 단어들을 테이블에 저장, 저장할 때마다 중복되는 단어가 있을시 빈도수 처리
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
// 테이블에 이미 단어가 있는지 확인하는 함수
int isExistInTable(DataTable* ptable, char* str)
{
	int i;
	for(i=0; i<(ptable->count); i++){
		if(isSameString(str, ptable->wordcount[i].word))
			return i;
	}
	return -1;
}
