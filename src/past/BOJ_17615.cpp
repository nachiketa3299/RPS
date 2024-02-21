///@date 2023-11-06
///백준 17615 볼 모으기
/// Greedy Algorithm (?)

/*!
* 빨간색 볼과 파란색 볼이 일직선상에 놓여 있다.
* RBBBRBRRR
* 볼을 규칙대로 옮겨서 **같은 색 볼끼리 인접하게 놓이도록 하려고 한다.**
* 볼을 옮기는 규칙은 아래와 같다.
* (1) 바로 옆에 다른 색의 볼이 있으면 그 볼을 모두 뛰어 넘어 옮길 수 있다.
* 예를 들어, 빨간색 볼은 옆에 있는 파란색 볼 무더기를 한 번에 뛰어넘어 옮길 수 있다.
* (2) 옮길 수 있는 볼의 색은 한 가지이다.
* 예를 들어, 빨간색 볼을 처음에 옮겼으면, 다음에도 빨간색 볼만 옮길 수 있다.
* 
* 볼 옮기기 예
* 1. RBBBRBRRR 4R을 5B 뒤로 옮길 수 있음
* 2. RBBBBRRRR 0R을 4B 뒤로 옮길 수 있음
* 3. BBBBRRRRR
* 
* 일직선 상에 놓여 있는 볼에 대한 정보가 주어질 때, 규칙에 따라 볼을 이동하여 같은 색끼리 모으되 최소 이동횟수를 찾는 프로그램을 작성한다.
*/

#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct ColorChunk
{
    ColorChunk(char color, int cnt): is_red(color == 'R' ? true : false), cnt(cnt) {}
    bool is_red = true;
    int cnt = 0;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N; cin >> N; ///< N [1, 5e5]

    /// RRRR 이나 BBBB같은 것도 들어올 수 있으며 이 경우 답은 0
    string input; cin >> input; ///< R, B


    /// RBBBRBRRR를 (R1)(B3)(R1)(B1)(R3) 형태로 만들어 보관
    vector<ColorChunk> chunks;
    int r_cnt_sum = 0; int b_cnt_sum = 0;

    {
        char tprev; ///< 바로 이전에 어떤 문자였는가
        int tcnt = 0; ///< 현재 세고 있는 문자의 갯수
        for (int i = 0; i < N; ++i)
        {
            /// 첫 요소는 세팅만
            if (i == 0)
            {
                tprev = input[0];
                tcnt++;
            }
            /// 첫 요소 아니면
            else
            {
                /// 지금 보고있는게 이전거랑 다르다?
                if (tprev != input[i])
                {
                    /// 이제까지 센거 푸쉬하고
                    chunks.push_back(ColorChunk(tprev, tcnt));
                    /// 초기화
                    tprev = input[i];
                    tcnt = 1;
                }
                /// 지금 보고 있는게 이전거랑 같다?
                else
                    tcnt++; /// 그냥 갯수만 증가
            }
            /// 혹시 지금 마지막 요소인가?
            if (i + 1 == N)
                /// 그냥 포문 탈출하면 마지막에 셌던 것들이 `chunks`에 안들어가므로 푸쉬해줌
                chunks.push_back(ColorChunk(tprev, tcnt));

            /// R의 총 갯수랑 B의 총 갯수 세야함
            if (input[i] == 'R') r_cnt_sum++;
            else                 b_cnt_sum++;
        }
    }


    /// B를 모두 좌측으로, B를 모두 우측으로, R을 모두 좌측으로, R을 모두 우측으로 이동하는 4가지 가짓수를 이 큐에 넣고 탑만 뽑아먹을꺼임
    priority_queue<int, vector<int>, greater<int>> candid_counts;

    /// @short 최 좌측과 최 우측에 몰려있는 청크들은 이미 정렬이 되어있으므로 이동할 필요가 없다. 그래서 그냥 다 더한담에 빼주면 됨.
    /// (R1)(B3)(R1)(B1)(R3) 라고 가정하면
    /// *R*을 모두 *좌측*으로 옮긴다 1 + 1 + 3 - 맨 *좌측* 첫번째 `ColorChunk`가 *R*라면 그 청크의 갯수, 아니라면 아무것도 안 빼기
    /// *R*을 모두 *우측*으로 옮긴다 1 + 1 + 3 - 맨 *우측* 첫번째 `ColorChunk`가 *R*라면 그 청크의 갯수, 아니라면 아무것도 안 빼기
    /// *B*을 모두 *좌측*으로 옮긴다 3 + 1     - 맨 *좌측* 첫번째 `ColorChunk`가 *B*라면 그 청크의 갯수, 아니라면 아무것도 안 빼기
    /// *B*을 모두 *우측*으로 옮긴다 3 + 1     - 맨 *우측* 첫번째 `ColorChunk`가 *B*라면 그 청크의 갯수, 아니라면 아무것도 안 빼기

    candid_counts.push(r_cnt_sum - ( chunks.front().is_red ? chunks.front().cnt : 0));
    candid_counts.push(r_cnt_sum - ( chunks.back ().is_red ? chunks.back ().cnt : 0));
    candid_counts.push(b_cnt_sum - (!chunks.front().is_red ? chunks.front().cnt : 0));
    candid_counts.push(b_cnt_sum - (!chunks.back ().is_red ? chunks.back ().cnt : 0));

    /// 다 넣고 top을 빼먹자.

    cout << candid_counts.top() << '\n';

    return 0;
}

