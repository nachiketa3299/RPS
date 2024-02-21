#define PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

auto main() -> int
{
    // 품목의 수
    int N; cin >> N;
    // 무게 한계
    int K; cin >> K;

    vector<int> W(N + 1, 0);
    vector<int> V(N + 1, 0);

    for (size_t i = 1; i <= N; ++i)
    {
        cin >> W[i]; // i 번째 품목의 무게(Weight)
        cin >> V[i]; // i 번째 품목의 가치(Value)
    }

    vector<vector<int>> DP(N + 1, vector<int>(K + 1, 0));

    for (size_t i = 1; i <= N; ++i)
    {
        for (size_t k = 1; k <= K; ++k)
        {
            if (W[i] > k)
            {
                DP[i][k] = DP[i - 1][k];
            }
            else //!(W[i] > k)
            {
                DP[i][k] = max
                (
                    DP[i - 1][k],
                    DP[i - 1][k - W[i]] + V[i]
                );
            }
        }
    }
    cout << DP[N][K];

    return 0;
}