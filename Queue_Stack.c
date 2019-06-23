#include<stdio.h>
#include<stdlib.h>

#define MAX 20
typedef int element;
typedef struct {
	int stack[MAX];
	int top;
}stack;
typedef stack* stackPtr;

typedef struct {
	stackPtr f;
	stackPtr r;
}Queue;
typedef Queue* QueuePtr;

int is_empty(stackPtr s);
int is_full(stackPtr s);
void push(stackPtr s, element item);
element pop(stackPtr s);
element peek(stack s);

QueuePtr init();
void enqueue(QueuePtr q, element item);
element dequeue(QueuePtr q);

void Func(QueuePtr q,int n);

int main()
{
	QueuePtr q;
	int tmp = 0,n;
	q = init();
	enqueue(q, 0);
	enqueue(q, 1);
	printf("피보나치 수열 몇번째 까지 수하실건가요?");
	scanf_s("%d", &n);
	Func(q, n-2);
free(q->f);
	free(q->r);
	free(q);
	return 0;
}


void Func(QueuePtr q,int n)
{
	int value = 0;
	printf("%d 번째 까지의 피보나치 수열 \n\n", n + 2);
	printf("%d   %d   ", q->f->stack[q->f->top-1], q->f->stack[(q->f->top)]);
	for (int i = 1; i <= n; i++)
	{
		value = dequeue(q);
		value = value + peek(*(q->f));
		printf("%d   ", value);
		push(q->f, value);
	}
	printf("\n");
}
element peek(stack s)
{
	return s.stack[s.top];
}

int is_empty(stackPtr s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}
int is_full(stackPtr s)
{
	if (s->top == MAX - 1)
		return 1;
	else
		return 0;
}

void push(stackPtr s, element item)
{
	if (is_full(s))
		printf("넣을수없음\n");
	else
	{
		s->top += 1;
		s->stack[s->top] = item;
	}
}

element pop(stackPtr s)
{
	if (is_empty(s))
		printf("비어있어서 꺼낼게없습니다.\n");
	else
	{
		int tmp = 0;
		tmp = s->stack[s->top];
		s->top -= 1;
		return tmp;
	}
}



QueuePtr init()
{
	QueuePtr q = (Queue*)malloc(sizeof(Queue));
	q->f = (stack*)malloc(sizeof(stack));
	q->f->top = -1;
	q->r = (stack*)malloc(sizeof(stack));
	q->r->top = -1;

	return q;
}

void enqueue(QueuePtr q, element item)
{
	if (q == NULL)
		printf("넣을수가없음\n");
	else
		push(q->f, item);
}
element dequeue(QueuePtr q)
{
	if (is_empty(q->f))
	{
		printf("비어있습니다.\n");
	}
	else
	{
		element tmp = 0,num=0;
		while (q->f->top != -1)
		{
			tmp = pop(q->f);
			push(q->r, tmp);
		}
		tmp = pop(q->r);
		while (q->r->top != -1)
		{
			num = pop(q->r);
			push(q->f, num);
		}
		return tmp;
	}
}
