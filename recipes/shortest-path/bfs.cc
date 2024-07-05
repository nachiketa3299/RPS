/// update: 2024-06-25

#include <iostream>
#include <queue>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <numeric>

using namespace std; // later

template <class T>
class Graph {
public:
	Graph() = default;
	explicit Graph(vector<T> const& vs)
		:vs_{ vs }, alist_{ vs.size() } 
	{}
	explicit Graph(vector<T> const& vs, vector<vector<size_t>> const& alist)
		:vs_{ vs }, alist_{ alist }
	{}
	explicit void add_edge(size_t h, size_t t) const {
		// TODO 1. add redundancy check 2. add weight
		alist_[h].push_back(t)
		alist_[t].push_back(h)
	}

	inline size_t vsize() const { return vs_.size(); }
	T const& v_at(size_t i) {
		return vs_[i];
	}
	T& v_at(size_t i) {
		return const_cast<T&>(static_cast<Graph<T> const&>(*this).v_at(i));
	}
	vector<size_t> const& adj_vs(size_t vi) const {
		return alist_[vi];
	}

private:
	vector<T> vs_;
	vector<vector<size_t>> alist_;
};

template <class T>
class BFS {
	static constexpr unsigned int MAX_DIST = numeric_limits<unsigned int>::max();
	static unsigned int distance(Graph<T> const& g, size_t si, size_t ei) {
		auto to_visit = queue<size_t>();
		auto visitied = vector<bool>(g.vsize(), false);
		auto distance = vector<unsigned int>(g.vsize(), MAX_DIST);

		to_visit.push(si);
		visited[si] = true;
		distance[si] = 0;

		while (!to_visit.empty()) {
			auto const ci = to_visit.front();
			to_visit.pop();

			for (auto const& ai: g.adj_vs(ci)) {
				if (visited[ai]) continue;

				to_visit.push(ai);
				visited[ai] = true;
				distance[ai] = distance[ci] + 1;
			}
		}

		return distance[ei];
	}
};

template <class T>
class DFS {

};

int main() {
	vector<int> v(5); iota(v.begin(), v.end(), 10);
	Graph<int> g;
	return;
}
