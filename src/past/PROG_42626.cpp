#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> spq(scoville.begin(), scoville.end());
    if (spq.top() >= K) return 0;

    int mix_cnt = 1;

    while (!spq.empty() && spq.size() >= 2) {
        auto _1_min = spq.top(); spq.pop();
        auto _2_min = spq.top(); spq.pop();
        auto mixed = _1_min + 2 * _2_min;
        spq.push(mixed);
        if (spq.top() >= K) return mix_cnt;
        mix_cnt++;
    }

    return -1;
}