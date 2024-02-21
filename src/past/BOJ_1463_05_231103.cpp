///@date 2023-11-03

/// (1) X가 3으로 나누어 떨어지면 3으로 나눈다
/// (2) X가 2로 나누어 떨어지면 2로 나눈다
/// (3) 1을 뺀다
/// 정수 N이 주어졌을 때, 위와 같은 연산 3개를 *적절히* 사용해서 숫자 1을 만들 때, 연산을 사용하는 횟수의 최솟값은?
/// 예를 들어 (10 -> 9 -> 3 -> 1)
/// 

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int IntType;
#define IO -1

class Int
{
public:
    Int(const IntType& N): N(N), cache(N <= 3 ? 3 : N) 
    {
        cache[1 IO] = 0; /// 그냥
        cache[2 IO] = cache[1 IO] + 1; /// 2로 나누는거 혹은 1 빼는거
        cache[3 IO] = cache[1 IO] + 1; /// 3으로 나누는거
    };
    int get_min_op_count()
    {
        if (N <= 3) return cache[N IO];

        for (int i = 4; i <= N; ++i)
        {
            vector<int> candid;

            if (i % 3 == 0) candid.push_back(i / 3);
            if (i % 2 == 0) candid.push_back(i / 2);
                            candid.push_back(i - 1);

            static auto cache_cmp = [this](const int& op1, const int& op2) { return cache[op1 IO] < cache[op2 IO]; };
            int min_case = *min_element(candid.begin(), candid.end(), cache_cmp);
            cache[i IO] = cache[min_case IO] + 1;
        }
        return cache[N IO];
    }
private:
    IntType N;
    vector<int> cache;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    IntType N; cin >> N; ///< N [1, 1e7]
    Int n(N);

    cout << n.get_min_op_count() << '\n';

    return 0;
}