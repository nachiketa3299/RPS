// title:  백준 1389 케빈 베이컨의 6단계 법칙 S1
// date: 2023-01-06 14:49 15:45 (30)
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <numeric>

#define DISCONNECTED -1

using namespace std;

#ifdef PS_DEBUG
void PrintList(const vector<vector<int>>& list) {
    for (size_t i = 1; i < list.size(); ++i) {
        cout << i << " | ";
        for (const auto& adj: list[i])
            cout << adj << " ";
        cout << '\n';
    }
    cout << '\n';
}
#endif //PS_DEBUG 

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; 
    int M; cin >> M;
    const int& n_users = N; // [2, 100]
    const int& n_relations = M; // [1, 5000]
    vector<vector<int>> adj_lists(n_users + 1, vector<int>());

    for (size_t r = 0; r < n_relations; ++r) {
        int s, e; cin >> s >> e;
        auto& cadj_list = adj_lists[s];

        if (cadj_list.end() != find(cadj_list.begin(), cadj_list.end(), e))
            continue;
        
        adj_lists[s].push_back(e);
        adj_lists[e].push_back(s);
    }

    #ifdef PS_DEBUG
    cout << "> Input Test: \n";
    PrintList(adj_lists);
    #endif //PS_DEBUG 
    
    vector<vector<int>> kv_numbers(n_users + 1, vector<int>(n_users + 1, DISCONNECTED));

    for (int user = 1; user <= n_users; ++user) {
        vector<bool> visited(n_users + 1, false);
        auto& ckv_number = kv_numbers[user];
        ckv_number[user] = 0;
        queue<int> to_visit;
        to_visit.push(user); 

        while (!to_visit.empty()) {
            const auto cvisit = to_visit.front(); to_visit.pop();
            bool found_target = false;
            for (const auto& adj: adj_lists[cvisit]) {
                if (visited[adj])
                    continue;

                ckv_number[adj] = ckv_number[cvisit] + 1;

                visited[adj] = true;
                to_visit.push(adj);
            }

            if (found_target) 
                break;
        }
    }

    #ifdef PS_DEBUG
    cout << "> KV_Numbers: \n";
    for (size_t v = 1; v <= n_users; ++v) {
        cout << accumulate(kv_numbers[v].begin(), kv_numbers[v].end(), 0) << " | ";
        for (size_t h = 1; h <= n_users; ++h) {
            cout << kv_numbers[v][h] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
    #endif //PS_DEBUG 

    for (size_t v = 1; v <= n_users; ++v) {
        kv_numbers[v][0] = accumulate(kv_numbers[v].begin(), kv_numbers[v].end(), 0);
    }
    size_t min_index = -1;
    auto minval = numeric_limits<int>::max();
    for (size_t v = 1; v <= n_users; ++v) {
        if (kv_numbers[v][0] < minval) {
            minval = kv_numbers[v][0];
            min_index = v;
        }
    }
    cout << min_index;
    return 0;
}