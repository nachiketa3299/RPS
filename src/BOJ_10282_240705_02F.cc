// 백준 10282 해킹 1158 똥싸러 1217 다시 1233

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;
using pair_t = pair<int, int>;

struct wedge_t
{
	int v;
	int w;
	bool operator>(wedge_t const& o) { return w > o.w; }
};

int main() {
	int tcs; cin >> tcs;

	for (auto tc = 0; tc < tcs; ++tc) {
		// INPUT
		// n in [1, 10'000], d in [1, 100'000], c in [1, n]
		int n, d, c; cin >> n >> d >> c; 

		auto deps = vector<tuple<int, int, int>>(d); // a(0) --w(2)-- b(1)

		for (auto& [a, b, s] : deps) {
			cin >> a >> b >> s; // no redundant (a, b) pair
		}

		// PROCESS

		auto adj_list = 
			vector<vector<wedge_t>>(n, vector<wedge_t>());

		for (auto const& [a, b, s]: deps) {
			adj_list[b - 1].push_back({a - 1, s});
		}

		// dijkstra
		auto dist_from_s = vector<int>(d, numeric_limits<int>::max());
		dist_from_s[c] = 0;

		auto to_visit = priority_queue<wedge_t, vector<wedge_t>, greater<wedge_t>>();
		to_visit.push({c, dist_from_s[c]});

		while (!to_visit.empty()) {
			auto const [cv, cw] = to_visit.top();
			to_visit.pop();

			if (cw > dist_from_s[cv]) {
				continue;
			}
			
			for (auto const& [av, aw]: adj_list[cv]) {
				auto const dist_new = cw + aw;

				if (dist_new > dist_from_s[av]) {
					continue;
				}

				dist_from_s[av] = dist_new;
				to_visit.push({av, dist_new});
			}
		}

		for(auto const& dist: dist_from_s)
		{
			cout << dist << ", ";
		}


	}
}