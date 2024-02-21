/// 백준 7490 0 만들기 G5

/*!
1 부터 N 까지 오름차순으로 수열 1...N 
+ 나 - 또는 공백을 숫자 사이에 삽입한다.
+ 는 더하기, -는 빼기, 공백은 숫자를 이어 붙이는 것을 의미한다.
이렇게 만든 수식의 값을 계산하고, 그 결과가 0이 될 수 있는지 살핀다.
N이 주어졌을 때, 수식의 결과가 0이 되는 모든 수식을 찾는 프로그램을 작성한다.
*/
// 15:42 ~

#define PS_DEBUG
#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

#define S_ADD '+'
#define S_SUB '-'
#define S_CON ' '

// '+' 75
// '-` 77
// ' '
// 최대 총 3^8? 6천번정도?

bool ParseOperation(int seq_size, const string& str, int target=0)
{
    int result = 1; // 0 번째는 여기서 미리 계산 (+1)

    bool is_plus = true;
    int temp = 0;

    for (size_t i = 1; i < str.size(); ++i)
    {
        if (i % 2 == 1) // 홀수번째는 연산자 ('+', '-', ' ')
        {
            switch(str[i])
            {
                case S_ADD:
                    is_plus = true;
                    break;
                case S_SUB:
                    is_plus = false;
                    break;
                case S_CON:
                    break;
            }
        }
        else // 짝수번째는 숫자
        {

        }
    }
    return (result == 0);
}

void DFS(int seq_size, int num, const string& str)
{
    if (seq_size == num)
    {
        if (ParseOperation(seq_size, str))
        {
            cout << str << '\n';
        }
        return;
    }

    DFS(seq_size, num + 1, str + S_ADD + to_string(num + 1));
    DFS(seq_size, num + 1, str + S_SUB + to_string(num + 1));
    DFS(seq_size, num + 1, str + S_CON + to_string(num + 1));
}


int main()
{
    int T; cin >> T; // [0, 10)


    // 테스트 케이스들에 대해서 다음을 수행한다.
    for (size_t t = 0; t < T; ++t)
    {
        int N; cin >> N; // [3, 9]
        string init_str = "1";
        DFS(N, 1, init_str);
        cout << '\n';
    }

    return 0;
    
}