// 17:28 18:04 (32)
// 백준 도로 검문 G1

#include <iostream>
#include <vector>
#include <tuple>
#include <numeric>
#include <queue>
#include <algorithm>

using namespace std;
static constexpr int INF = numeric_limits<int>::max();

int main() {
	// 지점의 갯수 [6, 1'000]
	int N; 
	cin >> N;

	// 도로의 갯수 [6, 5'000]
	int M; 
	cin >> M;

	using edge_t = tuple<size_t, size_t, int>; // type for edge (a, b, t)
	using adj_t = pair<int, size_t>; // type for adjacency list (weight, index)

	auto roads = vector<edge_t>(M);
	auto alist = vector<vector<adj_t>>(N);

	for (auto i = 0; i < M; ++i) {
		size_t a, b; int t;
		cin >> a >> b >> t; // a < b , t in [1, 10'000]
		roads[i] = edge_t { a-1, b-1, t };
		auto const& [u, v, w] = roads[i];

		alist[u].push_back(adj_t {t, v});
		alist[v].push_back(adj_t {t, u});
	}

	// for just simple edge (u, v) notation
	using einfo_t = pair<size_t, size_t>;

	// dijkstra ~
	// shortest path along `route` with or without `block`ed edge
	auto const min_dist 
		= [&alist](einfo_t const route, einfo_t const* block=nullptr) {

		auto const& [start, dest] = route;

		auto dists = vector<int>(alist.size(), INF);
		auto to_visit = priority_queue<adj_t, vector<adj_t>, greater<adj_t>>();

		// init dijkstra cond.
		dists[start] = 0;
		to_visit.push(adj_t {dists[start], start});

		// process dijkstra
		while (!to_visit.empty()) {
			auto const [dist, cv] = to_visit.top();
			to_visit.pop();

			if (cv == dest) {
				return dist;
			}

			for (auto const& [adist, av]: alist[cv]) {

				// if there is block
				if (block) {
					auto const& [bu, bv] = *block;
					// for edge has no direction, (u, v) is same as (v, u)

					if (cv == bu && av == bv) {
						continue;
					}

					if (cv == bv && av == bu) {
						continue;
					}
				}

				auto const cdist = dist + adist;
				if (cdist >= dists[av]) {
					continue;
				}

				dists[av] = cdist;
				to_visit.push(adj_t {dists[av], av});
			}
		}

		return dists[dest]; // caution: this can be INF on purpose
	}; // min_dist

	auto const rroute = einfo_t {0, N - 1}; // robbery's normal route
	auto const normal_dist = min_dist(rroute); // .. and its optimal shortest path length

	auto delays = vector<int>(M); // delays[i] is delay when blocking roads[i]

	for (auto i = 0; i < roads.size(); ++i) {
		auto const& [u, v, t] = roads[i];
		auto const delayed_dist = min_dist(rroute, new einfo_t{u, v});

		delays[i] = (delayed_dist == INF ? INF : delayed_dist - normal_dist);
	}

	auto const max_delay = *max_element(begin(delays), end(delays));

	cout << (max_delay == INF ? -1 : max_delay);
}