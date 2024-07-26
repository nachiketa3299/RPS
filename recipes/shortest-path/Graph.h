#ifndef RPS_GRAPH_H
#define RPS_GRAPH_H

#include <cstddef>
#include <vector>

namespace RPS {
	template <class T, class W>
	class Graph {
	public:
		using weight_t = W;
		using value_t = T;
		using size_t = std::size_t;

		using edge_t = tuple<size_t, size_t, weight_t>
		using adj_t = pair<weight_t, size_t>;

		Graph(std::vector<value_t> const& vertices, std::vector<edge_t> edges)
			: vertices_(vertices)
			, adj_list_(vertices_.size(), std::vector<adj_t>())
		{
			for (auto const& [f, t, w]: edges) {
				adj_list_[f].push_back(adj_t{w, t});
				adj_list_[t].push_back(adj_t)
			}
		}

		std::vector<value_t> vertices_;
		std::vector<adj_t> adj_list_;
	};
}

#endif