#define _CRT_SECURE_NO_WARNINGS_
#include<stdio.h>
#include<stdlib.h>


int** make(int *,int *);
void display(int**,int, int);
void culcu(int**, int**,int,int,int);


int main()
{
	int **f = NULL;
	int **f1 = NULL;
	int x1=0, y1=0, x2=0, y2=0;
	f = make(&x1,&y1);
	f1 = make(&x2,&y2);
	
	display(f, x1, y1);
	display(f1, x2, y2);

	culcu(f, f1, x2, y1, x1);

	return 0;
}

int** make(int *x1,int *y1)
{
	int y = 0, x = 0;
	
	printf("행 열 입력:");
	scanf_s("%d %d", &y,&x);

	*x1 = x;
	*y1 = y;

	int **f = (int**)malloc(sizeof(int*)*y);
	for (int i = 0; i < y; i++)
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


void culcu(int **f, int **f1, int x2, int y1,int m)
{
	int tmp = 0,yg = 0,xg = 0;
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

	display(p, x2, y1);
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
