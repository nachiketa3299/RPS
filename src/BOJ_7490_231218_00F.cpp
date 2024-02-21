/// ���� 7490 0 ����� G5

/*!
1 ���� N ���� ������������ ���� 1...N 
+ �� - �Ǵ� ������ ���� ���̿� �����Ѵ�.
+ �� ���ϱ�, -�� ����, ������ ���ڸ� �̾� ���̴� ���� �ǹ��Ѵ�.
�̷��� ���� ������ ���� ����ϰ�, �� ����� 0�� �� �� �ִ��� ���ɴ�.
N�� �־����� ��, ������ ����� 0�� �Ǵ� ��� ������ ã�� ���α׷��� �ۼ��Ѵ�.
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
// �ִ� �� 3^8? 6õ������?

bool ParseOperation(int seq_size, const string& str, int target=0)
{
    int result = 1; // 0 ��°�� ���⼭ �̸� ��� (+1)

    bool is_plus = true;
    int temp = 0;

    for (size_t i = 1; i < str.size(); ++i)
    {
        if (i % 2 == 1) // Ȧ����°�� ������ ('+', '-', ' ')
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
        else // ¦����°�� ����
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


    // �׽�Ʈ ���̽��鿡 ���ؼ� ������ �����Ѵ�.
    for (size_t t = 0; t < T; ++t)
    {
        int N; cin >> N; // [3, 9]
        string init_str = "1";
        DFS(N, 1, init_str);
        cout << '\n';
    }

    return 0;
    
}