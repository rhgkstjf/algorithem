#include<iostream>
using namespace std;

#define MAX 100
int answer[MAX];

void merge_sort(int a[], int start, int end);
void merge(int a[], int start, int end, int mid);
void print_arr(int a[], int size);

int main() {


	int a[] = { 6,1,2,7,10,52,44,12,24 };

	merge_sort(a, 0, 8);
	print_arr(a, 8);
	return 0;
}


void merge_sort(int a[], int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort(a, start, mid);
		merge_sort(a, mid + 1, end);
		merge(a, start, end, mid);
	}
}

void merge(int a[], int start, int end, int mid)
{
	int index1 = start;
	int index2 = mid+1;
	int index_ans = start;
	while (index1 <= mid && index2 <= end){
		if (a[index1] <= a[index2])
			answer[index_ans++] = a[index1++];
		else
			answer[index_ans++] = a[index2++];
	}
	if (index1 > mid)
	{
		for (int i = index2; i <= end; i++)
			answer[index_ans++] = a[i];
	}
	else
	{
		for (int i = index1; i <= mid; i++)
			answer[index_ans++] = a[i];
	}
	for (int i = start; i <= end; i++)
	{
		a[i] = answer[i];
	}
}

void print_arr(int a[], int size)
{
	for (int i = 0; i <= size; i++)
		cout << a[i] << " ";
	cout << endl;
}
