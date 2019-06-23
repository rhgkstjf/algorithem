#include<iostream>  
#include<string.h>	
#include<time.h> //랜덤하게 숫자를 뽑는것을 시간마다 다르게하기위해 헤더파일포함

using namespace std; // 표준 라이브러리 들은 표준 네임스페이스안에존재하므로 매번std::cout 범위지정자를 사용하기 번거롭고
					 //다른 클래스의 같은 이름의 함수 충돌을 방지하기위해 using namespace 사용

#define MAX 3	//tic - tac -tok 게임은 3x3 행렬이므로 정의해줩니다
#define VIC 99
#define LOSE 100

void put_xo(char xo[][MAX]);	//보드판을 출력하기위한 함수입니다

void input_index(int& g_x_index, int& g_y_index);
//사용자가 입력하면 인덱스값을 참조하여 값을 바꿔줍니다.

int rule_game(char xo[][MAX]);
//게임의 승패를 판단해주는 함수입니다. 반환값으로 위에서정의한 VIC LOSE 그리고 0이있습니다.

void init_xo(char xo[][MAX]);  //게임이 한번 끝나면 보드를 초기화시켜줍니다.

void ai_version();//컴퓨터와의 대결입니다.
void guess_vs_guess_version();//인공지능과의 대결입니다

char ai_upgrade_game(char xo[][MAX]);

int main()
{
	int sort = 0;
	cout << "1.인공지능과 대결  2.유저들간의 대결:";
	cin >> sort;
	if (sort == 1)
		ai_version();
	else if(sort == 2)
		guess_vs_guess_version();
	else
		cout << "다시 실행시켜주세요\n";

	return 0;
}

void guess_vs_guess_version()
{
	int trun_division = 0;
	int start = 0;
	double average = 0.0, user_1 = 0.0, user_2 = 0.0;
	int total = 0;
	int chance = 9;
	char xo[3][3] = { '\0' };
	srand((unsigned)time(NULL));

	while (1)
	{
		cout << "사용자간의 게임입니다 시작하시겠습니까 (종료 1, 시작:아무숫자) (user1 = 'x' user2 = 'o')\n";
		if (total == 0)
			cout << "아직 게임을 한판도하지않으셔서 확률을 알려드릴수없습니다.\n";
		else
			cout << "user1 이길확률:" << (user_1 / total)*100.0 << "  user2 이길확률:" << (user_2 / total)*100.0 <<endl;

		cout << "(1.종료) 아무숫자입력해주세요:";
		cin >> start;
		if (start == 1)
			break;
		total++;

		cout << "게임시작" << endl;

		while (1)
		{
			int user1_x_index = 0, user1_y_index = 0;
			int user2_x_index = 0, user2_y_index = 0;
			if (trun_division == 0)							//user1 의턴은 trun_division의값이 0일경우입니다.
			{
				input_index(user1_x_index, user1_y_index);	//이제 사용자가 입력을하면 user1_x_index,user1_y_index를 함수에서 참조하여 변경시켜줍니다.
				if (xo[user1_y_index][user1_x_index] != '\0')//솔직히 사용자가 보드보면서 입력하는데 혹시라도 잘못입력할수도있지않을가해서 만들었습니다.
				{
					while (xo[user1_y_index][user1_x_index] != '\0')
					{
						cout << "저기요. 이미 상대가 둿거나 당신이 둔곳입니다.\n";
						input_index(user1_x_index, user1_y_index);
					}
				}
				xo[user1_y_index][user1_x_index] = 'o';
				put_xo(xo);
				if (rule_game(xo) == VIC)			
				{
					cout << "user1 승리!\n";		
					user_1 += 1.0;
					chance = 9;						//언제나 게임이끝나면 기회를 초기화해줘야합니다.
					break;
				}	
				trun_division++;					//턴이 끝나면 다른사람의 턴으로바꾸기위해 하나를 더해줍니다.
			}
			else if (trun_division == 1)			//user2 는 trun_division의 값이 1일때 턴입니다.
			{
				input_index(user2_x_index, user2_y_index);	
				if (xo[user2_y_index][user2_x_index] != '\0')
				{
					while (xo[user2_y_index][user2_x_index] != '\0')
					{
						cout << "저기요. 이미 상대가 둿거나 당신이 둔곳입니다.\n";
						input_index(user2_x_index, user2_y_index);
					}
				}
				xo[user2_y_index][user2_x_index] = 'x';
				put_xo(xo);
				
				if (rule_game(xo) == VIC)			
				{
					cout << "user2 승리!\n";		
					user_2 += 1.0;
					chance = 9;						//언제나 게임이끝나면 기회를 초기화해줘야합니다.
					break;
				}
				trun_division--;					//역시나 턴을 마치고 다시 0으로 복구해줘야 다음사람의턴이됩니다.
			}
		}
	}
}

void ai_version()
{
	int start = 0;													//사용자에게 게임을 시작할때 물어본후 판단하기위한 입니다.
	double average = 0.0, cava = 0.0, gava = 0.0;					//평균값에 쓰일 변수입니다.
	int total = 0;
	int chance = 9;
	char xo[3][3] = { '\0' };	//보드입니다 모든값을 널값으로 초기화시켜줍니다.
	srand((unsigned)time(NULL));//시간마다 컴퓨터가 가질값을 변경하기위해 사용해줍니다.

	while (1)
		//do while문을 쓰면 처음시작때 종료 할 수 없으므로 그냥 while문 써줫습니다.
	{
		cout << "게임을 시작하시겠습니까 (종료:1 , 시작:anything number) (사용자가 이길 확률:" << average << "%):";
		cin >> start;
		if (start == 1)			//만약 사용자가 1을 입력시 바로 종료시켜줍니다.
			break;
		total++;				//종료를 안했으므로 게임시작 횟수 하나 늘립니다.
		while (1)				//이제 게임이 시작됩니다.
		{
			int g_x_index = 0, g_y_index = 0;					//사용자의 인덱스값과
			int c_x_index = 1, c_y_index = 1; //컴퓨터의 인덱스값입니다.


			cout << "게임 시작 (사용자:o  컴퓨터:x)\n";
			if (chance == 0)
			{
				cout << "죄송하지만 무승부입니다. 판이 모두 꽉찻습니다.\n";
				chance = 9;						//언제나 게임이끝나면 기회를 초기화해줘야합니다.
				break;
			}
			input_index(g_x_index, g_y_index);	//이제 사용자가 입력을하면 g_x_index,g_y_index를 함수에서 참조하여 변경시켜줍니다.
			if (xo[g_y_index][g_x_index] != '\0')//솔직히 사용자가 보드보면서 입력하는데 혹시라도 잘못입력할수도있지않을가해서 만들었습니다.
			{
				while (xo[g_y_index][g_x_index] != '\0')
				{
					cout << "저기요. 보드판보면서 두는데 똑같은데에다 다시두시게요?";
					input_index(g_x_index, g_y_index);
				}
			}

			xo[g_y_index][g_x_index] = 'o';		//이제 중복된게 아니므로 그 위치에 'o'를 삽입해줍니다
			chance--;							//한번 둔것이므로 찬스를 하나 차감합니다.
			put_xo(xo);							//그리고 출력한번 해줍니다.

			if (rule_game(xo) == VIC)			//이제 게임중에 사용자가 입력하면 사용자가이겼는지 확인해줘야합니다.
			{
				cout << "사용자 승리!\n";		//평균값 구하기위해 사용자가이길시 사용자의 이긴횟수 하나늘립니다.
				gava += 1.0;
				chance = 9;						//언제나 게임이끝나면 기회를 초기화해줘야합니다.
				break;
			}

			while (xo[c_y_index][c_x_index] != '\0') //이제 컴퓨터차레입니다 게임시작시 컴퓨터가가진 위치는 랜덤값이지만
			{										 //중간중간에는 이미 채워진 곳일수있으므로 채워지지않은곳을 찾을때까지 랜덤숫자넣어줍니다.
				if (xo[1][1] == '\0')
				{
					c_y_index = 1;
					c_x_index = 1;
				}
				else if (ai_upgrade_game(xo) == 'g')
				{
					int gg = 0, location = 0, temp = 0;

					for (int p = 0; p < 3; p++)
					{
						for (int t = 0; t < 3; t++)
						{
							if (xo[p][t] == 'x')
								gg += 1;
						}
						if (gg == 2)
						{
							location = p;
							break;
						}
						gg = 0;
					}
					while (xo[location][temp] == '\0')
					{
						temp++;
					}

					if(temp == 3)
					{
						c_y_index = rand() % 3;
						c_x_index = rand() % 3;
					}
					else
						xo[location][temp] = 'x';
				}
				else if (ai_upgrade_game(xo) == '|')
				{
					int gg = 0, location = 0, temp = 0;

					for (int p = 0; p < 3; p++)
					{
						for (int t = 0; t < 3; t++)
						{
							if (xo[t][p] == 'x')
								gg += 1;
						}
						if (gg == 2)
						{
							location = p;
							break;
						}
						gg = 0;
					}
					while (xo[temp][location] == '\0')
					{
						temp++;
					}

					if (temp == 3)
						{
							c_y_index = rand() % 3;
							c_x_index = rand() % 3;
						}
					else
						xo[location][temp] = 'x';
				}
				else if (ai_upgrade_game(xo) == 'L')
				{
					if (xo[0][0] == '\0')
					{
						c_x_index = 0;
						c_y_index = 0;
					}
					else if (xo[1][1] == '\0')
					{
						c_x_index = 1;
						c_y_index = 1;
					}
					else if (xo[2][2] == '\0')
					{
						c_x_index = 2;
						c_y_index = 2;
					}
					else
					{
						c_y_index = rand() % 3;
						c_x_index = rand() % 3;
					}
				}
				else if (ai_upgrade_game(xo) == '/')
				{
					if (xo[2][2] == '\0')
					{
						c_x_index = 2;
						c_y_index = 2;
					}
					else if (xo[1][1] == '\0')
					{
						c_x_index = 1;
						c_y_index = 1;
					}
					else if (xo[0][2] == '\0')
					{
						c_x_index = 2;
						c_y_index = 0;
					}
					else
					{
						c_y_index = rand() % 3;
						c_x_index = rand() % 3;
					}
				}
				else
				{
					c_y_index = rand() % 3;
					c_x_index = rand() % 3;
				}
			}
			xo[c_y_index][c_x_index] = 'x';
			chance--;								 //마찬가지로 컴퓨터도 한번 둔것이므로 찬스하나 차감합니다.
			put_xo(xo);								 //컴퓨터도 넣었으니 확인을 시켜줘야합니다.
			if (rule_game(xo) == LOSE)				 //컴퓨터가 놓고 빙고가되버리면 패배한것이므로 컴퓨터승리입니다.
			{
				cout << "컴퓨터 승리!\n";
				cava += 1.0;
				chance = 9;						//언제나 게임이끝나면 기회를 초기화해줘야합니다.
				break;
			}
		}
		init_xo(xo);								 //이제는 보드를 초기화시켜주고 게임할지말지 물어봐줍니다.
		average = (gava / total) * 100;				 //확률상 깨끗하게 보여주기위해 100곱해줍니다
	}
}


void input_index(int& g_x_index, int& g_y_index)	//c++에서 배워본 별명 한번 써봣습니다. 편한것같습니다.
{
	cout << "놓을 위치의 번호를 써주세요:";
	cin >> g_y_index >> g_x_index;
}

void put_xo(char xo[][MAX])							//출력함수입니다.
{

	for (int i = 0; i < MAX; i++)					//반복문에서 3x3이므로 MAX까지 중첩반복하여 인덱스를 다 출력해줍니다.
	{
		cout << "--|--|--\n";
		for (int k = 0; k < MAX; k++)
		{
			cout << ' ' << xo[i][k] << ' ';
		}
		cout << endl;
	}
	cout << "------------------------\n";			//보기편하게 일직선 문자열 추가해줫습니다.
}


int rule_game(char xo[][MAX])						//게임의 승패를 알려주는 함수입니다.
{
	int value_g = 0, value_c = 0;					//컴퓨터랑 사용자가 이겼을때를 구분하기위해 변수 2개 만들어줍니다.
	for (int i = 0; i < 3; i++)						//이 반복문은 가로의 x o 를 확인해줍니다. 
	{												//일직선상에 똑같은 문자가 3개 잇으면 그 문자에따라 승패를 알려줍니다.
		for (int k = 0; k < MAX; k++)
		{
			if (xo[i][k] == 'x')
				value_c += 1;
			else if (xo[i][k] == 'o')
				value_g += 1;
		}
		if (value_c == 3)
			return LOSE;
		else if (value_g == 3)
			return VIC;
		value_g = 0;								//조사가 끝나면 변수를 초기화시켜주는건 잊으면안됩니다.
		value_c = 0;
	}

	for (int i = 0; i < 3; i++)						//이 반복문또한 가로의 조건을 확인해줍니다.
	{
		for (int k = 0; k < 3; k++)
		{
			if (xo[k][i] == 'x')
				//다른점은 반복문의 형태는 같지만 xo의 인덱스가 서로 바껴있다는것이 다릅니다.
				value_c += 1;						//원래 [i][k] -> [k][i] 세로형태를 찾고자하므로 다릅니다. 열이 기준이 됩니다
			else if (xo[k][i] == 'o')
				value_g += 1;
		}
		if (value_c == 3)
			return LOSE;
		else if (value_g == 3)
			return VIC;
		value_g = 0;
		value_c = 0;
	}
	if (xo[0][0] == 'x' && xo[1][1] == 'x' && xo[2][2] == 'x')
		//남은 대각선은 조건문을 써서하는게 편할거같았습니다. 대각선의 충족조건 2가지
		return LOSE;												//2명의 플레이어이므로 4가지의 조건문만있으면됩니다.
	else if (xo[2][0] == 'x' && xo[1][1] == 'x' && xo[0][2] == 'x')
		return LOSE;
	else if (xo[2][0] == 'o' && xo[1][1] == 'o' && xo[0][2] == 'o')
		return VIC;
	else if (xo[0][0] == 'o' && xo[1][1] == 'o' && xo[2][2] == 'o')
		return VIC;

	return 0;														//defalut 반환값은 0입니다.
}


char ai_upgrade_game(char xo[][MAX])		//인공지능을 업그레이드해주는 함수입니다.
{
	int  value_c = 0, temp = 2;
	for (int i = 0; i < 3; i++)						
	{												
		for (int k = 0; k < MAX; k++)
		{
			if (xo[i][k] == 'x')
				value_c += 1;

			if (value_c == 2)
				return 'g';
		}
									
		value_c = 0;
	}

	for (int i = 0; i < 3; i++)						
	{
		for (int k = 0; k < 3; k++)
		{
			if (xo[k][i] == 'x')
				value_c += 1;						

			if (value_c == 2)
				return '|';
		}
		value_c = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		if (xo[i][i] == 'x')
			value_c += 1;
		if (value_c == 2)
			return 'L';
	}
	value_c = 0;
	for (int i = 2; i >= 0; i--)
	{
		if (xo[i][temp] == 'x')
			value_c += 1;
		if (value_c == 2)
			return '/';
		temp--;
	}

	return 'q';														
}



void init_xo(char xo[][MAX])	//2차원 배열 문자를 모두 '\0'로 초기화해줍니다
{
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < MAX; k++)
		{
			xo[i][k] = '\0';
		}
	}
}
