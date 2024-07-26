// 백준 10282 해킹 
// 13:27 14:05

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
	using adj_t = pair<int, int>; // weight , index
	using PriorityQueue = priority_queue<adj_t, vector<adj_t>, greater<adj_t>>;

	int tc; cin >> tc; // tc in [1, 100]

	for (auto i = 0; i < tc; ++i) { // TC LOOP
		int n, d, c; cin >> n >> d >> c;
		// n in [1, 10'000], 
		// d in [100'000], 
		// c in [1, n]

		auto alist = vector<vector<adj_t>>(n, vector<adj_t>());

		for (auto j = 0; j < d; ++j) {
			int a, b, s; cin >> a >> b >> s; // b -> a : s
			// a, b in [1, n]
			// a != b
			// s in [0, 1'000]

			alist[b - 1].push_back({s, a - 1});
		}


		auto dijkstra = [&alist](auto const& start)  {
			static auto constexpr INF_W = numeric_limits<int>::max();

			auto to_visit = PriorityQueue();
			auto dists = vector<int>(alist.size(), INF_W);

			dists[start] = int {};

			to_visit.push({dists[start], start});

			while (!to_visit.empty()) {
				auto const [cdist, cv] = to_visit.top();
				to_visit.pop();

				for (auto const& [aw, av]: alist[cv]) {
					auto const candid_dist = cdist + aw;

					if (candid_dist >= dists[av]) {
						continue;
					}

					dists[av] = candid_dist;
					to_visit.push({dists[av], av});
				}
			}

			auto count = int {};
			auto max_time = int {};

			for (auto const& dist: dists) {
				if (dist == INF_W) {
					continue;
				}

				++count;
				max_time = max(dist, max_time);
			}

			return make_pair(count, max_time);
		};

		auto const [count, max_time] = dijkstra(c - 1);
		cout << count << " " << max_time << '\n';
	}
}