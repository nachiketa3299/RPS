// title:  백준 1607 숨바꼭질 S1
// date:  2024-01-08 13:38 13:53 (15)
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <limits>

#define MAX_POS 100'000 + 1


using namespace std;

vector<int> GetAdjacentPoses(const int& cpos) {
    vector<int> ret;
    if (0 <= cpos + 1 && cpos + 1 < MAX_POS) ret.push_back(cpos + 1);
    if (0 <= cpos - 1 && cpos - 1 < MAX_POS) ret.push_back(cpos - 1);
    if (0 <= 2 * cpos && 2 * cpos < MAX_POS) ret.push_back(2 * cpos);
    return ret;
}

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }
    int N; cin >> N; const int& s_pos = N;
    int K; cin >> K; const int& e_pos = K;

    queue<int> to_visit;
    array<bool, MAX_POS> visited; visited.fill(false);
    array<int, MAX_POS> distance; distance.fill(numeric_limits<int>::max());

    to_visit.push(s_pos);
    visited[to_visit.front()] = true;
    distance[to_visit.front()] = 0;

    bool found_b = false;

    while (!to_visit.empty()) {
        auto cvisit_pos = to_visit.front(); to_visit.pop();
        for (const auto& adj_pos: GetAdjacentPoses(cvisit_pos)) {
            if (visited[adj_pos])
                continue;
            
            to_visit.push(adj_pos);
            visited[adj_pos] = true;
            distance[adj_pos] = distance[cvisit_pos] + 1;

            found_b = (adj_pos == e_pos);
        }

        if (found_b) 
            break;
    }

    cout << distance[e_pos];

    return 0;
}