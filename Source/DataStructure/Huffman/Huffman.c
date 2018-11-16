// ������ �ڵ� ���� ���α׷�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Defines

#define MAX_ELEMENT 100
#define MAX_CHAR 128
#define MAX_ALPHABET 52
#define MAX_DEPTH 10
// ���� ������ ����üŸ�� ����

typedef struct HUFFMAN
{
	char key;
	int weight;
	int depth;
	char code[MAX_DEPTH];
}HUFFMAN;
// Ʈ�� ����� �������ʵ� ����üŸ�� ����

typedef struct ELEMENT
{
	char key;
	int weight;
}ELEMENT;
// Ʈ���� ǥ���ϱ� ���� ���߿��Ḯ��Ʈ ����üŸ�� ����

typedef struct Node
{
	struct Node *right, *left;
	ELEMENT data;
}Node;
// �ּ� �� ����üŸ�� ����

typedef struct HeapType
{
	Node* heap[MAX_ELEMENT];
	int heap_size;
}HeapType;
// �ִ� �� ����üŸ�� ����

typedef struct MAXHEAPTYPE
{
	HUFFMAN heap[MAX_ALPHABET];
	int size;
}MAXHEAPTYPE;

// �Լ� ������Ÿ��
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

// �����Լ�
int main(void)
{
	// �� ����� ������ ����
	int CountOfObject = 0;
	// ���� ������ �迭
	HUFFMAN huffman[MAX_ALPHABET] = { 0, };
	// ������ �ڵ� �ӽ� �������
	char Code[MAX_DEPTH] = { 0, };
	// Ʈ���� ��Ʈ
	Node* root;
	// �ּ� ��
	HeapType heap = { 0, };
	// �ƽ�Ű�ڵ带 �ε����� �־� �� ������ ���� �� �迭
	int ASCII_TABLE[MAX_CHAR] = { 0, };
	// ���� ����
	FILE* pFile = OpenFile();
	// 52���� ���ĺ��� �� �󵵼��� ������� ������ �迭
	ELEMENT object[MAX_ALPHABET] = { 0, };
	// HUFFMAN �ڷ����� �������ʵ�� �ϴ� ��
	MAXHEAPTYPE huffman_heap = { 0, };
	// ���Ϸκ��� �� ���ڵ��� �󵵼��� �˾Ƴ���
	GetText(ASCII_TABLE, pFile);
	// ���ĺ� ���� ���� �����Ѵ�
	InitObject(ASCII_TABLE, object);
	// �� �ʱ�ȭ
	InitHeap(&heap);
	// �ּ� ���� �����
	MakeMinHeap(&heap, object);
	// ������ Ʈ���� �����
	root = MakeTree(&heap);
	// Ʈ���� ����Ѵ� (���� ��ȸ)
	//print_tree(root);
	// Ʈ���κ��� ������ �ڵ带 �����Ѵ�
	CreateHuffmanCode(root, huffman, -1, Code);
	// �ִ� ���� �����
	MakeMaxHeap(&huffman_heap, huffman, MAX_ALPHABET, &CountOfObject);
	// �������ڵ带 �󵵼��� ���� ������������Ѵ�
	SortingHuffmanCode(&huffman_heap, huffman);
	// �ִ� �� �ʱ�ȭ
	InitHeap(&heap);
	// ���̷� ����
	SortingDepth(&huffman_heap, huffman);
	// �������ڵ�(�󵵼�, ����, �ش� Ű�� ����)�� ȭ�鿡 ����Ѵ�
	PrintHuffmanCode(huffman, CountOfObject);
	// Tree Destroy
	Destroy_Tree(root);
	return 0;
}

FILE* OpenFile(void)
{
	// ���� ����
	FILE* f = fopen("word_list.txt", "r");
	if (f == NULL) {
		printf("Cannot Open File\n");
		exit(1);
	}
}

void GetText(int *arr, FILE *pf)
{
	int index;
	// �Էµ� ���ڸ� �ε����� �ϰ� �ش� �ε����� ���� 1�� �����Ͽ� �󵵼��� ����.
	while ((index = fgetc(pf)) != EOF) {
		arr[index]++;
	}
}

void InitObject(int *arr, ELEMENT *obj)
{
	int index = 0, i;
	/*
	���ʷ� �󵵼��� ���� �迭�� ���ĺ� �Ӹ� �ƴ϶� �ٸ��͵� ���ԵǾ� �����Ƿ�
	���ĺ� ���� ���ڴ� �����Ͽ� Ű���� �󵵼��� �������ʵ�� �ϴ� �迭 �ڷᱸ���� ����
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
	// ���� �ʱ�ȭ ��
	h->heap_size = 0;
}

void MakeMinHeap(HeapType* h, ELEMENT* obj)
{
	int i;
	Node* newnode;
	for (i = 0; i<MAX_ALPHABET; i++) {
		// ���ο� ��� ����
		newnode = CreateNode(NULL, NULL);
		// ����� �������ʵ忡 �󵵼��� Ű�� ����
		newnode->data.weight = obj[i].weight;
		newnode->data.key = obj[i].key;
		// �󵵼��� 0�̸� ���� �������� ����
		if (obj[i].weight)
			// �ּ� ���� ����
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
		// �ּ� ������ �ΰ��� ����Ʈ�� ���� ( ��Ʈ�� �󵵼����� ���� �� ����Ʈ���� ���� )
		p1 = DeleteMinHeap(h);
		p2 = DeleteMinHeap(h);
		// ���� �� ����Ʈ���� ���ļ� �ϳ��� Ʈ���� ����
		temp = CreateNode(p1, p2);
		// ������ ����
		temp->data.weight = p1->data.weight + p2->data.weight;
		// �� ����� Ű���� �󵵼����� �ǹ̰� ���ٴ� ���� ǥ���ϱ� ���� ���ĺ��� �ƴ� ���� ����
		temp->data.key = '^';
		// ���� ����� ���
		if (h->heap_size == 0) {
			InsertMinHeap(h, temp);
			// ���� ��Ʈ�� ��ȯ
			return h->heap[1];
		}
		// �ּ� �� ����
		InsertMinHeap(h, temp);
	}
	// ���� ��Ʈ�� ��ȯ
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
	// ������ Ʈ���� ��ȸ�� �� index���� �����Ǿ�� �ϹǷ� static���� ����
	static int index = 0;
	if (pnode) {
		// ��带 �湮�Ҷ����� ���� 1�� ���� ( 0���� �����ؾ��ϹǷ� �ʱⰪ -1 )
		depth++;
		// ���� ������ 0 �ο�
		code[depth] = '0';
		CreateHuffmanCode(pnode->left, ph, depth, code);
		// ������ ������ 1 �ο�
		code[depth] = '1';
		CreateHuffmanCode(pnode->right, ph, depth, code);
		code[depth] = '\0';
		// �ܸ���忡 ������ ���
		if (pnode->left == NULL && pnode->right == NULL) {
			// HUFFMAN �ڷ��� �迭 �ڷᱸ���� �������ڵ�, Ű, ����, �󵵼��� ����
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
		// �󵵼��� 0�� ���� ������� ����
		if (ph[i].weight == 0)
			break;
		printf("weight = %2d depth = %2d char = %c code = %s\n", ph[i].weight, ph[i].depth,
			ph[i].key, ph[i].code);
	}
}

void MakeMaxHeap(MAXHEAPTYPE* maxheap, HUFFMAN* pHuff, int size, int *count)
{
	int i;
	// �ִ� �� ������ �ݺ��Ͽ� �ִ� ���� ����
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
	// �̸� ������ �ִ������� �ݺ����� ���������� ���ؼ� �������� ����
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
	// ���� �󵵼� ����
	int preWeight = pHuff->weight;
	// �ݺ���, �󵵼��� 0�̸� Ż��
	while (pHuff[i].weight) {
		while (1) {
			// �󵵼��� �ٲ�� �󵵼� ���� �� Ż��
			if (preWeight != pHuff[i].weight) {
				preWeight = pHuff[i].weight;
				break;
			}
			// �󵵼��� �ٲ𶧱��� ���� ���� �ּ� �� ���Կ���
			InsertMinHeap_Depth(minheap, pHuff[i++]);
		}
		while (1) {
			// �󵵼��� ������ ���� ���� ���� �������� ������ ���� �ݺ����� �� ��������
			pHuff[pos++] = DeleteMinHeap_Depth(minheap);
			if (pos == i)
				break;
		}
		// �ٽ� �ּ� �� ����, ���� ������ �ϱ� ���ؼ� �� �ʱ�ȭ
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