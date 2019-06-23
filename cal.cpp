#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 60
typedef union {
	double data;
	char op;
}data;

typedef int element;

typedef struct {
	int top;
	char stack[MAX];
}stack;
typedef stack* stackptr;


typedef struct node node;
typedef node* nodeptr;
struct node {
	data data;
	nodeptr right;
	nodeptr left;
};

typedef struct {
	int top;
	nodeptr stack[MAX];
}nodestack;
typedef nodestack* nodestackptr;


//중위를 후위식으로 변환해주는 관련 함수
void get_exp(char a[]);
void postfix(char a[], char w[]);
int input_x(char a);

//스택 연산에 관한 함수들
void push(stackptr s, element item);
int is_empty(stack s);
int is_full(stack s);
char peek(stack s);
char pop(stackptr s);


//후위를 노드로 나눠주는 역할
nodestackptr division(nodestackptr snode, char a[]);
void init_arr(char a[]);

//스택노드 함수
nodeptr nodeptr_pop(nodestackptr node_s);
void nodeptr_push(nodestackptr node_s, nodeptr item);
//이진트리 순회 수식트리 계산 함수
void inorder_put(nodeptr T);
double eval_Tree(nodeptr T);

void puts_exp(char kxp[]);
void init_exp(char exp[]);

int main()
{
	char quit;
	double res = 0;
	char exp[MAX] = { '\0' };
	char kxp[MAX] = { '\0' };

	do {
		nodestackptr snode = (nodestackptr)malloc(sizeof(nodestack));
		nodeptr Tree = NULL;
		printf("계산기 프로그램 (종료:Q 입력) (계속:아무거나)");
		fflush(stdin);
		scanf_s("%c", &quit,sizeof(quit));
		if (quit == 'Q')
			break;
		snode->top = -1;
		get_exp(exp);

		postfix(exp, kxp);

		puts_exp(kxp);

		snode = division(snode, kxp);
		Tree = snode->stack[snode->top];

		printf("\n\n");
		inorder_put(Tree);

		res = eval_Tree(Tree);
		printf("\n%lf  \n", res);
		getchar();
		init_exp(exp);
		init_exp(kxp);
		Tree = NULL;
		snode = NULL;
		free(snode);
	} while (quit != 'Q');

	return 0;
}




void get_exp(char a[])
{
	printf("중위 식 입력하세요:");
	scanf_s("%s", a, MAX - 1);
}

int input_x(char a)
{
	switch (a)
	{
	case '+':
	case '-':return 1;

	case '*':
	case '/':return 2;

	case '(':return 3;
	}
}
int output_x(char a)
{
	switch (a)
	{
	case '(':return 0;

	case '+':
	case '-':return 1;

	case '*':
	case '/':return 2;

	}
}

void postfix(char a[], char w[])
{
	stackptr s = (stackptr)malloc(sizeof(stack));
	s->top = -1;


	int i = 0, index = 0;
	char tmp = a[i];


	while (a[i] != '\0')
	{
		if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/')
		{
			if (is_empty(*s))
			{
				w[index++] = 'x';
				push(s, a[i++]);
			}
			else
			{
				if (input_x(a[i]) >= output_x(peek(*s)))
				{
					w[index++] = 'x';
					push(s, a[i++]);
				}
				else
				{
					w[index++] = 'x';
					w[index++] = pop(s);
					push(s, a[i++]);
				}
			}
		}
		else if (a[i] == '(')
		{
			push(s, a[i]);
			i++;
		}
		else if (a[i] == ')')
		{
			char k = peek(*s);
			while (k != '(')
			{
				w[index++] = pop(s);
				k = peek(*s);
			}
			k = pop(s);
			i++;
		}
		else
		{
			w[index++] = a[i++];
		}

	}
	if (!is_empty(*s))
	{
		w[index++] = 'x';
		while (!is_empty(*s))
		{
			w[index++] = pop(s);
		}
	}
}


int is_empty(stack s)
{
	if (s.top == -1)
		return 1;
	else
		return 0;
}

int is_full(stack s)
{
	if (s.top == MAX - 1)
		return 1;
	else
		return 0;
}

char peek(stack s)
{
	if (is_empty(s))
		printf("꺼낼게 없습니다.\n");
	else
		return s.stack[s.top];
}

void push(stackptr s, element item)
{
	if (is_full(*s))
		printf("꽉차 있습니다.\n");
	else
	{
		s->top++;
		s->stack[s->top] = item;
	}
}

char pop(stackptr s)
{
	if (is_empty(*s))
		printf("아무것도 없습니다.\n");
	else
	{
		char tmp;
		tmp = s->stack[s->top];
		s->top--;
		return tmp;
	}
}




void nodeptr_push(nodestackptr node_s, nodeptr item)
{
	if (node_s->top == MAX - 1)
		printf("노드 스택이 꽉차있습니다..\n");
	else
	{
		node_s->stack[++node_s->top] = item;
	}
}

nodeptr nodeptr_pop(nodestackptr node_s)
{
	if (node_s->top == -1)
		printf("노드스택이 비어있습니다..\n");
	else
	{
		nodeptr tmp = NULL;
		tmp = node_s->stack[node_s->top--];
		return tmp;
	}
}

nodestackptr division(nodestackptr snode, char a[])
{
	int i = 0, sindex = 0;
	double value = 0;
	char save[MAX] = { '\0' };
	data gar;
	while (a[i] != '\0')
	{
		if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/')
		{
			if (sindex == 0)
			{
				nodeptr tmp = (nodeptr)malloc(sizeof(node));
				tmp->left = NULL;
				tmp->right = NULL;
				gar.op = a[i++];
				tmp->data = gar;
				nodeptr p1 = nodeptr_pop(snode);
				nodeptr p2 = nodeptr_pop(snode);
				tmp->left = p2;
				tmp->right = p1;
				nodeptr_push(snode, tmp);
			}
			else
			{
				value = atof(save);
				nodeptr tmp1 = (nodeptr)malloc(sizeof(node));
				tmp1->left = NULL;
				tmp1->right = NULL;
				gar.data = value;
				tmp1->data = gar;
				nodeptr_push(snode, tmp1);
				init_arr(save);
				sindex = 0;

				nodeptr tmp = (nodeptr)malloc(sizeof(node));
				tmp->left = NULL;
				tmp->right = NULL;
				gar.op = a[i++];
				tmp->data = gar;
				nodeptr p1 = nodeptr_pop(snode);
				nodeptr p2 = nodeptr_pop(snode);
				tmp->left = p2;
				tmp->right = p1;
				nodeptr_push(snode, tmp);

			}

		}
		else if (a[i] == 'x')
		{
			if (sindex == 0)
				i++;
			else
			{
				value = atof(save);
				nodeptr tmp = (nodeptr)malloc(sizeof(node));
				tmp->left = NULL;
				tmp->right = NULL;
				gar.data = value;
				tmp->data = gar;
				nodeptr_push(snode, tmp);
				init_arr(save);
				sindex = 0;
				i++;
			}
		}
		else if (a[i] == '.')
		{
			save[sindex++] = a[i];
			i++;
		}
		else
		{
			save[sindex++] = a[i];
			i++;
		}
	}
	return snode;
}

void init_arr(char a[])
{
	for (int i = 0; i < MAX; i++)
	{
		a[i] = '\0';
	}
}

void inorder_put(nodeptr T)
{
	if (T == NULL)
	{
	}
	else
	{
		inorder_put(T->left);
		if (T->left == NULL && T->right == NULL)
			printf("%lf  ", T->data.data);
		else
			printf("%c  ", T->data.op);
		inorder_put(T->right);
	}
}


double eval_Tree(nodeptr T)
{
	double left = 0, right = 0, value = 0;
	if (T == NULL)
		return 0;

	if (T->left == NULL && T->right == NULL)
	{
		data tmp;
		tmp.data = T->data.data;
		return tmp.data;
	}
	else
	{
		double k1 = eval_Tree(T->left);
		double k2 = eval_Tree(T->right);

		switch (T->data.op)
		{
		case'+':
			return k1 + k2;
		case '-':
			return k1 - k2;
		case '*':
			return k1 * k2;
		case '/':
			return k1 / k2;

		}
	}
	return 0;
}

void puts_exp(char kxp[])
{
	int i = 0;
	while (kxp[i] != '\0') {
		if (kxp[i] == 'x')
			i++;
		else {
			printf("%c", kxp[i]);
			i++;
		}
	}
}
void init_exp(char exp[])
{
	for (int i = 0; i < MAX; i++)
	{
		exp[i] = '\0';
	}
}
