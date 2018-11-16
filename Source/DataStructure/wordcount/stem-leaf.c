#include <stdio.h>
#include <time.h>

#define MAX_ELEMENT 20
#define MAX_STEM 10
#define _FILE_ "score.txt"
#define _MODE_ "r"
// 한 줄기를 나타낼 구조체
typedef struct Stem
{
	int leaf[MAX_ELEMENT];
	int count;
}Stem;
// 전체 줄기-잎을 하나의 구조체로 묶어서 정의
typedef struct StemLeafTable
{
	Stem stem[MAX_STEM];
}StemLeafTable;
// 편의상 구조체변수의 이름을 줄여서 사용
typedef StemLeafTable Table;

// Function prototype
// 텍스트파일에 있는 데이터들을 테이블에 넣음
void GetData2Table(Table*);
// 테이블의 내용을 출력
void DisplayTable(Table*);
// Sorting
// 퀵 정렬을 이용해서 테이블의 잎 데이터를 정렬
void SortTableByQuickSort(Table*);
// 퀵 정렬 알고리즘
void QuickSort(int*, int, int);
// 퀵 정렬시 피벗을 결정
int partition(int*, int, int);
// 버블 정렬 알고리즘
void BubbleSort(int*, int);
// 버블 정렬을 이용해서 테이블의 잎 데이터를 정렬
void SortTableByBubbleSort(Table*);
// 셸 정렬 알고리즘
void ShellSort(int*, int);
// 셸 정렬시 갭(gap)에 따라 삽입정렬하는 알고리즘
void inc_insertion_sort(int*, int, int, int);
// 셸 정렬을 이용해서 테이블의 잎 데이터를 정렬
void SortTableByShellSort(Table*);
// 시간 측정시 사용되는 함수
// 출처 : http://exeter.tistory.com/86
long long GetTimeDiff(unsigned int);

int main(void)
{
	// 변수 선언
	Table table = {0, };
	// 3가지 정렬알고리즘에 의해 잎 데이터의 정렬을 구현하기 위해 3가지 구조체 변수 선언
	Table table_for_quick, table_for_bubble, table_for_shell;
	// 테이블 초기화
	GetData2Table(&table);
	table_for_quick = table_for_bubble = table_for_shell = table;
	// Quick Sort
	// 시간측정 시작
	GetTimeDiff(0);
	// 퀵 정렬을 이용해서 테이블의 잎 데이터를 정렬
	SortTableByQuickSort(&table_for_quick);
	// 시간측정 종료, 경과시간을 마이크로세크 단위로 표시
	printf("Quick Sort : %lld[usec]\n", GetTimeDiff(1));
	// 테이블의 내용을 화면에 출력
	DisplayTable(&table_for_quick);
	// Bubble Sort
	// 시간측정 시작
	GetTimeDiff(0);
	// 버블 정렬을 이용해서 테이블의 잎 데이터를 정렬
	SortTableByBubbleSort(&table_for_bubble);
	// 시간측정 종료, 경과시간을 마이크로세크 단위로 표시
	printf("Bubble Sort : %lld[usec]\n", GetTimeDiff(1));
	// 테이블의 내용을 화면에 출력
	DisplayTable(&table_for_bubble);
	//Shell Sort
	// 시간측정 시작
	GetTimeDiff(0);
	// 셸 정렬을 이용해서 테이블의 잎 데이터를 정렬
	SortTableByShellSort(&table_for_shell);
	// 시간측정 종료, 경과시간을 마이크로세크 단위로 표시
	printf("Shell Sort : %lld[usec]\n", GetTimeDiff(1));
	// 테이블의 내용을 화면에 출력
	DisplayTable(&table_for_shell);
	return 0;
}
// 텍스트파일의 데이터를 테이블에 넣음
void GetData2Table(Table* ptable)
{
	// 파일 열기
	FILE* pFile = fopen(_FILE_, _MODE_);
	if(!pFile){
		fprintf(stderr, "Fail Open File\n");
		exit(1);
	}
	// 파일을 성공적으로 열었을 경우
	else{
		int temp;
		// 파일의 끝까지 도달할때까지 정수데이터를 읽음
		while(fscanf(pFile, "%d", &temp) != EOF){
			// 읽은 정수 데이터를 해당 줄기의 잎 배열에 정렬하지 않고 순서대로 넣음
			ptable->stem[temp/10].leaf[ptable->stem[temp/10].count++] = temp;
		}
	}
	// 파일 닫기
	fclose(pFile);
}
// 테이블의 내용을 화면에 출력
void DisplayTable(Table* ptable)
{
	int i, j;
	printf("------------------------------------------------------------------------\n");
	// 줄기의 개수만큼 반복
	for(i=0; i<MAX_STEM; i++){
		// 어떤 줄기인지와 해당 줄기의 잎 개수를 출력
		printf("| %2d | %2d |", i*10, ptable->stem[i].count);
		// 잎의 개수만큼 반복해서 잎의 데이터를 출력
		for(j=0; j<(ptable->stem[i].count); j++){
			printf("%4d", ptable->stem[i].leaf[j]);
		}
		printf("\n");
	}
	printf("------------------------------------------------------------------------\n");
}
// 퀵 정렬 알고리즘
void QuickSort(int* list, int left, int right)
{
	if(left < right){
		int q = partition(list, left, right);
		QuickSort(list, left, q-1);
		QuickSort(list, q+1, right);
	}
}
// 퀵 정렬을 위해 피벗을 정하고 데이터를 이동하는 알고리즘
int partition(int* list, int left, int right)
{
	int pivot, temp;
	int low, high;
	
	low = left;
	high = right + 1;
	pivot = list[left];
	do{
		do
			low++;
		while(low <= right && list[low] < pivot);
		do
			high--;
		while(high >= left && list[high] > pivot);
		if(low < high){
			temp = list[low];
			list[low] = list[high];
			list[high] = temp;
		}
	}while(low < high);
	temp = list[left];
	list[left] = list[high];
	list[high] = temp;

	return high;
}
// 퀵 정렬을 이용해 테이블의 잎 데이터를 정렬
void SortTableByQuickSort(Table* ptable)
{
	int i;
	// 줄기의 개수만큼 퀵 정렬 반복 ( 각 줄기를 잎 데이터 오름차순으로 정렬 )
	for(i=0; i<MAX_STEM; i++){
		QuickSort(ptable->stem[i].leaf, 0, ptable->stem[i].count-1);
	}
}
// 버블 정렬 알고리즘을 이용해서 테이블의 잎 데이터를 정렬
void SortTableByBubbleSort(Table* ptable)
{
	int i;
	// 줄기의 개수만큼 버블정렬 반복 ( 각 줄기를 잎 데이터 오름차순으로 정렬 )
	for(i=0; i<MAX_STEM; i++){
		BubbleSort(ptable->stem[i].leaf, ptable->stem[i].count);
	}
}
// 셸 정렬 알고리즘
void ShellSort(int* list, int n)
{
	int i, gap;
	for(gap=n/2; gap>0; gap = gap/2){
		if((gap%2) == 0) gap++;
		for(i=0; i<gap; i++){
			inc_insertion_sort(list, i, n-1, gap);
		}
	}
}
// 셸 정렬시 갭에 따라서 삽입정렬하는 함수
void inc_insertion_sort(int* list, int first, int last, int gap)
{
	int i,j;
	int key;
	for(i=first+gap; i<=last; i=i+gap){
		key = list[i];
		for(j=i-gap; j>=first && key < list[j]; j=j-gap)
			list[j+gap] = list[j];
		list[j+gap] = key;
	}
}
// 셸 정렬을 이용해서 테이블의 잎 데이터를 정렬
void SortTableByShellSort(Table* ptable)
{
	int i;
	// 줄기의 개수만큼 셸 정렬 반복 ( 각 줄기를 잎 데이터 오름차순으로 정렬 )
	for(i=0; i<MAX_STEM; i++){
		ShellSort(ptable->stem[i].leaf, ptable->stem[i].count);
	}
}
// 버블 정렬 알고리즘
void BubbleSort(int *arr, int size)
{
	int j = 0;
	int i = 0;

	for (j = 0; j < size - 1; j++) {
		for (i = 0; i < size - 1 - j; i++) {
			if (arr[i] > arr[i + 1]) {
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
}
// 시간 측정을 위해서 clock_gettime 함수를 이용해 마이크로세크단위로 시간을 측정
// 출처 : http://exeter.tistory.com/86
long long GetTimeDiff(unsigned int nFlag)
{
	const long long NANOS = 1000000000LL;
	static struct timespec startTS, endTS;
	static long long retDiff = 0;
	if(nFlag == 0){
		retDiff = 0;
		if( -1 == clock_gettime(CLOCK_MONOTONIC, &startTS))
			printf("Failed to call clock_gettime\n");
	}
	else{
		if( -1 == clock_gettime(CLOCK_MONOTONIC, &endTS))
			printf("Failed to call clock_gettime\n");
		retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
	}
	return retDiff/1000;
}
