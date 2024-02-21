#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using PQ = priority_queue<int, vector<int>, less<int>>;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N; cin >> N;
    PQ pq;

    for (int i = 0; i < N * N; ++i)
    {
        int t; cin >> t;
        pq.push(t);
    }
    for (int i = 0; i < N - 1; ++i) pq.pop();
    cout << pq.top() << '\n';

    return 0;
}