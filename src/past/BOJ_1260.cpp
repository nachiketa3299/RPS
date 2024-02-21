#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    vector<vector<int>> _edges;
    int _N;
    int _M;
    int _V;
    vector<int> _dfs_visited;
    vector<int> _bfs_visited;

private:
    void _DFS (int start) {
        this->_dfs_visited.push_back(start);
        for (int adj_v: this->_edges[start]) {
            if (this->isIn(this->_dfs_visited, adj_v)) {
                // case if visited
                continue;
            } else {
                // case if not visited
                this->_DFS(adj_v);
            }
        }

    }

    void _BFS (int start) {
        this->_bfs_visited.push_back(start);
        for (int adj_v: this->_edges[start]) {
            this->_bfs_visited.push_back(adj_v);
        }
        for (int adj_v: this->_edges[start]) {
            this->_BFS(adj_v);
        }
    }

    bool isIn (vector<int> vec, int key) {
        // return true if key is in vec
        return find(vec.begin(), vec.end(), key) != vec.end();
    }

public:
    /* Constructor */
    Graph (int n_ver, vector<vector<int>> edges) 
    : _N(n_ver) {
        this->_edges = edges;
    }


    /* Getter  */
    vector<int> getDFSVisited (int start) {
        this->_DFS(start);
        return this->_dfs_visited;
    }
    vector<int> getBFSVisited (int start) {
        this->_BFS(start);
        return this->_bfs_visited;
    }

};

int main (void) {
    int N, M, V;
    cin >> N >> M >> V;
    vector<vector<int>> edges (N);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        edges[u - 1].push_back(v - 1);
        edges[v - 1].push_back(u - 1);
    }

    for (auto &e: edges) {
        sort(e.begin(), e.end());
    }

    Graph graph(N, edges);

    vector<int> dfs_result = graph.getDFSVisited(V - 1);
    vector<int> bfs_result = graph.getBFSVisited(V - 1);

    for (auto e: dfs_result) {
        cout << e + 1 << " ";
    }
    cout << endl;
    /*
    for (auto e: bfs_result) {
        cout << e + 1 << " ";
    }
    */
    return 0;
}
