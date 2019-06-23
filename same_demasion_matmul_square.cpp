#define _CRT_SECURE_NO_WARNINGS_
#include<stdio.h>
#include<stdlib.h>


int** make(int *,int *);
int** culcu(int **, int **, int, int, int);
void display(int**,int, int);
void culcu_jung(int**, int);


int main()
{
	int **f = NULL;
	int x = 0, y = 0;
	f = make(&x, &y);
	culcu_jung(f, x);


	return 0;
}


int** culcu(int **f, int **f1, int x2, int y1, int m)
{
	int tmp = 0, yg = 0, xg = 0;
	int **p = (int**)malloc(sizeof(int*)*y1);

	for (int i = 0; i < y1; i++)
	{
		*(p + i) = (int*)malloc(sizeof(int)*x2);
		for (int k = 0; k < x2; k++)
		{
			for (int t = 0; t < m; t++)
			{
				tmp += *(*(f + i) + xg)  *  *(*(f1 + yg) + k);
				xg++;  yg++;
			}
			*(*(p + i) + k) = tmp;
			xg = 0;
			yg = 0;
			tmp = 0;
		}
	}
	return p;
}

void culcu_jung(int **f, int xy)
{
	int **tmp = NULL;
	tmp = f;
	int n = 0;
	printf("행렬 A의  몇승? 하실건가요?");
	scanf_s("%d", &n);

	for (int i = 0; i < n-1; i++)
	{
		tmp = culcu(tmp, f, xy, xy, xy);
	}

	display(tmp, xy, xy);
}




int** make(int *x1,int *y1)
{
	int y = 0, x = 0;
	
	printf("정방행렬 의 행 입력:");
	scanf_s("%d", &x);

	*x1 = x;
	*y1 = x;

	int **f = (int**)malloc(sizeof(int*)*x);
	for (int i = 0; i < x; i++)
	{
		*(f + i) = (int*)malloc(sizeof(int)*x);
		printf("%d 번째 행의 열입력:",i);
		for (int k = 0; k < x; k++)
		{
			scanf_s("%d", &(*(*(f + i) + k)));
		}
	}
	

	return f;
}



void display(int **f,int x, int y)
{
	for (int i = 0; i < y; i++) {
		for (int k = 0; k < x; k++)
		{
			printf("%d ", *(*(f + i) + k));
		}
		printf("\n");
	}
}
