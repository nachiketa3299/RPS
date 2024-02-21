#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <functional>

using namespace std;

class Graph {
public:
    using PosType = size_t;
public:
    using BFSStartDelegateSignature   = function<void(const PosType& /*s_pos*/, const PosType& /*e_pos*/)>;
    using BFSVisitDelgateSinature     = function<void(const PosType& /*c_pos*/, const PosType& /*v_pos*/)>;
    using BFSSuccessDelegateSignature = function<void(const PosType& /*s_pos*/, const PosType& /*e_pos*/)>;
    using BFSFailedDelegateSignature  = function<void(const PosType& /*s_pos*/, const PosType& /*e_pos*/)>;
public:
    enum class SearchState {
        Failed, Success
    };
    struct BFS_Data {
    public:
        BFS_Data(const Graph& graph, const int& is_pos, const int& ie_pos)
            : s_pos(is_pos), e_pos(ie_pos)
            , state(SearchState::Failed)
            , distance(graph.size_v(), numeric_limits<int>::max())
            , visited(graph.size_v(), false)
            , pparents(graph.size_v())
        {}
    public:
        void Print() const {
            cout << ">> BFS Data from " << s_pos << " to " << e_pos << '\n';

            if (!IsValid()) {
                cout << "\t> No Path.\n";
                return;
            }

            cout << "\t> Shortest Path: ";
            for (const auto& pos: path())
                cout << pos << " ";
            cout << '\n';
            cout << "\t> Distance: " << distance[e_pos] << '\n';
        }
        vector<Graph::PosType> path() const {
            assert(IsValid());
            vector<Graph::PosType> ret;
            auto c_pos = e_pos;
            ret.push_back(c_pos);
            while (true) {
                const auto p_pos = pparents[c_pos];
                if (p_pos == c_pos)
                    break;
                ret.push_back(p_pos);
                c_pos = p_pos;
            }
            reverse(ret.begin(), ret.end());
            return ret;
        }
        inline bool IsValid() const {
            return state == SearchState::Failed ? false : true;
        }
    public:
        SearchState state;
        int s_pos, e_pos;
        vector<int> distance;
        vector<bool> visited;
        vector<Graph::PosType> pparents;
    };
public:
    Graph(const size_t& v_count)
        : adj_lists_(v_count)
    {}
    void AddEdge(const PosType& v_s, const PosType& v_e) {
        assert(v_s < size_v() && v_e < size_v());

        if (find(adj_lists_[v_s].cbegin(), adj_lists_[v_s].cend(), v_e) != adj_lists_[v_s].cend())
            return;
        if (find(adj_lists_[v_e].cbegin(), adj_lists_[v_e].cend(), v_s) != adj_lists_[v_e].cend())
            return;

        adj_lists_[v_s].push_back(v_e);
        adj_lists_[v_e].push_back(v_s);
    }
    inline size_t size_v() const {
        return adj_lists_.size();
    }
    void PrintEdges() const {
        for (size_t v = 0; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& adj_v: adj_lists_[v])
                cout << adj_v << " ";
            cout << '\n';
        }
    }
    inline const vector<PosType>& GetAdjacentPoses(const PosType& pos) const {
        return adj_lists_[pos];
    }
    BFS_Data BFS(const PosType& s_pos, const PosType& e_pos) const {
        BFS_Data ret(*this, s_pos, e_pos);

        queue<PosType> to_visit;

        // Init state
        to_visit.push(s_pos);
        ret.visited[s_pos] = true;
        ret.distance[s_pos] = 0;
        ret.pparents[s_pos] = s_pos;
        OnBFSStart(s_pos, e_pos);

        while (!to_visit.empty()) {
            const auto cv_pos = to_visit.front();
            to_visit.pop();
            for (const auto& adj_pos: GetAdjacentPoses(cv_pos)) {
                if (ret.visited[adj_pos])
                    continue;

                ret.visited[adj_pos] = true;
                ret.distance[adj_pos] = ret.distance[cv_pos] + 1;
                ret.pparents[adj_pos] = cv_pos;
                OnBFSVisit(cv_pos, adj_pos);

                if (adj_pos == e_pos) {
                    ret.state = SearchState::Success;
                    break;
                }

                to_visit.push(adj_pos);
            }
        }

        switch (ret.state) {
            case SearchState::Success:
                OnBFSSuccess(s_pos, e_pos);
                return ret;
            default:
            case SearchState::Failed:
                OnBFSFailed(s_pos, e_pos);
                return ret;
        }
    }
private:
    vector<vector<PosType>> adj_lists_;
public:
    void PushBFSStartDelegate    (const BFSStartDelegateSignature&   delegate) {
        bfs_start_delegates_.push_back(delegate);
    }
    void PushBFSSuccessDelegate  (const BFSSuccessDelegateSignature& delegate) {
        bfs_success_delegates_.push_back(delegate);
    }
    void PushBFSVisitDelegate    (const BFSVisitDelgateSinature&     delegate) {
        bfs_visit_delegates_.push_back(delegate);
    }
    void PushBFSFailedDelegate(const BFSFailedDelegateSignature&  delegate) {
        bfs_failed_delegates_.push_back(delegate);
    }
private:
    inline void OnBFSStart  (BFSStartDelegateSignature::first_argument_type   s_pos, BFSStartDelegateSignature::second_argument_type   e_pos) const {
        for (const auto& on_bfs_start_delegate: bfs_start_delegates_)
            on_bfs_start_delegate(s_pos, e_pos);
    }
    inline void OnBFSVisit  (BFSVisitDelgateSinature::first_argument_type     c_pos, BFSVisitDelgateSinature::second_argument_type     v_pos) const {
        for (const auto& on_bfs_visit_delegate: bfs_visit_delegates_)
            on_bfs_visit_delegate(c_pos, v_pos);
    }
    inline void OnBFSSuccess(BFSSuccessDelegateSignature::first_argument_type s_pos, BFSSuccessDelegateSignature::second_argument_type e_pos) const {
        for (const auto& on_bfs_end_delegate: bfs_success_delegates_)
            on_bfs_end_delegate(s_pos, e_pos);
    }
    inline void OnBFSFailed (BFSFailedDelegateSignature::first_argument_type  s_pos, BFSFailedDelegateSignature::second_argument_type  e_pos) const {
        for (const auto& on_bfs_error_end_delegate: bfs_failed_delegates_)
            on_bfs_error_end_delegate(s_pos, e_pos);
    }
private:
    vector<BFSStartDelegateSignature>   bfs_start_delegates_;
    vector<BFSVisitDelgateSinature>     bfs_visit_delegates_;
    vector<BFSSuccessDelegateSignature> bfs_success_delegates_;
    vector<BFSFailedDelegateSignature>  bfs_failed_delegates_;
};

class WeightedGraph {
public:
    using PosType = size_t;
    using WeightType = int;
    using DistanceType = size_t;
public:
    struct Edge {
        using PosType = WeightedGraph::PosType;
        using WeightType = WeightedGraph::WeightType;
        Edge(const PosType& is_pos, const PosType& ie_pos, const WeightType& iweight)
            : s_pos(is_pos), e_pos(ie_pos)
            , weight(iweight)
        {}
        PosType s_pos, e_pos;
        WeightType weight;
    };


public:
    struct DelegateSignatures {
        using PosType = WeightedGraph::PosType;
        using EdgeType = WeightedGraph::Edge;
    public:
        using SearchSetting  = function<void(const PosType& s_pos, const PosType& e_pos)>;
        using SearchVisiting = function<void(const EdgeType& edge)>;
    };
    enum class SearchState {
        Failed, Success
    };
    struct SearchData {
    public:
        using PosType      = WeightedGraph::PosType;
        using WeightType   = WeightedGraph::WeightType;
        using DistanceType = WeightedGraph::DistanceType;
        using SearchState  = WeightedGraph::SearchState;

    public:
        SearchData(const PosType& is_pos, const PosType& ie_pos, const WeightedGraph& graph)
            : s_pos    (is_pos)
            , e_pos    (ie_pos)
            , state    (SearchState::Failed)
            , distance (numeric_limits<DistanceType>::max())
            , distances(graph.size_v(), numeric_limits<DistanceType>::max())
            , visited  (graph.size_v(), false)
            , pparents (graph.size_v(), numeric_limits<PosType>::max())
        {
            // Initialize Search Data
            visited[s_pos] = true;
            distances[s_pos] = 0;
            pparents[s_pos] = s_pos;
        }
        inline bool IsValid() const {
            return state == SearchState::Success ? true : false;
        }

    public:
        vector<PosType> path() const {
            vector<PosType> ret;
            auto c_pos = e_pos;
            ret.push_back(c_pos);
            while (true) {
                const auto& p_pos = pparents[c_pos];
                if (p_pos == c_pos)
                    break;
                ret.push_back(p_pos);
                c_pos = p_pos;
            }
            reverse(ret.begin(), ret.end());
            return ret;
        };
    public:        
        void Print() const {
            cout << ">> Search Data from " << s_pos << " to " << e_pos << '\n';
            if (!IsValid()) {
                cout << "\t> Search Failed.";
                return;
            }
            cout << "\t> Search Success:\n";
            cout << "\t\t> Distance: " << distance << '\n';
            cout << "\t\t> Shortest Path: ";
            for (const auto& pos: path())
                cout << pos << " ";
            cout << '\n';
        }
    public:
        SearchState state;
        PosType s_pos, e_pos;
        DistanceType distance;
        vector<DistanceType> distances;
        vector<PosType> pparents;
        vector<bool> visited;
    };
    enum class SearchMethod {
        Dijkstra, BellmanFord
    };

public:
    WeightedGraph(const size_t& isize_v)
        : adj_lists_(isize_v, vector<Edge>())
    {}
    SearchData GetShortestPath(const PosType& s_pos, const PosType& e_pos, const SearchMethod& method) {
        OnSearchStart(s_pos, e_pos);
        SearchData data(s_pos, e_pos, *this);
        switch(method) {
            case SearchMethod::Dijkstra:
                BFS_Dijkstra(data);
                break;
            default:
                break;
        }
        return data;
    }
    void BFS_Dijkstra(SearchData& out_data) const {
        auto& [
            state, 
            s_pos, e_pos, 
            distance, distances, 
            pparents, visited
        ] = out_data;

        queue<PosType> to_visit;
        to_visit.push(s_pos);

        while (!to_visit.empty()) {
            const auto c_pos = to_visit.front();
            to_visit.pop();

            for (const auto& adj_pos: GetAdjacentPoses(c_pos)) {
            }
        }
    }
    void GetAdjacentPoses(const PosType& pos) const {
    }

public:
    inline size_t size_v() const {
        return adj_lists_.size();
    }

public:
    void AddEdge(const PosType& s_pos, const PosType& e_pos, const WeightType& weight) {
        assert(s_pos < size_v() && e_pos < size_v());
        adj_lists_[s_pos].push_back(Edge(s_pos, e_pos, weight));
    }

public:
    void PrintList() const {
        for (size_t v = 0; v < size_v(); ++v) {
            cout << v << " | ";
            for (const auto& [s_pos, e_pos, weight]: adj_lists_[v])
                cout << e_pos << "[" << weight << "] ";
            cout << '\n';
        }
    }

private:
    vector< vector<Edge> > adj_lists_;

private:
    void OnSearchStart   (DelegateSignatures::SearchSetting::first_argument_type s_pos, DelegateSignatures::SearchSetting::second_argument_type e_pos) const {
        for (const auto& delegate: search_start_delegates_)
            delegate(s_pos, e_pos);
    }
    void OnSearchVisiting(DelegateSignatures::SearchVisiting::argument_type edge) const {
        for (const auto& delegate: search_visiting_delegates_)
            delegate(edge);
    }
    void OnSearchSuccess (DelegateSignatures::SearchSetting::first_argument_type s_pos, DelegateSignatures::SearchSetting::second_argument_type e_pos) const {
        for (const auto& delegate: search_success_delegates_)
            delegate(s_pos, e_pos);
    }
    void OnSearchFailed  (DelegateSignatures::SearchSetting::first_argument_type s_pos, DelegateSignatures::SearchSetting::second_argument_type e_pos) const {
        for (const auto& delegate: search_failed_delegates_)
            delegate(s_pos, e_pos);
    }
private:
    vector<DelegateSignatures::SearchSetting>  search_start_delegates_;
    vector<DelegateSignatures::SearchVisiting> search_visiting_delegates_;
    vector<DelegateSignatures::SearchSetting>  search_success_delegates_;
    vector<DelegateSignatures::SearchSetting>  search_failed_delegates_;
};
/*
auto main() -> int {
    Graph graph(5);
    const auto sd  = [](const Graph::PosType& s_pos, const Graph::PosType e_pos) { cout << "> Starting BFS from " << s_pos << " to " << e_pos << '\n'; };
    const auto vd  = [](const Graph::PosType& c_pos, const Graph::PosType v_pos) { cout << "\t> Visiting: " << c_pos << "->" << v_pos << '\n'; };
    const auto esd  = [](const Graph::PosType& s_pos, const Graph::PosType e_pos) { cout << "> BFS Successed from: " << s_pos << " to " << e_pos << '\n'; };
    const auto efd  = [](const Graph::PosType& s_pos, const Graph::PosType e_pos) { cout << "> BFS Failed from:" << s_pos << " to " << e_pos << '\n'; };

    graph.PushBFSStartDelegate(sd);
    graph.PushBFSVisitDelegate(vd);
    graph.PushBFSSuccessDelegate(esd);
    graph.PushBFSFailedDelegate(efd);

    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(2, 3);

    cout << "> Adj list of graph:\n";
    graph.PrintEdges();
    cout << '\n';

    const auto s_pos = 0;
    const auto e_pos = 3;
    const auto bdata = graph.BFS(s_pos, e_pos);
    cout << '\n';
    bdata.Print();

    return 0;
} 
*/

auto main() -> int {
    WeightedGraph wgraph(6); // 0, 1, 2, 3, 4, 5
    wgraph.AddEdge(0, 1, 10);
    wgraph.AddEdge(2, 3, 4);
    wgraph.AddEdge(0, 3, 4);
    wgraph.AddEdge(4, 5, 2);
    wgraph.AddEdge(3, 4, 20);
    wgraph.PrintList();

    return 0;
}
