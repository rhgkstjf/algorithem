#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAX 100001

int temp[MAX];

typedef struct {
	int a[MAX];
	int size;
	long long compare;
	long long move;
	double time;
	char name[25];
}eval;
typedef eval* evalptr;

typedef struct {
	eval sort[7];
}state;
typedef state* stateptr;

typedef struct {
	int h[MAX];
	int hs;
}heap;
typedef heap* heaptr;

void swap(int *a, int *b);
void init_eval(evalptr e, int size);
void print_arr(int arr[], int size);


void selection_sort(evalptr e);
void bubble_sort(evalptr e);
void insert_sort(evalptr e);
void shell_insert_sort(int a[], int first, int last, int gap, evalptr e);
void shell_sort(evalptr e);
void merge_sort(int a[], int start, int end, evalptr e);
void merge(int a[], int start, int end, int mid, evalptr e);
int partition(int a[], int start, int end,evalptr e);
void quick_sort(int a[], int start, int end, evalptr e);
void heap_sort(int a[], evalptr e);

void insert_heap(heaptr h,int item, evalptr e);
int delete_heap(heaptr h, evalptr e);
void init_heap(heaptr h);

void caclStatistics(stateptr stats,int n);
void cmpSortsByTable(stateptr stats);

int main()
{
	stateptr s = (stateptr)malloc(sizeof(state));
	/*evalptr e = (evalptr)malloc(sizeof(eval));
	init_eval(e, 11);

	heaptr h = (heaptr)malloc(sizeof(heap));
	init_heap(h);

	for (int i = 1; i < 10 + 1; i++)
	{
		insert_heap(h, e->a[i], e);
	}
	for (int i = h->hs; i > 0; i--)
	{
		delete_heap(h, e);
	}*/

	for (int i = 1; i < 3; i++)
	{
		caclStatistics(s,i);
		cmpSortsByTable(s);
	}
	free(s);
	return 0;
}

void swap(int *a, int *b)
{
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;
}

void init_eval(evalptr e, int size)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++)
		e->a[i] = rand() % 1000 + 1;

	e->compare = 0;
	e->move = 0;
	e->size = size;
	e->time = 0.0;
}

void print_arr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");
}

void bubble_sort(evalptr e)
{
	init_eval(e, e->size);
	for (int i = e->size; i >= 0; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			e->compare += 1;
			if (e->a[j] > e->a[j + 1])
			{
				swap(&(e->a[j]), &e->a[j + 1]);
				e->move += 3;
			}
		}
	}
}

void selection_sort(evalptr e)
{
	int least = 0;
	init_eval(e, e->size);
	for (int i = 0; i < e->size - 1; i++)
	{
		least = i;
		for (int j = i + 1; j < e->size; j++)
		{
			e->compare += 1;
			if (e->a[least] > e->a[j])
				least = j;
		}
		if (least != i)
		{
			swap(&(e->a[least]), &(e->a[i]));
			e->move += 3;
		}
	}
}

void insert_sort(evalptr e)
{
	init_eval(e, e->size);
	int  j = 0, key = 0;
	for (int i = 1; i < e->size; i++)
	{
		j = i - 1;
		key = e->a[i];

		while (j >= 0 && e->a[j] > key)
		{
			e->compare += 1;
			e->a[j + 1] = e->a[j];
			j--; e->move += 1;
		}

		e->a[j + 1] = key;
	}
}

void shell_insert_sort(int a[], int first, int last, int gap, evalptr e)
{
	int key = 0, j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		key = a[i];
		j = i - gap;
		while (j >= first && a[j] > key)
		{
			e->compare += 1;

			a[j + gap] = a[j];
			e->move += 1;

			j = j - gap;
		}
		a[j + gap] = key;
	}
}

void shell_sort(evalptr e)
{
	init_eval(e, e->size);
	int gap = 0;
	for (gap = e->size / 2; gap > 0; gap = gap / 2)
	{
		if (gap % 2 == 0)		gap++;

		for (int i = 0; i < gap; i++)
		{
			shell_insert_sort(e->a, 0, e->size, gap, e);
		}
	}
}


void merge(int a[], int start, int end, int mid, evalptr e)
{
	int part1 = start;
	int part2 = mid + 1;
	int index = start;

	while (part1 <= mid && part2 <= end)
	{
		e->compare += 1;
		e->move += 1;
		if (a[part1] <= a[part2])
		{
			temp[index] = a[part1];
			part1++;
		}
		else
		{
			temp[index] = a[part2];
			part2++;
		}
		index++;
	}
	if (part1 > mid)
	{
		for(int i=part2 ;i<=end;i++)
			temp[index++] = a[i];
		
	}
	else {
		for (int i = part1; i <= mid; i++)
			temp[index++] = a[i];
	}

	for (int i = start; i <= end; i++)
	{
		a[i] = temp[i];
	}
}

void merge_sort(int a[], int start, int end, evalptr e)
{
	int mid;
	if (start < end)
	{
		mid = (start + end) / 2;
		merge_sort(a, start, mid, e);
		merge_sort(a, mid + 1, end, e);
		merge(a, start, end, mid, e);
	}
}


void insert_heap(heaptr h,int item,evalptr e)
{
	h->hs = h->hs + 1;
	int i = h->hs;
	while (i > 1 && h->h[i / 2] > item)
	{
		e->compare += 1;
		e->move += 1;
		h->h[i] = h->h[i / 2];
		i /= 2;
	}
	h->h[i] = item;
}
int delete_heap(heaptr h,evalptr e)
{
	int item = h->h[1];
	int value = h->h[h->hs--];
	int i = 1, j = 2;
	while (j <= h->hs)
	{
		e->compare += 1;
		if (j < h->hs && h->h[j] > h->h[j + 1])
			j += 1;
		if (value > h->h[j]) break;

		e->move += 1;
		h->h[i] = h->h[j];
		i = j;
		j *= 2;
	}
	e->move += 1;
	h->h[i] = value;
	return item;
}
void heap_sort(int a[], evalptr e)
{
	heaptr h = (heaptr)malloc(sizeof(heap));
	init_heap(h);
	int j = 0;
	for (int i = 1; i <= e->size; i++)
	{
		insert_heap(h,a[i-1],e);
	}
	while (int i = h->hs > 0)
	{
		a[j++] = delete_heap(h, e);
		i--;
	}
	
}
void init_heap(heaptr h)
{
	h->hs = 0;
}


void quick_sort(int a[], int start, int end,evalptr e)
{
	if (start < end)
	{
		int pivot = partition(a, start, end,e);
		quick_sort(a, start, pivot - 1,e);
		quick_sort(a, pivot + 1, end,e);
	}
}

int partition(int a[], int start, int end,evalptr e)
{
	int pivot = a[start];
	int low = start;
	int high = end + 1;

	do {
		do { low++;  e->compare += 1; } while (low <= end && a[low] < pivot);
		do { high--; e->compare += 1; } while (high >= start && a[high] > pivot);

		if (low < high)
		{
			swap(&a[low], &a[high]);
			e->move += 1;
		}
	} while (low < high);
	swap(&a[start], &a[high]);
	e->move += 1;
	return high;
}


void caclStatistics(stateptr stats,int n)
{
	clock_t start, end;
	double elapsed = 0.0;
	
	for (int i = 0; i < 7; i++)
	{
		init_eval(&stats->sort[i], 4*n);
	}
	

	start = clock();
	selection_sort(&stats->sort[0]);
	end = clock();
	strcpy(stats->sort[0].name, "선택정렬");
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats->sort[0].time = elapsed;


	start = clock();
	bubble_sort(&stats->sort[1]);
	end = clock();
	strcpy(stats->sort[1].name, "버블정렬");
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats->sort[1].time = elapsed;


	start = clock();
	insert_sort(&stats->sort[2]);
	end = clock();
	strcpy(stats->sort[2].name, "삽입정렬");
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats->sort[2].time = elapsed;

	start = clock();
	shell_sort(&stats->sort[3]);
	end = clock();
	strcpy(stats->sort[3].name, "쉘  정렬");
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats->sort[3].time = elapsed;

	start = clock();
	heap_sort(stats->sort[4].a,&stats->sort[4]);
	end = clock();
	strcpy(stats->sort[4].name, "히프 정렬");
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats->sort[4].time = elapsed;

	start = clock();
	quick_sort(stats->sort[5].a, 0, stats->sort[5].size-1, &stats->sort[5]);
	end = clock();
	strcpy(stats->sort[5].name, "퀵  정렬");
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats->sort[5].time = elapsed;

	start = clock();
	merge_sort(stats->sort[6].a, 0, stats->sort[6].size-1 , &stats->sort[6]);
	end = clock();
	strcpy(stats->sort[6].name, "합병 정렬");
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats->sort[6].time = elapsed;
}

void cmpSortsByTable(stateptr stats)
{
	printf("---------------------------------------------------------------------------------\n");
	printf("구분		소요시간			비교횟수		이동횟수\n");
	for (int i = 0; i < 7; i++)
	{

			printf("%s	  %.6lf			  %lld			%lld \n",
				stats->sort[i].name, stats->sort[i].time, stats->sort[i].compare, stats->sort[i].move);
	
	}
	printf("---------------------------------------------------------------------------------\n");
	for (int i = 0; i < 7; i++)
	{

			print_arr(stats->sort[i].a, stats->sort[i].size);

	}
	for (int i = 7; i < 0; i--)
	{
		free(stats->sort[i].a);
	}
}
