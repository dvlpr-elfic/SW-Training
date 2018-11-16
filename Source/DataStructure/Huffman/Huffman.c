// 허프만 코드 생성 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Defines

#define MAX_ELEMENT 100
#define MAX_CHAR 128
#define MAX_ALPHABET 52
#define MAX_DEPTH 10
// 답을 저장할 구조체타입 정의

typedef struct HUFFMAN
{
	char key;
	int weight;
	int depth;
	char code[MAX_DEPTH];
}HUFFMAN;
// 트리 노드의 데이터필드 구조체타입 정의

typedef struct ELEMENT
{
	char key;
	int weight;
}ELEMENT;
// 트리를 표현하기 위한 이중연결리스트 구조체타입 정의

typedef struct Node
{
	struct Node *right, *left;
	ELEMENT data;
}Node;
// 최소 힙 구조체타입 정의

typedef struct HeapType
{
	Node* heap[MAX_ELEMENT];
	int heap_size;
}HeapType;
// 최대 힙 구조체타입 정의

typedef struct MAXHEAPTYPE
{
	HUFFMAN heap[MAX_ALPHABET];
	int size;
}MAXHEAPTYPE;

// 함수 프로토타입
FILE* OpenFile(void);
void GetText(int*, FILE*);
void InitObject(int*, ELEMENT*);
void InitHeap(HeapType*);
void MakeMinHeap(HeapType*, ELEMENT*);
Node* CreateNode(Node*, Node*);
void InsertMinHeap(HeapType*, Node*);
Node* MakeTree(HeapType*);
Node* DeleteMinHeap(HeapType*);
void print_tree(Node*);
void CreateHuffmanCode(Node*, HUFFMAN*, int, char*);
void PrintHuffmanCode(HUFFMAN*, int);
void MakeMaxHeap(MAXHEAPTYPE*, HUFFMAN*, int, int*);
void InsertMaxHeap(MAXHEAPTYPE*, HUFFMAN);
HUFFMAN DeleteMaxHeap(MAXHEAPTYPE*);
void SortingHuffmanCode(MAXHEAPTYPE*, HUFFMAN*);
void InitMaxHeap(MAXHEAPTYPE*);
void Destroy_Tree(Node*);
// Depth Sort
void SortingDepth(MAXHEAPTYPE*, HUFFMAN*);
void InsertMinHeap_Depth(MAXHEAPTYPE*, HUFFMAN);
HUFFMAN DeleteMinHeap_Depth(MAXHEAPTYPE*);

// 메인함수
int main(void)
{
	// 힙 사이즈를 저장할 변수
	int CountOfObject = 0;
	// 답을 저장할 배열
	HUFFMAN huffman[MAX_ALPHABET] = { 0, };
	// 허프만 코드 임시 저장공간
	char Code[MAX_DEPTH] = { 0, };
	// 트리의 루트
	Node* root;
	// 최소 힙
	HeapType heap = { 0, };
	// 아스키코드를 인덱스로 주어 각 글자의 수를 셀 배열
	int ASCII_TABLE[MAX_CHAR] = { 0, };
	// 파일 열기
	FILE* pFile = OpenFile();
	// 52개의 알파벳과 그 빈도수를 순서대로 저장할 배열
	ELEMENT object[MAX_ALPHABET] = { 0, };
	// HUFFMAN 자료형을 데이터필드로 하는 힙
	MAXHEAPTYPE huffman_heap = { 0, };
	// 파일로부터 각 글자들의 빈도수를 알아낸다
	GetText(ASCII_TABLE, pFile);
	// 알파벳 외의 것은 제외한다
	InitObject(ASCII_TABLE, object);
	// 힙 초기화
	InitHeap(&heap);
	// 최소 힙을 만든다
	MakeMinHeap(&heap, object);
	// 허프만 트리를 만든다
	root = MakeTree(&heap);
	// 트리를 출력한다 (중위 순회)
	//print_tree(root);
	// 트리로부터 허프만 코드를 생성한다
	CreateHuffmanCode(root, huffman, -1, Code);
	// 최대 힙을 만든다
	MakeMaxHeap(&huffman_heap, huffman, MAX_ALPHABET, &CountOfObject);
	// 허프만코드를 빈도수가 높은 순서대로정렬한다
	SortingHuffmanCode(&huffman_heap, huffman);
	// 최대 힙 초기화
	InitHeap(&heap);
	// 깊이로 정렬
	SortingDepth(&huffman_heap, huffman);
	// 허프만코드(빈도수, 깊이, 해당 키값 포함)를 화면에 출력한다
	PrintHuffmanCode(huffman, CountOfObject);
	// Tree Destroy
	Destroy_Tree(root);
	return 0;
}

FILE* OpenFile(void)
{
	// 파일 열기
	FILE* f = fopen("word_list.txt", "r");
	if (f == NULL) {
		printf("Cannot Open File\n");
		exit(1);
	}
}

void GetText(int *arr, FILE *pf)
{
	int index;
	// 입력된 문자를 인덱스로 하고 해당 인덱스의 값을 1씩 증가하여 빈도수를 센다.
	while ((index = fgetc(pf)) != EOF) {
		arr[index]++;
	}
}

void InitObject(int *arr, ELEMENT *obj)
{
	int index = 0, i;
	/*
	최초로 빈도수를 받은 배열은 알파벳 뿐만 아니라 다른것도 포함되어 있으므로
	알파벳 외의 문자는 제외하여 키값과 빈도수를 데이터필드로 하는 배열 자료구조에 저장
	*/
	for (i = 'a'; i <= 'z'; i++) {
		obj[index].key = i;
		obj[index++].weight = arr[i];
	}
	for (i = 'A'; i <= 'Z'; i++) {
		obj[index].key = i;
		obj[index++].weight = arr[i];
	}
}

void InitHeap(HeapType* h)
{
	// 힙을 초기화 함
	h->heap_size = 0;
}

void MakeMinHeap(HeapType* h, ELEMENT* obj)
{
	int i;
	Node* newnode;
	for (i = 0; i<MAX_ALPHABET; i++) {
		// 새로운 노드 생성
		newnode = CreateNode(NULL, NULL);
		// 노드의 데이터필드에 빈도수와 키값 복사
		newnode->data.weight = obj[i].weight;
		newnode->data.key = obj[i].key;
		// 빈도수가 0이면 힙에 삽입하지 않음
		if (obj[i].weight)
			// 최소 힙에 삽입
			InsertMinHeap(h, newnode);
	}
}

Node* CreateNode(Node* left, Node* right)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (newnode == NULL) {
		printf("Malloc Error\n");
		exit(1);
	}
	newnode->left = left;
	newnode->right = right;
	return newnode;
}

void InsertMinHeap(HeapType* h, Node* sub_root)
{
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (sub_root->data.weight < h->heap[i / 2]->data.weight)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = sub_root;
}

Node* MakeTree(HeapType* h)
{
	int size = h->heap_size;
	Node *p1, *p2, *temp;
	while (h->heap_size) {
		// 최소 힙에서 두개의 서브트리 꺼냄 ( 루트의 빈도수값이 작은 두 서브트리를 꺼냄 )
		p1 = DeleteMinHeap(h);
		p2 = DeleteMinHeap(h);
		// 꺼낸 두 서브트리를 합쳐서 하나의 트리로 만듬
		temp = CreateNode(p1, p2);
		// 데이터 복사
		temp->data.weight = p1->data.weight + p2->data.weight;
		// 이 노드의 키값과 빈도수값은 의미가 없다는 것을 표시하기 위해 알파벳이 아닌 문자 대입
		temp->data.key = '^';
		// 힙이 비었을 경우
		if (h->heap_size == 0) {
			InsertMinHeap(h, temp);
			// 힙의 루트를 반환
			return h->heap[1];
		}
		// 최소 힙 삽입
		InsertMinHeap(h, temp);
	}
	// 힙의 루트를 반환
	return h->heap[1];
}

Node* DeleteMinHeap(HeapType* h)
{
	int parent, child;
	Node *item, *temp;

	item = (h->heap[1]);
	temp = (h->heap[(h->heap_size)--]);
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child<h->heap_size) && (h->heap[child]->data.weight) > h->heap[child + 1]->data.weight)
			child++;
		if (temp->data.weight <= h->heap[child]->data.weight)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void print_tree(Node* p)
{
	if (p) {
		print_tree(p->left);
		if (p->data.key != '^')
			printf("%c : %d\n", p->data.key, p->data.weight);
		print_tree(p->right);
	}
}


void CreateHuffmanCode(Node* pnode, HUFFMAN* ph, int depth, char* code)
{
	// 허프만 트리를 순회할 시 index값이 유지되어야 하므로 static으로 선언
	static int index = 0;
	if (pnode) {
		// 노드를 방문할때마다 깊이 1씩 증가 ( 0부터 시작해야하므로 초기값 -1 )
		depth++;
		// 왼쪽 간선은 0 부여
		code[depth] = '0';
		CreateHuffmanCode(pnode->left, ph, depth, code);
		// 오른쪽 간선은 1 부여
		code[depth] = '1';
		CreateHuffmanCode(pnode->right, ph, depth, code);
		code[depth] = '\0';
		// 단말노드에 도달한 경우
		if (pnode->left == NULL && pnode->right == NULL) {
			// HUFFMAN 자료형 배열 자료구조에 허프만코드, 키, 깊이, 빈도수를 저장
			(ph + index)->key = pnode->data.key;
			(ph + index)->weight = pnode->data.weight;
			(ph + index)->depth = depth;
			strcpy((ph + index)->code, code);
			index++;
		}

	}
}

void PrintHuffmanCode(HUFFMAN* ph, int n)
{
	int i;
	for (i = 0; i<n; i++) {
		// 빈도수가 0인 것은 출력하지 않음
		if (ph[i].weight == 0)
			break;
		printf("weight = %2d depth = %2d char = %c code = %s\n", ph[i].weight, ph[i].depth,
			ph[i].key, ph[i].code);
	}
}

void MakeMaxHeap(MAXHEAPTYPE* maxheap, HUFFMAN* pHuff, int size, int *count)
{
	int i;
	// 최대 힙 삽입을 반복하여 최대 힙을 생성
	for (i = 0; i<size - 1; i++) {
		InsertMaxHeap(maxheap, pHuff[i]);
	}
	*count = maxheap->size;
}

void InsertMaxHeap(MAXHEAPTYPE* maxheap, HUFFMAN huffman)
{
	int i;
	i = ++(maxheap->size);
	while ((i != 1) && (huffman.weight > maxheap->heap[i / 2].weight)) {
		maxheap->heap[i] = maxheap->heap[i / 2];
		i /= 2;
	}
	maxheap->heap[i] = huffman;
}

HUFFMAN DeleteMaxHeap(MAXHEAPTYPE* maxheap)
{
	int parent, child;
	HUFFMAN item, temp;

	item = maxheap->heap[1];
	temp = maxheap->heap[(maxheap->size)--];
	parent = 1;
	child = 2;

	while (child <= maxheap->size) {
		if ((child < maxheap->size) && (maxheap->heap[child].weight) < maxheap->heap[child + 1].weight)
			child++;
		if (temp.weight >= maxheap->heap[child].weight)
			break;
		maxheap->heap[parent] = maxheap->heap[child];
		parent = child;
		child *= 2;
	}
	maxheap->heap[parent] = temp;
	return item;
}


void SortingHuffmanCode(MAXHEAPTYPE* maxheap, HUFFMAN* huffman)
{
	// 미리 생성된 최대힙에서 반복적인 삭제연산을 통해서 내림차순 정렬
	while (maxheap->size) {
		static int index = 0;
		huffman[index++] = DeleteMaxHeap(maxheap);
	}
}

void InitMaxHeap(MAXHEAPTYPE* maxheap)
{
	maxheap->size = 0;
}
void Destroy_Tree(Node* pNode)
{
	if (pNode == NULL) {
		return;
	}
	Destroy_Tree(pNode->left);
	Destroy_Tree(pNode->right);
	free(pNode);
}

void SortingDepth(MAXHEAPTYPE* minheap, HUFFMAN* pHuff)
{
	int pos = 0, i = 0;
	// 과거 빈도수 저장
	int preWeight = pHuff->weight;
	// 반복문, 빈도수가 0이면 탈출
	while (pHuff[i].weight) {
		while (1) {
			// 빈도수가 바뀌면 빈도수 갱신 후 탈출
			if (preWeight != pHuff[i].weight) {
				preWeight = pHuff[i].weight;
				break;
			}
			// 빈도수가 바뀔때까지 깊이 기준 최소 힙 삽입연산
			InsertMinHeap_Depth(minheap, pHuff[i++]);
		}
		while (1) {
			// 빈도수가 같은것 끼리 깊이 기준 오름차순 정렬을 위해 반복적인 힙 삭제연산
			pHuff[pos++] = DeleteMinHeap_Depth(minheap);
			if (pos == i)
				break;
		}
		// 다시 최소 힙 삽입, 삭제 연산을 하기 위해서 힙 초기화
		InitMaxHeap(minheap);
	}

}

HUFFMAN DeleteMinHeap_Depth(MAXHEAPTYPE* minheap)
{
	int parent, child;
	HUFFMAN item, temp;

	item = minheap->heap[1];
	temp = minheap->heap[(minheap->size)--];
	parent = 1;
	child = 2;

	while (child <= minheap->size) {
		if ((child < minheap->size) && ((minheap->heap[child].depth) > minheap->heap[child + 1].depth))
			child++;
		if ((temp.depth <= minheap->heap[child].depth))
			break;
		minheap->heap[parent] = minheap->heap[child];
		parent = child;
		child *= 2;
	}
	minheap->heap[parent] = temp;
	return item;
}

void InsertMinHeap_Depth(MAXHEAPTYPE* minheap, HUFFMAN huffman)
{
	int i;
	i = ++(minheap->size);
	while ((i != 1) && ((huffman.depth < minheap->heap[i / 2].depth))) {
		minheap->heap[i] = minheap->heap[i / 2];
		i /= 2;
	}
	minheap->heap[i] = huffman;
}