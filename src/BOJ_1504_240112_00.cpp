// title: 백준 1504 특정한 최단 경로 G4
// date: 15:23

#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int start = 0;
    int end = 0;
    int distance = 0; // [1, 1000]
    friend istream& operator>>(istream& is, Edge& ref) {
        is >> ref.start >> ref.end >> ref.distance;
        return is;
    }
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; 
    int E; cin >> E;

    const int& vertices_count = N; // [2, 8e2]
    const int& edges_count = E; // [0, 2e5]

    vector<Edge> edges(E);
    for_each(edges.begin(), edges.end(), [](auto& edge){ cin >> edge; });

    // Must pass these vertices
    int v1, v2; cin >> v1 >> v2; // v1 != v2 , v1 != N, v2 != 1

    return 0;
}