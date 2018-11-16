// 학생 정보를 시험 성적과 이름순서대로 정렬하는 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 10
#define MAX_SUBJECT 5
#define MAX_STUDENT 100
#define MAX_ID 5
#define MAX_CHAR_PER_LINE 100
#define MAX_WORD_PER_LINE 8
#define MAX_HEAP_SIZE 101

typedef struct STUDENT
{
	char number[MAX_ID];
	char id[MAX_ID];
	char name[MAX_NAME];
	int score[MAX_SUBJECT];
	float average;
}STUDENT;

typedef struct HeapType
{
	STUDENT heap[MAX_HEAP_SIZE];
	int heap_size;
}HeapType;

FILE* OpenFile(void);
void GetStudentInfo(FILE*, STUDENT*);
void PrintStudentInfo(STUDENT*);
void MinHeapSort(HeapType*, STUDENT*);
void InsertMinHeap(HeapType*, STUDENT);
STUDENT DeleteMinHeap(HeapType*);
void MaxHeapSort(HeapType*, STUDENT*);
void InsertMaxHeap(HeapType*, STUDENT);
STUDENT DeleteMaxHeap(HeapType*);
void InitHeap(HeapType*);

int main(void)
{
	// 힙
	HeapType heap = {0, };
	// 학생 정보 배열
	STUDENT student[MAX_STUDENT] = {0, };
	// 파일 열기
	FILE* pFile = OpenFile();
	// 파일로부터 학생정보 읽기
	GetStudentInfo(pFile, student);
	printf("------------------- 평균점수로 정렬 --------------------\n");
	// 평균점수로 정렬 진행
	MinHeapSort(&heap, student);
	// 평균점수로 오름차순 정렬된 정보를 출력
	PrintStudentInfo(student);
	// 힙 초기화
	InitHeap(&heap);
	// 이름 순으로 정렬진행
	MaxHeapSort(&heap, student);
	printf("------------------- 이름 순으로 정렬 -------------------\n");
	// 이름순으로 오름차순 정렬된 정보를 출력
	PrintStudentInfo(student);
	// 파일 닫기
	fclose(pFile);
	return 0;
}

FILE* OpenFile(void)
{
	FILE* f = fopen("Score-100.txt", "r");
	if(f == NULL){
		fprintf(stderr, "Cannot Open File\n");
		exit(1);
	}
	else
		return f;
}


void GetStudentInfo(FILE* f, STUDENT* s)
{
	int i, j, k;
	char ch = 0;
	char str[MAX_WORD_PER_LINE][MAX_CHAR_PER_LINE] = {0, };
	char score[MAX_SUBJECT] = {0, };
	// 텍스트파일의 첫번째 라인 무시
	fgets(*str, MAX_CHAR_PER_LINE, f);
	// 학생 정보를 텍스트 파일로부터 읽음
	for(i=0; i<MAX_STUDENT; i++){
		s[i].average = 0.0;
		for(j=0; j<MAX_WORD_PER_LINE; j++){
			fscanf(f, "%s", str[j]);
		}
		strcpy(s[i].number, str[0]), strcpy(s[i].id, str[1]), strcpy(s[i].name, str[2]);
		for(k=0; k<MAX_SUBJECT; k++){
			s[i].score[k] = atoi(str[k+3]);
			s[i].average += (float)(s[i].score[k]);
		}
		s[i].average /= (float)MAX_SUBJECT;
	}
}

void PrintStudentInfo(STUDENT* s)
{
	int i;
	printf("   NO   ID   NAME     C1    C2    C3    C4    C5   AVG\n");
	for(i=0; i<MAX_STUDENT; i++){
		printf("%5s %5s %5s %5d %5d %5d %5d %5d %5.1f\n", s[i].number, s[i].id, s[i].name,
				s[i].score[0], s[i].score[1], s[i].score[2], s[i].score[3], s[i].score[4], s[i].average);
	}
}

void MinHeapSort(HeapType* h, STUDENT* s)
{
	int i;
	// 최소 힙을 만듬
	for(i=0; i<MAX_STUDENT; i++){
		InsertMinHeap(h, s[i]);
	}
	// 최소 힙에서 하나씩 꺼내어 배열에 차곡차곡 쌓는다
	for(i=0; i<MAX_STUDENT; i++){
		s[i] = DeleteMinHeap(h);
	}
}

void InsertMinHeap(HeapType* h, STUDENT item)
{
	int i;
	i = ++(h->heap_size);
	
	while((i != 1) && (item.average < h->heap[i/2].average)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

STUDENT DeleteMinHeap(HeapType* h)
{
	int parent, child;
	STUDENT item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while(child <= h->heap_size){
		if((child < h->heap_size) && (h->heap[child].average) > h->heap[child+1].average)
			child++;
		if(temp.average <= h->heap[child].average)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}


void MaxHeapSort(HeapType* h, STUDENT* s)
{
	int i;
	for(i=0; i<MAX_STUDENT; i++){
		InsertMaxHeap(h, s[i]);
	}
	for(i=0; i<MAX_STUDENT; i++){
		s[i] = DeleteMaxHeap(h);
	}
}

void InsertMaxHeap(HeapType* h, STUDENT item)
{
	int i;
	i = ++(h->heap_size);
	while((i != 1) && (strcmp(item.name, h->heap[i/2].name) < 0)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

STUDENT DeleteMaxHeap(HeapType* h)
{
	int parent, child;
	STUDENT item, temp;
	
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while(child <= h->heap_size){
		if((child < h->heap_size) && (strcmp(h->heap[child].name, h->heap[child+1].name) > 0))
			child++;
		if(strcmp(temp.name, h->heap[child].name) <= 0)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void InitHeap(HeapType *h)
{
	h->heap_size = 0;
}
