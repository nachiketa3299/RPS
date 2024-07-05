// 백준 G4 해킹 10282
// 2024-07-05 19:21 19:51

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;


int main() {
	int tc_count; cin >> tc_count; // in [1, 100]

	for (int tc = 0; tc < tc_count; ++tc) {

		int n, d, c;; cin >> n >> d >> c;
		// n in [10'000], d in [100'000], c in [1, n]

		using w_t = int;
		using adj_t = pair<w_t, size_t>; // weight, index 

		auto adj_list = vector<vector<adj_t>>(n, vector<adj_t>());

		for (int i = 0; i < d; ++i) {
			int a, b, s; cin >> a >> b >> s;
			// a, b in [1, n], a != b, s in [0, 1'000]
			// a depends on b, if b infected, s sec later a also be infected.
			// no copied pair (a, b) exists

			adj_list[b - 1].push_back({s, a - 1});
		}

		auto const start = c - 1;

		auto dist = vector<w_t>(n, numeric_limits<w_t>::max());

		auto to_visit = priority_queue<adj_t, vector<adj_t>, greater<adj_t>>();

		dist[start] = 0;

		to_visit.push({dist[start], start});

		while (!to_visit.empty()) {
			auto const [new_dist, cv] = to_visit.top();
			to_visit.pop();


			for (auto const& [w, av]: adj_list[cv]) {
				auto const cdist = dist[cv] + w;

				if (cdist >= dist[av]) {
					continue;
				}

				dist[av] = cdist;
				to_visit.push({dist[av], av});
			}
		}

		int infected_count = 0, max_dist = 0;

		for (auto const& d: dist) {
			if (d == numeric_limits<w_t>::max()) {
				continue;
			}

			++infected_count;
			if (max_dist < d) max_dist = d;
		}

		cout << infected_count << " " << max_dist << '\n';
	}
}