#include<iostream>
#include<vector>
using namespace std;



void quick_sort(int A[], int left, int right);
void selection(int A[], int left, int right, int k);
int partition(int A[], int left, int right);
void swap(int* a, int* b);
void print_vector(int A[], int start, int end);


int main()
{
    int A[] = { 6,3,11,9,12,2,8,15,18,10,7,14 };
    //
    quick_sort(A, 0, 11);
    selection(A, 0, 11, 9);
    //print_vector(A,0,11);

    return 0;
}

void quick_sort(int A[], int left, int right)
{
    if (left < right)
    {
        int pivot = partition(A, left, right);
        quick_sort(A, left, pivot - 1);
        quick_sort(A, pivot + 1, right);
    }

}

int partition(int A[], int left, int right)
{
    int low = left - 1;
    int high = right;
    int pivot = A[right];

    do
    {
        do
        {
            low++;
        } while (A[low] < pivot && low <= right);
        do
        {
            high--;
        } while (A[high] > pivot&& high >= left);
        if (low < high)
        {
            swap(&A[low], &A[high]);
        }
    } while (low < high);

    swap(&A[right], &A[low]);
    print_vector(A, left, right);
    return low;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_vector(int A[], int start, int end)
{
    for (int p = start; p < end; p++)
        cout << A[p] << " ";
    cout << endl;
}

void selection(int A[], int left, int right, int k)
{
    if (left < right)
    {
        int pivot = partition(A, left, right);
        int size = (pivot - 1) - left + 1;
        cout << "pivot: " << A[pivot] << endl;
        cout << "k: " << k << endl;
        cout << "size: " << size << endl;
        if (k <= size)
        {
            //cout << "왼쪽 사이즈가 더 큼" << endl;
            selection(A, left, pivot - 1, k);
        }
        else if (k == size + 1)
            cout << A[pivot] << endl;
        else {
            //cout << "왼쪽에 없음" << endl;
            selection(A, pivot + 1, right, k - size - 1);
        }
    }
    else
        cout << A[left];
}
