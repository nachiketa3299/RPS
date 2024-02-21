#define PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Item
{
    int weight_{0};
    int value_{0};
};

int main()
{
    int N; cin >> N;
    int K; cin >> K;

    // (주의) 인덱스 1 부터 N 까지의 품목이 존재함.
    // 인덱스 0 번에는 더미 품목 (무게 0 가치 0)
    vector<Item> items(N + 1);
    for (size_t i = 1; i <= N; ++i)
    {
        cin >> items[i].weight_;
        cin >> items[i].value_;
    }

    // === 여기서부터 메모이제이션을 시작합니다. ===
    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
    // dp[i][k] 는 maximum value that can be attained with weight 
    // less than or equal to `k` using items up to `i`. (first `i` items)

    // 각 반복문은 "i 번 품목(items[i])을 넣을까 말까"에 대한 고민이다.
    for (size_t i = 1; i <= N; ++i)
    {
        // 가방의 한계 무게용량을 1 부터 , 최대 한계 K 까지 1 씩늘려가면서 생각한다.
        for (size_t k = 1; k <= K; ++k)
        {
            // 현재 품목의 무게 >  현재 가방 공간
            if (items[i].weight_ > k)
            {
                // 지금 넣을까 말까 고민중인 품목 items[i]가 현재 가방용량 k에는
                // 너무 무거워서(초과) 넣을 수 없는 상태이다.
                // 애초에 넣을 수 없는상태이므로 이전 품목에서 했던 판단을 가져오면 된다.
                dp[i][k] = dp[i - 1][k];
            }

            // 현재 품목의 무게 <= 현재 가방 공간
            else // !(items[i].weight_ > k)
            {
                // 이제 가방 용량이 충분히 확장되었으므로, items[i]가 일단 현재 가방에 들어갈 수 있다.
                dp[i][k] = max
                (
                    dp[i - 1][k], 
                    // (1) 위는 items[i]를 넣지 않았을 때의 가치의 최댓값 
                    // 이전 품목에서 했던 판단을 그대로 가져오면 된다.
                    dp[i - 1][k - items[i].weight_] + items[i].value_ 
                    // (2) 위는 items[i]를 넣었을 때의 가치의 최댓값
                    // 가방 용량이 k - 현재 품목의 무게 였을때 했던 최적 판단에, 현재 품목의 가치를 더한다.
                );
                // (1), (2) 중 최댓값이 dp[i][k] 이다.
            }
        }
    }
    cout << dp[N][K];

    return 0;
}