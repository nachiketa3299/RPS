// [[2023-10-24T12:27, 2023-10-24T13:11]]
#include <iostream>
#include <queue>

using namespace std;

using PQ = priority_queue<int, vector<int>, greater<int>>;

int main(void)
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    PQ pq;
    for (int i = 0; i < N * N; ++i)
    {
        int t; cin >> t;

        pq.push(t);
        if (pq.size() > N) pq.pop();
    }

    //for (int i = 0; i < N - 1; ++i) pq.pop();

    cout << pq.top() << '\n';

    return 0;
}
