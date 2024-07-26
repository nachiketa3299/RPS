// 백준 11657 G4 타임머신 14:50 15:09 (19)

#include <iostream>
#include <tuple>
#include <vector>
#include <numeric>

using namespace std;

int main() {
	int N; cin >> N; // N in [1, 500]
	int M; cin >> M; // M in [1, 6'000]

	using w_t = long long int;
	using edge_t = tuple<w_t, size_t, size_t>;

	auto edges = vector<edge_t>(M);
	for (auto& [C, A, B]: edges) {
		cin >> A >> B >> C;
		--A; --B;
		// A, B in [1, N]
		// C in [-10'000, 10'000]
	}

	const auto kInf_Weight = numeric_limits<w_t>::max();
	auto dists = vector<w_t>(N, kInf_Weight);
	dists[0] = w_t {};

	for (auto i = 0; i < N - 1; ++i) {
		for (auto const& [w, f, t]: edges) {
			if (dists[f] == kInf_Weight) {
				continue;
			}

			if (dists[f] + w >= dists[t]) {
				continue;
			}

			dists[t] = dists[f] + w;
		}
	}

	auto has_negative_cycle = false;

	for (auto const& [w, f, t]: edges) {
		if (dists[f] == kInf_Weight) {
			continue;
		}

		if (dists[f] + w >= dists[t]) {
			continue;
		}

		has_negative_cycle = true;
		break;
	}

	if (has_negative_cycle) {
		cout << -1;
	}
	else {
		for (auto i = 1; i < dists.size(); ++i) {
			cout << (dists[i] == kInf_Weight ? -1 : dists[i]) << '\n';
		}
	}
}