// KCM Travel P4
// 18:26 - 18:47 (21) 21:18

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
#include <numeric>
#include <map>
#include <map>

using namespace std;
static constexpr int INF = numeric_limits<int>::max();

int main() {

	{int T; cin >> T;} // T is always 1? WTF?

	int N; cin >> N; // N in [2, 100]
	int M; cin >> M; // M in [0, 10'000]
	int K; cin >> K; // K in [0, 10'000]

	using w_t = pair<int, int>; // (cost, time)
	using edge_t = tuple<size_t, size_t, w_t>; // (from, to, w)
	using adj_t = pair<w_t, size_t>;

	auto tickets = vector<edge_t>(K);
	auto alist = vector<vector<adj_t>>(N, vector<adj_t>());

	for (auto& [f, t, w]: tickets) {
		auto& [cost, time] = w;
		size_t u, v; int c, d; cin >> u >> v >> c >> d;
		f = u - 1; t = v - 1; cost = c; time = d;

		alist[f].push_back({w, t});
		alist[t].push_back({w, f});
	}

	// 비용이 M원 이하면서, 시간은 가장 짧아야 한다.

	using einfo_t = pair<size_t, size_t>;


	auto const min_dist = [&alist, &M](einfo_t const route) -> int {
		auto const& [start, dest] = route;
		auto dist = vector<map<int, int>>(alist.size(), map<int, int>());
		dist[start][0] = 0;

		return 0;
	};

	auto const route = einfo_t {0, N - 1};
	auto const [min_cost, min_time] = min_dist(route);

	if (min_cost == INF || min_time == INF) {
		cout << "Poor KCM";
	}
	else {
		cout << min_time;
	}
}