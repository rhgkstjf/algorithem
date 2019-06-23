#include<stdio.h>
#include<stdlib.h>
#define MAX 50
#define MAX_V 50
#define INF 1000

typedef struct {
	int u;
	int v;
	int weight;
}edge;

typedef struct {
	edge h[MAX_V];
	int hs;
}heap;
typedef heap* heaptr;
int parent[MAX_V];
int num[MAX_V];

void init_set(int size);
void union_set(int i, int j);
//int find_set(int vertex);
int find_set(int i);
void insert_edge_all(heaptr h);

void heap_print(heaptr h);
void insert_heap_min(heaptr h, edge e);
void insert_heap(heaptr h, int u, int v, int weight);
edge delete_heap_min(heaptr h);
void kruskal(int n);

int main()
{
	/*int graph[MAX][MAX] = {
		{INF,7,INF,INF,3,10,INF},
		{7,INF,4,10,2,6,INF},
		{INF,4,INF,2,INF,INF,INF},
		{INF,10,2,INF,11,9,4},
		{3,2,INF,11,INF,INF,5},
		{10,6,INF,9,INF,INF,INF},
		{INF,INF,INF,4,5,INF,INF} };*/
	kruskal(7);

	return 0;
}
void init_set(int size)
{
	for (int i = 0; i < size; i++)
	{
		parent[i] = -1;
		num[i] = 1;
	}
}


int find_set(int i)
{
	int temp = i;
	while (parent[temp] >= 0)
		temp = parent[temp];
	
	int temp2 = temp;
	int temp3;
	while (parent[temp2] >= 0)
	{
		temp3 = parent[temp2];
		parent[temp2] = temp;
		temp2 = temp3;
	}
	return temp;
}


void insert_heap_min(heaptr h, edge e)
{
	int i = ++h->hs;
	while (i > 0 && e.weight < h->h[i / 2].weight)
	{
		h->h[i] = h->h[i / 2];
		i = i / 2;
	}
	h->h[i] = e;
}

void insert_heap(heaptr h, int u, int v, int weight)
{
	edge e;
	e.u = u;
	e.v = v;
	e.weight = weight;
	insert_heap_min(h, e);
}
edge delete_heap_min(heaptr h)
{
	edge value = h->h[1];
	edge temp = h->h[h->hs];
	int i = 1, j = 2;
	h->hs = h->hs - 1;
	while (j <= h->hs)
	{
		if (j < h->hs && h->h[j].weight > h->h[j + 1].weight)
			j++;

		if (temp.weight < h->h[j].weight) break;

		h->h[i] = h->h[j];
		i = j;
		j *= 2;
	}
	h->h[i] = temp;
	return value;
}

void insert_edge_all(heaptr h)
{
	insert_heap(h, 0, 1, 7);
	insert_heap(h, 0, 4, 3);
	insert_heap(h, 0, 5, 10);
	insert_heap(h, 1, 2, 4);
	insert_heap(h, 1, 4, 2);
	insert_heap(h, 1, 5, 6);
	insert_heap(h, 1, 3, 10);
	insert_heap(h, 2, 3, 2);
	insert_heap(h, 3, 4, 11);
	insert_heap(h, 3, 6, 4);
	insert_heap(h, 3, 5, 9);
	insert_heap(h, 4, 6, 5);
}
/*
int find_set(int vertex) {
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p);
	s = i;
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;
	return s;
}
*/
void kruskal(int n)
{
	int edge_num = 0;
	heaptr h = (heaptr)malloc(sizeof(heap));
	h->hs = 0;
	int uset, vset;
	edge e;
	insert_edge_all(h);
	init_set(n);

	while (edge_num < (n - 1))
	{
		e = delete_heap_min(h);
		uset = find_set(e.u);
		vset = find_set(e.v);
		if (uset != vset)
		{
			printf("(%d.%d)간선 가중치:%d 연결합니다!!\n", e.u, e.v, e.weight);
			edge_num++;
			union_set(uset,vset);
		}
	}
	free(h);
}

void heap_print(heaptr h)
{
	int i = 1;
	while (i <= h->hs)
	{
		printf("(%d %d) weight:%d\n", h->h[i].u, h->h[i].v, h->h[i].weight);
		i++;
	}
}

void union_set(int s1, int s2) {
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}
