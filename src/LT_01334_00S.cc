// 14:25 15:09 //44
#include <vector>
#include <iostream>
using namespace std;

#include <utility>
#include <numeric>
#include <queue>

class Solution {
public:
	int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
		using w_t = int;
		using adj_t = pair<w_t, int>;
		using pq_t = priority_queue<adj_t, vector<adj_t>, greater<adj_t>>;

		auto alist = vector<vector<adj_t>>(n, vector<adj_t>());

		for (auto const& edge: edges) {
			auto const& from = edge[0];
			auto const& to = edge[1];
			auto const& weight = edge[2];

			alist[from].push_back({weight, to});
			alist[to].push_back({weight, from});
		}

		auto reachable_counts = vector<int>(n, int {});
		static constexpr auto INF_W = numeric_limits<w_t>::max();

		auto dijkstra = [&alist, &distanceThreshold](auto const& start) {
			auto dists = vector<w_t>(alist.size(), INF_W);
			dists[start] = w_t {};
			auto tvisit = pq_t();
			tvisit.push({dists[start], start});

			while (!tvisit.empty()) {
				auto const [cdist, cv] = tvisit.top();
				tvisit.pop();

				for (auto const& [aw, av]: alist[cv]) {
					auto const candid_dist = cdist + aw;
					if (candid_dist >= dists[av]) {
						continue;
					}

					dists[av] = candid_dist;
					tvisit.push({dists[av], av});
				}
			}

			auto reachable_count = int {};

			for (auto i = 0; i < dists.size(); ++i) {
				if (dists[i] > distanceThreshold) {
					continue;
				}

				if (i == start) {
					continue;
				}
				++reachable_count;
			}

			return reachable_count;
		};

		auto min_count = numeric_limits<int>::max();
		auto min_index = int {};

		for (auto i = 0; i < reachable_counts.size(); ++i) {
			reachable_counts[i] = dijkstra(i);

			if (reachable_counts[i] > min_count) {
				continue;
			}

			min_count = reachable_counts[i];
			min_index = i;
		}

		return min_index;
	}
};

int main() {
	vector<vector<int>> edges = {
		{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}
	};

	auto s = Solution().findTheCity(4, edges, 4);

	cout << s << endl;;
}