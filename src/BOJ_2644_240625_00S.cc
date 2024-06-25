/// 2024-06-25T12:50 13:28 (38)
/// 2644 S2 촌수계산

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using p_c_t = pair<int, int>;

class Lineage {
public:
	static constexpr int NO_DIST = -1;
	Lineage(int n, vector<p_c_t> const& p_c_rs):
		alist_(n, vector<int>())
	{
		for (auto const& [p, c]: p_c_rs) {
			alist_[p].push_back(c);
			alist_[c].push_back(p);
		}
	}

	int query(p_c_t const& qry) {
		return bfs_distance(qry);
	}

private:
	inline int vsize() const { return alist_.size(); }

	int bfs_distance(p_c_t const& qry) {
		auto const& [si, ei] = qry;
		auto to_visit = queue<int>();
		auto visited = vector<bool>(vsize(), false);
		auto distance = vector<int>(vsize(), NO_DIST);

		to_visit.push(si);
		visited[si] = true;
		distance[si] = 0;

		while (!to_visit.empty()) {
			auto const ci = to_visit.front();
			to_visit.pop();

			for (auto const& ai: alist_[ci]) {
				if (visited[ai]) continue;

				to_visit.push(ai);
				visited[ai] = true;
				distance[ai] = distance[ci] + 1;
			}
		}
		return distance[ei];
	}

private:
	vector<vector<int>> alist_;
};

istream& operator>>(istream& in, p_c_t& p_c) {
	in >> p_c.first >> p_c.second;
	--p_c.first; --p_c.second; // indexify input numbers
	return in;
}

int main() {
	int n; cin >> n; // in [1, 100]

	p_c_t qry; cin >> qry;

	int m; cin >> m;
	vector<p_c_t> p_c_rs(m);
	for (auto& p_c_r: p_c_rs)
		cin >> p_c_r;

	auto ln = Lineage(n, p_c_rs);

	cout << ln.query(qry) << '\n';
}

