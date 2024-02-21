#include <iostream>
#include <vector>
#include <queue>

#define INF 1000'000'000
#define N 3

using namespace std;

vector< pair<int, int> > nodes[N];
int dist[N];

void dijkstra(int start) {
    priority_queue< pair<int, int> > pq;

    pq.push({ 0, start });
    dist[start] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first; // Idiotic Code !!!!
        int here = pq.top().second;
        pq.pop();

        // Past record is better than current
        if (dist[here] < cost)
            continue;
        
        for (int i = 0; i < nodes[here].size(); ++i) {
            int via_cost = cost + nodes[here][i].first;

            if (via_cost >= dist[nodes[here][i].second])
                continue;
            
            dist[nodes[here][i].second] = via_cost;
            pq.push({ -via_cost, nodes[here][i].second });
        }
    }
}

auto main() -> int {
    for (int i = 0; i < N; ++i)
        dist[i] = INF;

    nodes[0].push_back({ 5, 1 }); // 0 | 1[5] 2[1]
    nodes[0].push_back({ 1, 2 }); // 1 |
    nodes[2].push_back({ 3, 1 }); // 2 | 1[3]

    dijkstra(0);

    for (int i = 0; i < N; ++i)
        cout << dist[i] << " ";

    return 0;
}