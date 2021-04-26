#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    vector<int> s;
    
    for (int p : moves)
    {
        for (int i = 0; i <board[0].size(); i++)
        {
            if (board[i][p - 1] != 0)
            {
                if (s.size() == 0)
                    s.push_back(board[i][p - 1]);
                else if (board[i][p - 1] == s.back())
                {
                    s.pop_back();
                    answer += 2;
                }
                else
                    s.push_back(board[i][p - 1]);

                board[i][p - 1] = 0;
                break;
            }
        }
    }
    return answer;
}
