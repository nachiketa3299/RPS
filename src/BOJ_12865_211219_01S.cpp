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

    // (����) �ε��� 1 ���� N ������ ǰ���� ������.
    // �ε��� 0 ������ ���� ǰ�� (���� 0 ��ġ 0)
    vector<Item> items(N + 1);
    for (size_t i = 1; i <= N; ++i)
    {
        cin >> items[i].weight_;
        cin >> items[i].value_;
    }

    // === ���⼭���� �޸������̼��� �����մϴ�. ===
    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
    // dp[i][k] �� maximum value that can be attained with weight 
    // less than or equal to `k` using items up to `i`. (first `i` items)

    // �� �ݺ����� "i �� ǰ��(items[i])�� ������ ����"�� ���� ����̴�.
    for (size_t i = 1; i <= N; ++i)
    {
        // ������ �Ѱ� ���Կ뷮�� 1 ���� , �ִ� �Ѱ� K ���� 1 ���÷����鼭 �����Ѵ�.
        for (size_t k = 1; k <= K; ++k)
        {
            // ���� ǰ���� ���� >  ���� ���� ����
            if (items[i].weight_ > k)
            {
                // ���� ������ ���� ������� ǰ�� items[i]�� ���� ����뷮 k����
                // �ʹ� ���ſ���(�ʰ�) ���� �� ���� �����̴�.
                // ���ʿ� ���� �� ���»����̹Ƿ� ���� ǰ�񿡼� �ߴ� �Ǵ��� �������� �ȴ�.
                dp[i][k] = dp[i - 1][k];
            }

            // ���� ǰ���� ���� <= ���� ���� ����
            else // !(items[i].weight_ > k)
            {
                // ���� ���� �뷮�� ����� Ȯ��Ǿ����Ƿ�, items[i]�� �ϴ� ���� ���濡 �� �� �ִ�.
                dp[i][k] = max
                (
                    dp[i - 1][k], 
                    // (1) ���� items[i]�� ���� �ʾ��� ���� ��ġ�� �ִ� 
                    // ���� ǰ�񿡼� �ߴ� �Ǵ��� �״�� �������� �ȴ�.
                    dp[i - 1][k - items[i].weight_] + items[i].value_ 
                    // (2) ���� items[i]�� �־��� ���� ��ġ�� �ִ�
                    // ���� �뷮�� k - ���� ǰ���� ���� ������ �ߴ� ���� �Ǵܿ�, ���� ǰ���� ��ġ�� ���Ѵ�.
                );
                // (1), (2) �� �ִ��� dp[i][k] �̴�.
            }
        }
    }
    cout << dp[N][K];

    return 0;
}