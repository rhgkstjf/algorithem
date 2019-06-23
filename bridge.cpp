#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef struct {  //인접 그래프 구조체 정의
	int n;
	int adjMat[MAX][MAX];
}graphType;
typedef graphType* graphTypeptr;

typedef struct { //간선 저장할 구조체 정의
	int v[MAX][2];
	int amount;
}edgetype;
typedef edgetype* edgetypeptr;

int visited[MAX];  //dfs 사용위해 전역변수 선언
int count = 0;	   //연결 성분 파악위해 count 전역변수 선언

void init_Mat(graphTypeptr Mat);  //인접 행렬 그래프초기화
bool exist_edge_Mat(graphTypeptr g, int start, int end);//간선 존재여부
void insert_edge_Mat(graphTypeptr g, int start, int end);//간선 추가
void insert_vertex_Mat(graphTypeptr g);//정점 추가
void print_Mat(graphType g);//그래프 출력
void delete_edge_Mat(graphTypeptr g, int start, int end);//간선 삭제

void array_init(int a[]);//배열 초기화
void dfs(graphType g, int i);//깊이 우선 탐색 연결성분 버전
void find_connected(graphType g);//그래프 연결 성분 탐색
void find_bridge(graphType g,edgetypeptr bridge);//브릿지 간선 탐색

void print(edgetype bridge);//간선 출력

int main()
{
	graphType g;
	edgetypeptr bridge = (edgetypeptr)malloc(sizeof(edgetype));

	init_Mat(&g);
	for (int i = 0; i < 10; i++)//정점 추가
		insert_vertex_Mat(&g);

	insert_edge_Mat(&g, 0, 1);
	insert_edge_Mat(&g, 1, 2);
	insert_edge_Mat(&g, 1, 3);
	insert_edge_Mat(&g, 2, 4);
	insert_edge_Mat(&g, 3, 4);
	insert_edge_Mat(&g, 3, 5);
	insert_edge_Mat(&g, 5, 6);
	insert_edge_Mat(&g, 5, 7);
	insert_edge_Mat(&g, 6, 7);
	insert_edge_Mat(&g, 7, 8);
	insert_edge_Mat(&g, 7, 9); // 여기까지 그래프 초기화
	//insert_edge_Mat(&g, 1, 7);

	print_Mat(g);  //초기화 확인

	find_bridge(g,bridge); //브릿지 탐색 후 브릿지 간선 반환
	print(*bridge); //브릿지 간선 출력


	return 0;
}

void insert_vertex_Mat(graphTypeptr g)//행렬 그래프 정점 추가함수
{
	if (((g->n + 1)) > MAX)
		printf("정점 갯수 최대\n");

	else
		g->n++;
}

void init_Mat(graphTypeptr Mat)
{
	Mat->n = 0;
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
			Mat->adjMat[i][j] = 0;
	}

}

void insert_edge_Mat(graphTypeptr g, int start, int end)
//행렬 그래프 간선 삽입 함수
{
	if (start >= g->n || end >= g->n)
		printf("정점 번호 오류\n");
	else if (exist_edge_Mat(g, start, end) == true)
	{
		printf("이미 간선 존재\n");
	}
	else
	{
		g->adjMat[start][end] = 1;
		g->adjMat[end][start] = 1;
	}
}

bool exist_edge_Mat(graphTypeptr g, int start, int end)
{//행렬 그래프 간선 존재 여부확인 함수
	if (g->adjMat[start][end] == 1)
		return true;
	else
		return false;
}

void print_Mat(graphType g)
{//그래프 보기 좋게 출력하는 함수
	printf("인접 행렬 그래프 시각화-------------------------------------\n");
	printf("		0	1	2	3	4	5	6	7	8	9\n");
	for (int i = 0; i < g.n; i++)
	{
		printf("%d번째 정점	", i);
		for (int w = 0; w < g.n; w++)
		{
			if (g.adjMat[i][w] == 1)
				printf("%d	", 1);
			else
				printf("%d	", 0);
		}
		printf("\n");
	}
	printf("\n");
}
void array_init(int a[])
{//연결성분을 브릿지 탐색 함수에서 간선 갯수만큼 반복하기떄문에
//배열을 한번 반복후 초기화를 시켜주기위해 만듬
	for (int i = 0; i < MAX; i++)
		a[i] = 0;
}
void dfs(graphType g, int i)
{//깊이 우선 탐색 다만 방문한곳을 count로 넣음 연결성분구분위해
	visited[i] = count;
	//printf("%d정점 방문		", i);
	for (int w = 0; w < g.n; w++)
	{
		if (g.adjMat[i][w] == 1 && visited[w] == 0) //간선 존재할시 dfs호출
			dfs(g, w);
	}
	//printf("\n");
}


void find_connected(graphType g)
{//연결 성분 알기위해 탐색
	count = 0;
	for (int k = 0; k< g.n; k++)
	{
		if (visited[k] == 0)//조건문을 지나면 1이 되기떄문에
		{					//다음 반복문 수행시 dfs수행
			count++;
			dfs(g, k);
		}
	}

}

void delete_edge_Mat(graphTypeptr g, int start, int end)
{//간선 삭제함수 브릿지찾을떄 삭제를 해야함
	if (start >= g->n || end >= g->n)
		printf("정점 번호 오류\n");
	else if (exist_edge_Mat(g, start, end) == false)
	{
		printf("간선 이미 존재하지않음\n");
	}
	else
	{
		g->adjMat[start][end] = 0;
		g->adjMat[end][start] = 0;
	}
}

void find_bridge(graphType g, edgetypeptr bridge)
{
	printf("브릿지 찾는중 ---------\n");
	bridge->amount = 0;//갯수 0개 초기화
	int edge[MAX][2] = { 0 };
	int idx = 0, number = 0;
	bool judge = false; // 브릿지 확인위해 필요한 변수
	for (int i = 0; i < (g.n) - 1; i++)
	{//존재하는 간선 저장하기위한 반복문
		for (int k = i + 1; k < g.n; k++)
		{
			if (g.adjMat[i][k] == 1)
			{
				number++;
				edge[idx][0] = i;
				edge[idx++][1] = k;
			}
		}
	}

	printf("\n\n");
	for (int i = 0; i < number; i++)
	{//브릿지 찾는 반복문 시작
		count = 0;
		array_init(visited);//초기화하지않으면 브릿지찾는데 사용 의미가없음
		delete_edge_Mat(&g, edge[i][0], edge[i][1]);//간선을 삭제해봄
		find_connected(g);
		insert_edge_Mat(&g, edge[i][0], edge[i][1]);//다시 간선 추가해줌
		for (int t = 0; t < MAX; t++)
		{//visited에 1그리고0 이아닌 2가 존재한다면 그간선은 브릿지
			if (visited[t] != 0 && visited[t] != 1)
				judge = true;
		}
		if (judge == true)
		{//브릿지인경우 간선 구조체에 저장
			//printf("%d %d 간선은 브릿지\n", edge[i][0], edge[i][1]);
			bridge->v[bridge->amount][0] = edge[i][0];
			bridge->v[bridge->amount++][1] = edge[i][1];
			
			judge = false;//판단변수도 초기화
		}
		else{//아닐경우 아무것도 하지않음
			//printf("%d %d 간선은 브릿지가 아님\n", edge[i][0], edge[i][1]);
		}
	}
	//print(bridge);
}

void print(edgetype bridge)
{
	for (int i = 0; i < bridge.amount; i++)
		printf("%d %d 두정점의 간선은 브릿지\n", bridge.v[i][0], bridge.v[i][1]);
}
