#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <numeric>

using namespace std;

template <class T, class W>
class Graph {
public:
	using edge_t = tuple<size_t, size_t, W>;
	using adj_t = pair<W, size_t>;

	Graph(vector<T> const& nodes, vector<Graph::edge_t> edges): 
		nodes_(nodes), 
		adj_list_(nodes.size(), vector<adj_t>()) 
	{
		for (auto const& [f, t, w]: edges) {
			// assumes that no redundant edge in
			adj_list_[f].push_back({w, t});
			adj_list_[t].push_back({w, f});
		}
	}

	friend ostream& operator<<(ostream& out, Graph const& r) {
		for (auto i = 0; i < r.adj_list_.size(); ++i) {
			out << r.nodes_[i] << '(' << i << "): ";

			for (auto const& [w, t]: r.adj_list_[i]) {
				out << '{';
				out << r.nodes_[t] << '(' << t << "), ";
				out << w;
				out << "}, ";
			}

			out << '\n';
		}
		return out;
	}

	W shortest_distance_between(size_t start, size_t dest) {
		auto to_visit = priority_queue<adj_t, vector<adj_t>, greater<adj_t>>();
		auto dists = vector<W>(nodes_.size(), inf());

		dists[start] = inf() - inf();
		to_visit.push({dists[start], start});

		while(!to_visit.empty()) {
			auto const [new_dist, c] = to_visit.top();

			if (c == dest) {
				return new_dist;
			}

			to_visit.pop();

			if (new_dist > dists[c]) {
				continue;
			}

			for (auto const& [w, adj]: adj_list_[c]) {
				auto const cdist = dists[c] + w; // candid distance

				if (cdist >= dists[adj]) {
					continue;
				}

				dists[adj] = cdist;
				to_visit.push({cdist, adj});
			}
		}
		return dists[dest];
	}

	static W inf() {
		return numeric_limits<W>::max();
	}

private:
	vector<T> nodes_;
	vector<vector<adj_t>> adj_list_;
};

struct node_t { string v; };
ostream& operator<<(ostream& out, node_t const& r) {
	out << r.v;
	return out;
}

int main() {
	auto const nodes = vector<node_t> { 
		{"A"}, {"B"}, {"C"}, {"D"}, {"E"}, {"F"}, {"G"}
	};

	auto const edges = vector<Graph<node_t, float>::edge_t> {
		{0, 1,  2.f}, {0, 2,  6.f}, 
		{2, 3,  8.f}, {1, 3,  5.f},
		{3, 4, 10.f}, {3, 5, 15.f},
		{4, 6,  2.f}, {5, 6,  6.f}
	};

	auto g = Graph<node_t, float>(nodes, edges);
	cout << g;


	cout << g.shortest_distance_between(0, 0) << endl;
	cout << g.shortest_distance_between(0, 1) << endl;
	cout << g.shortest_distance_between(0, 2) << endl;
	cout << g.shortest_distance_between(0, 3) << endl;
	cout << g.shortest_distance_between(0, 4) << endl;
	cout << g.shortest_distance_between(0, 5) << endl;
	cout << g.shortest_distance_between(0, 6) << endl;
}
