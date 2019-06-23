#define _CRT_SECURE_NO_WARNINGS_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 20

void init(char *a)
{
	for (int i = 0; i < MAX; i++) {
		*(a + i) = '\0';
	}
}

void print_arr(char *a)
{
	int i = 0;
	while (*(a+i) != '\0')
	{
		printf("%c", *(a + i));
		i++;
	}
}
int main()
{
	char  **name = NULL;
	int **hangle = NULL;
	int **eng = NULL;
	int **math = NULL;
	double **ava = NULL;

	int n = 0;
	printf("학생수는?");
	scanf_s("%d", &n);
	getchar();


	name = (char**)malloc(sizeof(char*)*n);
	hangle = (int**)malloc(sizeof(int*)*n);
	eng = (int**)malloc(sizeof(int*)*n);
	math = (int**)malloc(sizeof(int*)*n);
	ava = (double**)malloc(sizeof(double*)*n);

	for (int i = 0; i < n; i++)
	{
		*(name + i) = (char*)malloc(sizeof(char)*MAX);
		*(hangle + i) = (int*)malloc(sizeof(int) * 1);
		*(eng + i) = (int*)malloc(sizeof(int) * 1);
		*(math + i) = (int*)malloc(sizeof(int) * 1);
		*(ava + i) = (double*)malloc(sizeof(double) * 1);

		init(*(name + i));

		printf("학생 이름:");
		gets_s(*(name + i), MAX - 1);
		fflush(stdin);


		printf("국어 점수:");
		scanf_s("%d", *(hangle + i));
		getchar();

		printf("영어 점수:");
		scanf_s("%d", *(eng + i));
		getchar();
	
		printf("수학 점수:");
		scanf_s("%d", *(math + i));
		getchar();

		*(*(ava + i) + 0) = ((double)(*(*(hangle + i) + 0)) +(double)(*(*(eng + i) + 0))+ (double)(*(*(math + i) + 0))) / 3.0;

	}
	
	printf("\n학생성명	국어  수학  영어  평균\n");

	for (int i = 0; i < n; i++)
	{

		print_arr(*(name + i));

		printf("		%d    %d    %d    %.2lf \n\n", *(*(hangle + i) + 0),*(*(eng + i) + 0), *(*(math + i) + 0), *(*(ava + i) + 0));
	}

	for (int i = n - 1; i == 0; i--)
	{
		free(*(name + i));
		free(*(hangle+ i));
		free(*(eng + i));
		free(*(math + i));
		free(*(ava + i));
	}

	return 0;
}
