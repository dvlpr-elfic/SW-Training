#include <stdio.h>
#include <time.h>

#define MAX_ELEMENT 20
#define MAX_STEM 10
#define _FILE_ "score.txt"
#define _MODE_ "r"
// �� �ٱ⸦ ��Ÿ�� ����ü
typedef struct Stem
{
	int leaf[MAX_ELEMENT];
	int count;
}Stem;
// ��ü �ٱ�-���� �ϳ��� ����ü�� ��� ����
typedef struct StemLeafTable
{
	Stem stem[MAX_STEM];
}StemLeafTable;
// ���ǻ� ����ü������ �̸��� �ٿ��� ���
typedef StemLeafTable Table;

// Function prototype
// �ؽ�Ʈ���Ͽ� �ִ� �����͵��� ���̺� ����
void GetData2Table(Table*);
// ���̺��� ������ ���
void DisplayTable(Table*);
// Sorting
// �� ������ �̿��ؼ� ���̺��� �� �����͸� ����
void SortTableByQuickSort(Table*);
// �� ���� �˰���
void QuickSort(int*, int, int);
// �� ���Ľ� �ǹ��� ����
int partition(int*, int, int);
// ���� ���� �˰���
void BubbleSort(int*, int);
// ���� ������ �̿��ؼ� ���̺��� �� �����͸� ����
void SortTableByBubbleSort(Table*);
// �� ���� �˰���
void ShellSort(int*, int);
// �� ���Ľ� ��(gap)�� ���� ���������ϴ� �˰���
void inc_insertion_sort(int*, int, int, int);
// �� ������ �̿��ؼ� ���̺��� �� �����͸� ����
void SortTableByShellSort(Table*);
// �ð� ������ ���Ǵ� �Լ�
// ��ó : http://exeter.tistory.com/86
long long GetTimeDiff(unsigned int);

int main(void)
{
	// ���� ����
	Table table = {0, };
	// 3���� ���ľ˰��� ���� �� �������� ������ �����ϱ� ���� 3���� ����ü ���� ����
	Table table_for_quick, table_for_bubble, table_for_shell;
	// ���̺� �ʱ�ȭ
	GetData2Table(&table);
	table_for_quick = table_for_bubble = table_for_shell = table;
	// Quick Sort
	// �ð����� ����
	GetTimeDiff(0);
	// �� ������ �̿��ؼ� ���̺��� �� �����͸� ����
	SortTableByQuickSort(&table_for_quick);
	// �ð����� ����, ����ð��� ����ũ�μ�ũ ������ ǥ��
	printf("Quick Sort : %lld[usec]\n", GetTimeDiff(1));
	// ���̺��� ������ ȭ�鿡 ���
	DisplayTable(&table_for_quick);
	// Bubble Sort
	// �ð����� ����
	GetTimeDiff(0);
	// ���� ������ �̿��ؼ� ���̺��� �� �����͸� ����
	SortTableByBubbleSort(&table_for_bubble);
	// �ð����� ����, ����ð��� ����ũ�μ�ũ ������ ǥ��
	printf("Bubble Sort : %lld[usec]\n", GetTimeDiff(1));
	// ���̺��� ������ ȭ�鿡 ���
	DisplayTable(&table_for_bubble);
	//Shell Sort
	// �ð����� ����
	GetTimeDiff(0);
	// �� ������ �̿��ؼ� ���̺��� �� �����͸� ����
	SortTableByShellSort(&table_for_shell);
	// �ð����� ����, ����ð��� ����ũ�μ�ũ ������ ǥ��
	printf("Shell Sort : %lld[usec]\n", GetTimeDiff(1));
	// ���̺��� ������ ȭ�鿡 ���
	DisplayTable(&table_for_shell);
	return 0;
}
// �ؽ�Ʈ������ �����͸� ���̺� ����
void GetData2Table(Table* ptable)
{
	// ���� ����
	FILE* pFile = fopen(_FILE_, _MODE_);
	if(!pFile){
		fprintf(stderr, "Fail Open File\n");
		exit(1);
	}
	// ������ ���������� ������ ���
	else{
		int temp;
		// ������ ������ �����Ҷ����� ���������͸� ����
		while(fscanf(pFile, "%d", &temp) != EOF){
			// ���� ���� �����͸� �ش� �ٱ��� �� �迭�� �������� �ʰ� ������� ����
			ptable->stem[temp/10].leaf[ptable->stem[temp/10].count++] = temp;
		}
	}
	// ���� �ݱ�
	fclose(pFile);
}
// ���̺��� ������ ȭ�鿡 ���
void DisplayTable(Table* ptable)
{
	int i, j;
	printf("------------------------------------------------------------------------\n");
	// �ٱ��� ������ŭ �ݺ�
	for(i=0; i<MAX_STEM; i++){
		// � �ٱ������� �ش� �ٱ��� �� ������ ���
		printf("| %2d | %2d |", i*10, ptable->stem[i].count);
		// ���� ������ŭ �ݺ��ؼ� ���� �����͸� ���
		for(j=0; j<(ptable->stem[i].count); j++){
			printf("%4d", ptable->stem[i].leaf[j]);
		}
		printf("\n");
	}
	printf("------------------------------------------------------------------------\n");
}
// �� ���� �˰���
void QuickSort(int* list, int left, int right)
{
	if(left < right){
		int q = partition(list, left, right);
		QuickSort(list, left, q-1);
		QuickSort(list, q+1, right);
	}
}
// �� ������ ���� �ǹ��� ���ϰ� �����͸� �̵��ϴ� �˰���
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
// �� ������ �̿��� ���̺��� �� �����͸� ����
void SortTableByQuickSort(Table* ptable)
{
	int i;
	// �ٱ��� ������ŭ �� ���� �ݺ� ( �� �ٱ⸦ �� ������ ������������ ���� )
	for(i=0; i<MAX_STEM; i++){
		QuickSort(ptable->stem[i].leaf, 0, ptable->stem[i].count-1);
	}
}
// ���� ���� �˰����� �̿��ؼ� ���̺��� �� �����͸� ����
void SortTableByBubbleSort(Table* ptable)
{
	int i;
	// �ٱ��� ������ŭ �������� �ݺ� ( �� �ٱ⸦ �� ������ ������������ ���� )
	for(i=0; i<MAX_STEM; i++){
		BubbleSort(ptable->stem[i].leaf, ptable->stem[i].count);
	}
}
// �� ���� �˰���
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
// �� ���Ľ� ���� ���� ���������ϴ� �Լ�
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
// �� ������ �̿��ؼ� ���̺��� �� �����͸� ����
void SortTableByShellSort(Table* ptable)
{
	int i;
	// �ٱ��� ������ŭ �� ���� �ݺ� ( �� �ٱ⸦ �� ������ ������������ ���� )
	for(i=0; i<MAX_STEM; i++){
		ShellSort(ptable->stem[i].leaf, ptable->stem[i].count);
	}
}
// ���� ���� �˰���
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
// �ð� ������ ���ؼ� clock_gettime �Լ��� �̿��� ����ũ�μ�ũ������ �ð��� ����
// ��ó : http://exeter.tistory.com/86
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
