/// 백준 11050(B1, 이항 계수)
/// Dynamic Programming
/// @date 2023-11-01T15:11 ~ 2023-11-01T15:52 (41)
/// 
/// 자연수 N과 정수 K가 주어졌을 때 이항 계수 \binom{N}{K}를 구하는 프로그램을 작성한다.

#include <iostream>
#include <vector>

using namespace std;

int Binom(const int& N, const int& K)
{
    /// 이항계수 (N, K)는
    /// (N-1, K-1) + (N-1, K)  -> (0 < K < N)
    /// 1                      -> (K == 0 || K == N)

    vector<vector<int>> cache(N + 1);

    for (int n = 1; n < N + 1; ++n)
    {
        cache[n].resize(n + 1);
        for (int k = 0; k < cache[n].size(); ++k)
        {
            if (k == 0 || k == n) cache[n][k] = 1;
            else cache[n][k] = cache[n - 1][k - 1] + cache[n - 1][k];
        }
    }
    return cache[N][K];
}

int main(void)
{
    int N; cin >> N; ///< [1, 10]
    int K; cin >> K; ///< [0, N ]


    cout << Binom(N, K) << '\n';

    return 0;
}
