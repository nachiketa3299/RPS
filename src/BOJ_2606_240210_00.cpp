#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define PS_DEBUG
// #undef PS_DEBUG

#define PS_IO_OPT                                                                      \
    std::ios_base::sync_with_stdio(false);                                             \
    std::cin.tie(nullptr);                                                             \
    std::cout.tie(nullptr);

using namespace std;

auto main() -> int
{
    PS_IO_OPT
    int node_size; cin >> node_size; // [1, 100]
    int edge_size; cin >> edge_size;

    vector<vector<int>> adj_lists(node_size);

    for (int i = 0; i < edge_size; ++i)
    {
        int edge_start, edge_end;
        cin >> edge_start >> edge_end;
        adj_lists[edge_start - 1].push_back(edge_end - 1);
        adj_lists[edge_end - 1].push_back(edge_start - 1);
    }

    const int s_pos = 1 - 1;

    vector<bool> discovered(node_size, false);
    queue<int> to_visit;
    int connected_count = 0;

    { // Init BFS
        to_visit.push(s_pos);
        discovered[s_pos] = true;
    }

    // Do BFS
    while (!to_visit.empty())
    {
        const auto cv_pos = to_visit.front();
        to_visit.pop();

        for (const auto& adj_pos: adj_lists[cv_pos])
        {
            if (discovered[adj_pos])
                continue;

            discovered[adj_pos] = true;
            to_visit.push(adj_pos);
            connected_count++;
        }
    }

    cout << connected_count << '\n';

    return EXIT_SUCCESS;
}