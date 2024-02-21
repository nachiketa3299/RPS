#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using _2DIV = vector<vector<int>>;
using PQ = priority_queue<int, vector<int>, less<int>>;

int main(void) {
    int N; cin >> N;
    _2DIV raws(N, vector<int>(N));
    for (auto& i : raws) {
        for (auto& j : i) cin >> j;
    }

    PQ pq;
    for (auto it = raws.rbegin(); it != raws.rend(); ++it) {
        for (auto& c : *(it)) pq.push(c);
        while (pq.size() <= N) pq.pop();
    }
    while(pq.size() == 1) pq.pop();
    cout << pq.top() << '\n';

    return 0;
}