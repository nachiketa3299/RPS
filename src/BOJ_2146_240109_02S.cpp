// title: 백준 다리만들기 2146 G3
// date: 2024-01-09T16:15 17:56 (100)

#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;


struct Pos2 {
    Pos2(): v(0), h(0) {}
    Pos2(const int& v, const int& h): v(v), h(h) {}
    Pos2(const Pos2& pos): v(pos.v), h(pos.h) {}
    static std::vector<Pos2> GetOffsets() {
        return std::vector<Pos2> { Pos2(-1, 0), Pos2(+1, 0), Pos2(0, -1), Pos2(0, +1) };
    }
    Pos2 operator+(const Pos2& other) const {
        return Pos2(v + other.v, h + other.h);
    }
    bool operator==(const Pos2& other) const {
        return v == other.v && h == other.h;
    }
    inline bool IsInBound(const Pos2& min_vh, const Pos2& max_vh) const {
        return IsInVBound(min_vh.v, max_vh.v) && IsInHBound(min_vh.h, max_vh.h);
    }
    inline bool IsInVBound(const int& min_v, const int& max_v) const {
        return min_v <= v && v < max_v;
    }
    inline bool IsInHBound(const int& min_h, const int& max_h) const {
        return min_h <= h && h < max_h;
    }
    int v, h;
};

class Map {
public:
    using LabelType = int;
public:
    Map(const size_t& map_size_v, const size_t& map_size_h):
        raw_inputs_(map_size_v, vector<int>(map_size_h, 0)),
        labels_(map_size_v, vector<LabelType>(map_size_h, 0)) {
        // Input
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h)
                cin >> raw_inputs_[v][h];
        }

        // using BFS to label each ground with number and save it to labels
        LabelType ground_label = 0;
        vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (raw_inputs_[v][h] == kMapLabel_Sea)
                    continue;
                if (visited[v][h])
                    continue;
                ground_label++;            
                queue<Pos2> to_visit; to_visit.push(Pos2(v, h));
                visited[to_visit.front().v][to_visit.front().h] = true;
                labels_[to_visit.front().v][to_visit.front().h] = ground_label;

                while (!to_visit.empty()) {
                    const auto cvisit = to_visit.front(); to_visit.pop();
                    for (const auto& adj_pos: GetAdjacentCells(cvisit)) {
                        if (visited[adj_pos.v][adj_pos.h])
                            continue;
                        visited[adj_pos.v][adj_pos.h] = true;

                        if (raw_inputs_[adj_pos.v][adj_pos.h] == kMapLabel_Sea) 
                            continue;
                        labels_[adj_pos.v][adj_pos.h] = ground_label;
                        to_visit.push(adj_pos);
                    }
                }
            }
        }
    }
    vector<Pos2> GetAdjacentCells(const Pos2& pivot_cell) const {
        vector<Pos2> ret;
        for (const auto& offset: Pos2::GetOffsets()) {
            const auto& tpos = pivot_cell + offset;
            if (!tpos.IsInBound(Pos2(0, 0), Pos2(size_v(), size_h())))
                continue;
            ret.push_back(tpos);
        }
        return ret;
    }
    inline size_t size_v() const {
        return labels_.size();
    }
    inline size_t size_h() const {
        return labels_.front().size();
    }
public:
    size_t GetShortestBridgeLength() {
        int shortest_bridge_length = numeric_limits<int>::max();
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (labels_[v][h] == kMapLabel_Sea)
                    continue;
                const auto cg_pos = Pos2(v, h);
                // Test if this is inner ground (not adjacent with sea)
                const auto cg_adj_poses = GetAdjacentCells(cg_pos);
                const auto is_inner_ground = find_if(cg_adj_poses.cbegin(), cg_adj_poses.cend(), 
                    [this](const auto& pos){ return labels_[pos.v][pos.h] == kMapLabel_Sea; }) == cg_adj_poses.cend();
                if (is_inner_ground)
                    continue;
                
                queue<Pos2> to_visit;
                vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
                vector<vector<int>> distance(size_v(), vector<int>(size_h(), numeric_limits<int>::max()));

                to_visit.push(cg_pos);
                visited[to_visit.front().v][to_visit.front().h] = true;
                distance[to_visit.front().v][to_visit.front().h] = 0;

                #ifdef PS_DEBUG
                vector<vector<Pos2>> bridge_path_parent(size_v(), vector<Pos2>(size_h(), Pos2(0, 0)));
                bridge_path_parent[cg_pos.v][cg_pos.h] = cg_pos;
                #endif //PS_DEBUG 

                const auto& cg_label = labels_[v][h];
                bool found_bridge = false;
                while (!to_visit.empty()) {
                    const auto cvisit = to_visit.front(); to_visit.pop();

                    for (const auto& adj_pos: GetAdjacentCells(cvisit)) {
                        if (visited[adj_pos.v][adj_pos.h])
                            continue;
                        visited[adj_pos.v][adj_pos.h] = true;

                        const auto& adj_label = labels_[adj_pos.v][adj_pos.h];
                        if (adj_label == cg_label)
                            continue;

                        to_visit.push(adj_pos);
                        distance[adj_pos.v][adj_pos.h] = distance[cvisit.v][cvisit.h] + 1;

                        #ifdef PS_DEBUG
                        bridge_path_parent[adj_pos.v][adj_pos.h] = cvisit;
                        #endif //PS_DEBUG 

                        if (adj_label != cg_label && adj_label != kMapLabel_Sea) {
                            found_bridge = true;
                            shortest_bridge_length = min(shortest_bridge_length, distance[cvisit.v][cvisit.h]);

                            #ifdef PS_DEBUG
                            bridges_.push_back(make_pair(adj_pos, bridge_path_parent));
                            #endif //PS_DEBUG 
                        }
                    }
                    if (found_bridge)  
                        break;
                }
            }
        }
        return shortest_bridge_length;
    }
#ifdef PS_DEBUG
public:
    void PrintGroundLabels() const {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                const auto& clabel = labels_[v][h];
                switch(clabel) {
                    case kMapLabel_Sea:
                        cout << '.';
                        break;
                    default:
                        cout << clabel;
                        break;
                }
            }
            cout << '\n';
        }
        cout << "\n\n";
    }
    void PrintAllBridges() const {
        vector<vector<Pos2>> rbridges;

        for (const auto& bpair: bridges_) {
            const auto& last_pos = bpair.first;
            const auto& pos_tree = bpair.second;

            auto cchild = last_pos;
            vector<Pos2> trbridge;
            trbridge.push_back(cchild);

            while (true) {
                const auto& cparent = pos_tree[cchild.v][cchild.h];
                if (cparent == cchild)
                    break;
                trbridge.push_back(cparent);
                cchild = cparent;
            }
            rbridges.push_back(trbridge);
        }
        vector<vector<tuple<char, char, char>>> printer (size_v(), vector<tuple<char, char, char>>(size_h(), make_tuple(' ', ' ', ' ')));
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                const auto& clabel = labels_[v][h];
                switch(clabel) {
                    case kMapLabel_Sea:
                        get<1>(printer[v][h]) = '.';
                        break;
                    default:
                        get<1>(printer[v][h]) = (char)(clabel + 48);
                        break;
                }
            }
        }
        for (const auto& rbridge_poses: rbridges) {
            auto cprinter(printer);

            for (int i = 0; i < rbridge_poses.size(); ++i) {
                const auto& cpos = rbridge_poses[i];
                if (i == 0) {
                    // End pos
                    get<0>(cprinter[cpos.v][cpos.h]) = '[';
                    get<2>(cprinter[cpos.v][cpos.h]) = ']';
                }
                else if (i == rbridge_poses.size() - 1) {
                    // Start pos
                    get<0>(cprinter[cpos.v][cpos.h]) = '(';
                    get<2>(cprinter[cpos.v][cpos.h]) = ')';
                }
                else {
                    get<0>(cprinter[cpos.v][cpos.h]) = '{';
                    get<1>(cprinter[cpos.v][cpos.h]) = '=';
                    get<2>(cprinter[cpos.v][cpos.h]) = '}';
                }
            }

            cout << ">> Bridge Length: " << rbridge_poses.size() - 2 << '\n';
            for (size_t v = 0; v < size_v(); ++v) {
                for (size_t h = 0; h < size_h(); ++h) {
                    const auto& ct = cprinter[v][h];
                    cout << get<0>(ct) << get<1>(ct) << get<2>(ct);
                }
                cout << '\n';
            }
            cout << '\n';
        }
    }
#endif //PS_DEBUG 
private:
    vector<vector<int>> raw_inputs_;
    vector<vector<LabelType>> labels_;
    static constexpr LabelType kMapLabel_Sea = 0;
    #ifdef PS_DEBUG
    vector< pair<Pos2, vector<vector<Pos2>>> > bridges_;
    #endif //PS_DEBUG 
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N;
    const int& map_size_v = N;
    const int& map_size_h = N;

    Map map(map_size_v, map_size_h);

    #ifdef PS_DEBUG
    cout << "> Ground Labels :\n";
    map.PrintGroundLabels();
    #endif //PS_DEBUG 

    cout << map.GetShortestBridgeLength();

    #ifdef PS_DEBUG
    cout << "\n> Bridges: \n";
    map.PrintAllBridges();
    #endif //PS_DEBUG 


    return 0;
}