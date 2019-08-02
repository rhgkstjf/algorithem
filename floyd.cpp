#include<iostream>
#include<string>
using namespace std;
#define INF 999
#define MAX 49
#define MAX_STATION MAX+1

//http://blog.naver.com/PostView.nhn?blogId=overroad89&logNo=90134529557&categoryNo=17&parentCategoryNo=-1&viewDate=&currentPage=&postListTopCurrentPage=&isAfterWrite=true
//링크 사진참조
//역들을 행렬로 표현하기위해 enum사용
enum Station{
	인천공항,행신,서울,용산,영등포,광명,수원,수서,동탄,지제,평택,천안아산,천안,오송
,공주,서대전,논산,익산,신태인,정읍,광주송정,목포,전주,남원,순천,여수EXPO,대전
,김천구미,대구,동대구,밀양,구포,신경주,울산,부산,온양온천,신창,신례원,홍성,대천,군산,청량리,퇴계원,마석,청평,가평,강촌,남춘천,춘천,};

//enum에 맞쳐 enum+1번째에 해당 역의 이름을 가진 string 전역변수 선언
string name_station[MAX_STATION] = {"   ","인천공항","행신","서울","용산","영등포","광명","수원","수서","동탄","지제","평택","천안아산","천안","오송"
,"공주","서대전","논산","익산","신태인","정읍","광주송정","목포","전주","남원","순천","여수EXPO","대전"
,"김천구미","대구","동대구","밀양","구포","신경주","울산","부산","온양온천","신창","신례원","홍성","대천","군산"
,"청량리","퇴계원","마석","청평","가평","강촌","남춘천","춘천",};

//그래프가 가질 노드 가중치와 기차종류
typedef struct {
	string trainname;
	int weight;
}node;
typedef node* nodeptr;

//노드의 초기화와 가중치 삽입 함수 클래스보다 위에선언되있어야 클래스내에서 사용가능
nodeptr init_node(string name, int n);
void insert_weight(nodeptr graph[][MAX], Station start, Station destination, int weight,string name);

//train 열차종류,열차의 노선에따른 가중치 그래프가짐
class train {
public:
	node* graph[MAX][MAX];
	string trace_line;
	train(string train_name) {
		this->trace_line = train_name;
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{

				if (i == j)
					graph[i][j] = init_node("station", 0);
				else
					graph[i][j] = init_node(train_name, INF);
			}
		}
	}
	//소멸자 또한 new를통한 객체 할당한만큼 해제 역순으로
	~train() {
		for (int i = MAX-1; i < 0; i--) {
			for (int j = MAX-1; j < 0; j--)
			{
				delete graph[i][j];
			}
			delete[] (graph+i);
		}
	}
	void weight_print() {
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				cout << graph[i][j]->weight << "  ";
			}
			cout << endl;
		}
	}
};


//train public 상속받은 ktx 생성자 호출시 매개변수있는 부모생성자 호출
class ktx : public train {
public:
	//자신의 그래프에 가중치 (nodeptr)로삽입
	ktx(string train_name) :train(train_name) {
		insert_weight(graph, 인천공항, 서울, 53, this->trace_line);
		insert_weight(graph, 행신, 서울, 14,this->trace_line);
		insert_weight(graph, 서울, 용산, 6,this->trace_line);
		insert_weight(graph, 용산, 광명, 11, this->trace_line);
		insert_weight(graph, 광명, 천안아산, 14, this->trace_line);
		insert_weight(graph, 천안아산, 오송, 13, this->trace_line);
		insert_weight(graph, 오송, 공주, 10, this->trace_line);
		insert_weight(graph, 오송, 서대전, 22, this->trace_line);
		insert_weight(graph, 오송, 대전, 12, this->trace_line);
		insert_weight(graph, 공주, 익산, 9, this->trace_line);
		insert_weight(graph, 서대전, 논산, 7, this->trace_line);
		insert_weight(graph, 논산, 익산, 7, this->trace_line);
		insert_weight(graph, 익산, 전주, 13, this->trace_line);
		insert_weight(graph, 전주, 남원, 18, this->trace_line);
		insert_weight(graph, 남원, 순천, 20, this->trace_line);
		insert_weight(graph, 순천, 여수EXPO, 25, this->trace_line);
		insert_weight(graph, 대전, 김천구미, 14, this->trace_line);
		insert_weight(graph, 김천구미, 동대구, 20, this->trace_line);
		insert_weight(graph, 동대구, 밀양, 15, this->trace_line);
		insert_weight(graph, 밀양, 구포, 10, this->trace_line);
		insert_weight(graph, 구포, 부산, 20, this->trace_line);
	}

	~ktx() {}
};
//위와동일
class srt : public train {
public:
	srt(string train_name) :train(train_name) {
		insert_weight(graph, 수서, 동탄, 11, this->trace_line);
		insert_weight(graph, 동탄, 지제, 7, this->trace_line);
		insert_weight(graph, 지제, 천안아산, 12, this->trace_line);
		insert_weight(graph, 천안아산, 오송, 13, this->trace_line);
		insert_weight(graph, 오송, 공주, 10, this->trace_line);
		insert_weight(graph, 오송, 서대전, 22, this->trace_line);
		insert_weight(graph, 오송, 대전, 12, this->trace_line);
		insert_weight(graph, 공주, 익산, 9, this->trace_line);
		insert_weight(graph, 서대전, 익산, 6, this->trace_line);
		insert_weight(graph, 익산, 정읍, 15, this->trace_line);
		insert_weight(graph, 익산, 전주, 13, this->trace_line);
		insert_weight(graph, 정읍, 광주송정, 30, this->trace_line);
		insert_weight(graph, 광주송정, 목포, 34, this->trace_line);
		insert_weight(graph, 대전, 김천구미, 14, this->trace_line);
		insert_weight(graph, 김천구미, 동대구, 16, this->trace_line);
		insert_weight(graph, 동대구, 신경주, 7, this->trace_line);
		insert_weight(graph, 신경주, 울산, 7, this->trace_line);
		insert_weight(graph, 울산, 부산, 15, this->trace_line);
	}

	~srt() {}
};
//위와동일
class Rose : public train {
public:
	Rose(string train_name) :train(train_name) {
		insert_weight(graph, 서울, 용산, 10, this->trace_line);
		insert_weight(graph, 용산, 영등포, 15, this->trace_line);
		insert_weight(graph, 영등포, 수원, 44, this->trace_line);
		insert_weight(graph, 수원, 평택, 32, this->trace_line);
		insert_weight(graph, 평택, 천안아산, 32, this->trace_line);
		insert_weight(graph, 천안아산, 천안, 10, this->trace_line);
		insert_weight(graph, 천안, 서대전, 55, this->trace_line);
		insert_weight(graph, 천안,대전,50, this->trace_line);
		insert_weight(graph, 서대전, 논산, 45, this->trace_line);
		insert_weight(graph, 논산, 익산,49, this->trace_line);
		insert_weight(graph, 익산, 신태인, 32, this->trace_line);
		insert_weight(graph,신태인, 정읍, 46, this->trace_line);
		insert_weight(graph, 정읍, 광주송정, 32, this->trace_line);
		insert_weight(graph, 광주송정, 목포, 49, this->trace_line);
		insert_weight(graph, 대전, 김천구미, 35, this->trace_line);
		insert_weight(graph, 김천구미, 대구, 32, this->trace_line);
		insert_weight(graph, 대구, 동대구, 20, this->trace_line);
		insert_weight(graph, 동대구, 밀양, 40, this->trace_line);
		insert_weight(graph, 밀양, 구포, 43, this->trace_line);
		insert_weight(graph, 구포, 부산, 51,this->trace_line);
	}

	~Rose() {}
};

class Nuri :public train {
public:
	Nuri(string train_name) :train(train_name) {
		insert_weight(graph, 천안아산, 온양온천, 15, this->trace_line);
		insert_weight(graph, 온양온천, 신창, 5, this->trace_line);
		insert_weight(graph, 신창, 신례원, 20, this->trace_line);
		insert_weight(graph, 신례원, 홍성, 19, this->trace_line);
		insert_weight(graph, 홍성, 대천, 24, this->trace_line);
		insert_weight(graph, 대천, 군산, 39, this->trace_line);
		insert_weight(graph, 군산, 익산, 33, this->trace_line);
	}
	~Nuri(){}
};

class ITX :public train {
public:
	ITX(string train_name) :train(train_name) {
		insert_weight(graph, 서울, 청량리, 7, this->trace_line);
		insert_weight(graph, 청량리, 퇴계원, 15, this->trace_line);
		insert_weight(graph, 퇴계원, 마석, 15, this->trace_line);
		insert_weight(graph, 마석, 청평, 15, this->trace_line);
		insert_weight(graph, 청평, 가평, 15, this->trace_line);
		insert_weight(graph, 가평, 강촌, 15, this->trace_line);
		insert_weight(graph, 강촌, 남춘천, 15, this->trace_line);
		insert_weight(graph, 남춘천, 춘천, 15, this->trace_line);
	}
	~ITX() {}
};


//3 기차의 그래프를 가장 가중치가 적은 그래프로 변환
template<class k,class s,class r,class n,class x>
void weight_change_min(k& k, s& s, r& r,n& n,x& x ,nodeptr g[][MAX]);


// 모든 정점에서의 최단경로를 알아내기위해  floyd알고리즘사용
void floyd(nodeptr g[][MAX],int path[][MAX], string transfer[][MAX]);
//인덱스번호를찾음 enum과  name_station통해 그 해당역의 인덱스 반환
int find_string_to_enum(string station_n);
//출발부터 도착까지 경로를 변경한 노선을 전부 저장함. 그리고 재귀를통해 경로를 출력
void print_path(int path[][MAX],int start, int destination,string transfer[][MAX], int& transfer_price);
//경로 배열을 초기화함
void init_path(int path[][MAX]);
//출선시작때 타는 기차 종류 출력
string start_point_train(nodeptr g[][MAX], int start);
//모든 역의 정보 출력
void Station_name_print();

int main()
{
	char start_end = '\0';
	string start_point;
	string destination_point;
	nodeptr weight_graph[MAX][MAX] = { NULL };
	int path[MAX][MAX];
	string train_transrate[MAX][MAX] = { "" };

	//열차들의 객체 생성
	ktx k("ktx");
	srt s("srt");
	Rose r("Rose");
	Nuri n("Nuriro");
	ITX x("ITX");

	//열차들의 가중치 최소값 업데이트 경로 배열 초기화
	weight_change_min(k, s, r, n,x, weight_graph);
	init_path(path);
	//최단경로 탐색 시작
	floyd(weight_graph, path, train_transrate);
	//일단 한번은 시작함

	do {
		int transfer_price = 0;
		cout << "================================기차 노선 정보 제공================================"<<endl;
		cout << "정보 탐색 가능 STATION 나열--------------------------------------------------------" << endl;
		Station_name_print();
		cout << "-----------------------------------------------------------------------------------"<<endl<<endl<<endl;
		cout << "출발역 입력하세요:";
		cin >> start_point;
		cout << "도착역 입력하세요:";
		cin >> destination_point;

		//출발역과 도착역의 역이름을 알기위해 인덱스 번호 -1 반환
		int ss = find_string_to_enum(start_point) - 1;
		int dd = find_string_to_enum(destination_point) - 1;

		cout << "경로 정보 가져옵니다\n";
		cout << "-----------------------------------------------------------------------------------\n";

		//최단경로 탐색중에 얻은 결과 모두 출력
		cout << "가는 경로" << endl;
		cout << "출발:" << name_station[ss + 1] <<'('<<start_point_train(weight_graph,ss)<<')'<< "->";
		print_path(path, ss, dd, train_transrate,transfer_price);
		cout << name_station[dd + 1] << "도착" << endl;
		cout << "총 소요시간:" << weight_graph[ss][dd]->weight * 2 << "분 소요됩니다\n" << endl;
		cout<<"거리가격:"<<weight_graph[ss][dd]->weight*2*100<<"원"<<"환승비:"<<transfer_price<<"원"<<endl;
		cout << "계속 하시겠습니까?:( q:종료  c:계속)";
		cin >> start_end;
		cout << endl << endl;
	} while (start_end != 'q');//q입력하면 종료
	
	
	return 0;
}

//노드 새로할당하여 노드 초기화후 반환
nodeptr init_node(string name, int n) {
	nodeptr k = (nodeptr)new node;
	if (k == NULL) {
		cout << "할당오류";
		return NULL;
	}
	else {
		k->trainname = name;
		k->weight = n;
		return k;
	}
}

//시작점 출발점 가중치 그래프받아와서 간선 삽입 (무방향그래프) 간선2배
void insert_weight(nodeptr graph[][MAX],Station start, Station destination,int weight,string name) {
	nodeptr tmp = (nodeptr)new node;
	tmp->weight = weight;
	tmp->trainname = name;
	graph[start][destination] = tmp;
	graph[destination][start] = tmp;
}

//객체들을 참조변수로 받아 복사생성자 호출 안하게함
//3개의 그래프를 가중치가 가장 적은것으로 바꿔줌
//3개다 999이면 경로가 존재하지않음. 다만 이그래프에선 경로존재하지않는곳이 존재하지않음 무궁화호와 누리로를 거치면 모두갈수있게해놓음
template<class k,class s,class r,class n,class x>
void weight_change_min(k& k, s& s, r& r,n& n,x& x,nodeptr g[][MAX]) {
	nodeptr tmp = NULL;
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			tmp = k.graph[i][j];
			//모든 가중치가 INF면 경로가 존재하지않는곳 
			if (k.graph[i][j]->weight == INF && s.graph[i][j]->weight == INF && r.graph[i][j]->weight == INF
				&& n.graph[i][j]->weight == INF && x.graph[i][j]->weight == INF)
			{
				tmp->trainname = "경로가없음";
			}
			//하나씩 비교하면서 가장 작은가중치를 찾아 노드를 반환
			else {
				if (tmp->weight > s.graph[i][j]->weight)
					tmp = s.graph[i][j];

				if (tmp->weight > r.graph[i][j]->weight)
					tmp = r.graph[i][j];
				
				if (tmp->weight > n.graph[i][j]->weight)
					tmp = n.graph[i][j];
				if (tmp->weight > x.graph[i][j]->weight)
					tmp = x.graph[i][j];
			}
			g[i][j] = tmp;
		}
	}
}

//최단경로 탐색중 경로 우회시 우회하는 경로의 열차 , 경로의 인덱스변호 저장 가중치 업데이트
void floyd(nodeptr g[][MAX],int path[][MAX],string transfer[][MAX])
{
	int number = 0;
	for (int k = 0; k < MAX; k++)
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (g[i][j]->weight > g[i][k]->weight + g[k][j]->weight)
				{
					if (g[k][j]->trainname != "경로가없음") {//경로를 저장할때 반대로 올라오는 경로를 저장하기위해 조건문추가

						transfer[i][j] = g[k][j]->trainname;
					}
					else                                     //그냥g[k][j]의 열차만 저장하면 위로 올라오는 기차경로 저장이안됨
						transfer[i][j] = g[k][i]->trainname;

					path[i][j] = k;							 //경로를 우회했다는것을 저장하기위함 i->j 에서 i->k->j k를통해 우회
					g[i][j]->weight = g[i][k]->weight + g[k][j]->weight;//최단 경로를 업데이트
				}
			}
		}
	}
}
//들어온 문자열을 전역변수 name_station과 비교후 맞으면 인덱스 반환
int find_string_to_enum(string station_n) {
	for (int i = 1; i < MAX+1; i++) {
		if (station_n == name_station[i])
			return i;
	}
	return -1;
	
}

//우회를 통해 더 짧은 경로들의 집합 path,transfer통해 경로출력
void print_path(int path[][MAX],int start, int destination,string transfer[][MAX],int& transfer_price) {
	//경로의 시작점 도착점이 -1이 아니면 경로를 우회해서갔음
	if (path[start][destination] != -1) {
		//처음 시작점 i에서 우회한 지점 k로 가는 재귀호출
		print_path(path, start, path[start][destination],transfer,transfer_price);
		cout << name_station[path[start][destination] + 1];
		cout<< '(' << transfer[start][destination] << ')' << "->";
		transfer_price += 1000;
		//k에서 j로가는 경로 재귀로 호출
		print_path(path, path[start][destination], destination, transfer, transfer_price);
	}
	else
		return;
}
//경로의 인덱스 저장할 배열 초기화
void init_path(int path[][MAX]) {
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
			path[i][j] = -1;
	}
}
//출발지점에서의 열차탑승 종류 출력
string start_point_train(nodeptr g[][MAX],int start) {
	int least = 0;
	for (int i = 1; i < MAX; i++)
	{
		if (g[start][least]->weight == 0 || g[start][i]->weight == 0)
			continue;
		else
		{
			if(g[start][least]->weight > g[start][i]->weight)
				least = i;
		}
	}
	return g[start][least]->trainname;
}
//모든 역의 정보 출력
void Station_name_print() {
	cout << "수도권---";
	for (int i = 1; i <= 14; i++)
	{
		cout << name_station[i] << ' ';
	}
	cout << endl<<"전라도---";
	for (int i = 15; i <= 26;i++)
	{
		cout << name_station[i] << ' ';
	}
	cout << endl << "경상도---";
	for (int i = 27; i <= 34; i++)
	{
		cout << name_station[i] << ' ';
	}
	cout << endl << "장항선---";
	for (int i = 35; i <= 41; i++)
	{
		cout << name_station[i] << ' ';
	}
	cout << endl << "경춘선---";
	for (int i = 42; i < MAX_STATION; i++)
	{
		cout << name_station[i] << ' ';
	}
	cout << endl<<endl;
}
