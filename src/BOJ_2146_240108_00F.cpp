// title: 백준 2146 다리 만들기 G3
// date:  15:38 18:33 Failed (반례 통과 못함)
/*
통과 못한 반례:
5
1 0 0 0 1
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 1 0 0 1
*/
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#define SEA 0

using namespace std;

#include <vector>

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
    Map(const size_t& map_size_v, const size_t& map_size_h): labels_(map_size_v, vector<int>(map_size_h, SEA)), raw_(labels_) {
        // Input
        for (size_t v = 0; v < size_v(); ++v)
            for (size_t h = 0; h < size_h(); ++h)
                cin >> raw_[v][h];

        // Labeling grounds
        size_t ground_label = SEA;
        static vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (visited[v][h])
                    continue;
                if (raw_[v][h] == SEA)
                    continue;

                ground_label++; 
                queue<Pos2> to_visit; to_visit.push(Pos2(v, h));
                visited[to_visit.front().v][to_visit.front().h] = true;
                labels_[to_visit.front().v][to_visit.front().h] = ground_label;

                while (!to_visit.empty()) {
                    const auto cvisit = to_visit.front(); to_visit.pop();

                    for (const auto& adj_pos: GetAdjacentPoses(cvisit)) {
                        if (visited[adj_pos.v][adj_pos.h])
                            continue;
                        
                        if (raw_[adj_pos.v][adj_pos.h] == SEA)
                            continue;

                        labels_[adj_pos.v][adj_pos.h] = ground_label;
                        visited[adj_pos.v][adj_pos.h] = true;
                        to_visit.push(adj_pos);
                    }
                }
            }
        }

    }
private:
    vector<Pos2> GetAdjacentPoses(const Pos2& pivot) const {
        vector<Pos2> ret;
        for (const auto& offset: Pos2::GetOffsets()) {
            const auto tpos = offset + pivot;
            if (tpos.IsInBound(Pos2(0, 0), Pos2(size_v(), size_h())))
                ret.push_back(tpos);
        }
        return ret;
    }
    vector<Pos2> GetAdjacentPosesWithSea(const Pos2& pivot) const {
        vector<Pos2> ret;
        bool has_sea = false;;
        for (const auto& offset: Pos2::GetOffsets()) {
            const auto tpos = offset + pivot;
            if (!tpos.IsInBound(Pos2(0, 0), Pos2(size_v(), size_h())))
                continue;
            has_sea = (labels_[tpos.v][tpos.h] == SEA);
            ret.push_back(tpos);
        }
        if (has_sea)
            return ret;
        else
            return vector<Pos2> {};
    }
    inline size_t size_v() const {
        return labels_.size();
    }
    inline size_t size_h() const {
        return labels_.front().size();
    }
public:
    size_t GetShortestBridgeLength() {
        int min_bridge_length = numeric_limits<int>::max();
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                const auto& pivot_ground_label = labels_[v][h];
                if (pivot_ground_label == SEA)
                    continue;

                queue<Pos2> to_visit;
                vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
                vector<vector<int>> distance(size_v(), vector<int>(size_h(), numeric_limits<int>::max()));

                to_visit.push(Pos2(v, h));
                visited[to_visit.front().v][to_visit.front().h] = true;
                distance[to_visit.front().v][to_visit.front().h] = 0;

                bool found_bridge = false;
                while (!to_visit.empty()) {
                    const auto cvisit = to_visit.front(); to_visit.pop();
                    for (const auto& adj_pos: GetAdjacentPosesWithSea(cvisit)) {
                        if (visited[adj_pos.v][adj_pos.h])
                            continue;
                        visited[adj_pos.v][adj_pos.h] = true;
                        distance[adj_pos.v][adj_pos.h] = distance[cvisit.v][cvisit.h] + 1;
                        to_visit.push(adj_pos);

                        const auto& adj_label = labels_[adj_pos.v][adj_pos.h];
                        // If Adjacent tile is not Sea *and* has different ground label, then it is bridge
                        if (adj_label == pivot_ground_label)
                            continue;
                        if (adj_label == SEA)
                            continue;
                        // Not Sea, Different Ground
                        const auto& cbridge_cells = distance[cvisit.v][cvisit.h];

                        #ifdef PS_DEBUG
                        const auto cbridge_start = Pos2(v, h);
                        const auto cbridge_end = adj_pos;
                        auto it = find_if(bridges_.begin(), bridges_.end(), [&cbridge_start, &cbridge_end](const auto& cinfo){ 
                            return cinfo.start_pos == cbridge_start && cinfo.end_pos == cbridge_end || cinfo.start_pos == cbridge_end && cinfo.end_pos == cbridge_start;
                        });
                        if (it == bridges_.end())
                            bridges_.push_back(BridgeInfo(Pos2(v, h), adj_pos, cbridge_cells));
                        #endif //PS_DEBUG 

                        #ifdef PS_DEBUG
                        cout << "> Distance Test: \n";
                        for (size_t v = 0; v < size_v(); ++v) {
                            for (size_t h = 0; h < size_h(); ++h) {
                                if (Pos2(v, h) == adj_pos)
                                    cout << 'E';
                                else if (distance[v][h] >= size_v())
                                    cout << '.';
                                else if (distance[v][h] == 0)
                                    cout << 'S';
                                else
                                    cout << distance[v][h];
                            }
                            cout << '\n';
                        }
                        cout << '\n';
                        #endif //PS_DEBUG 
                        min_bridge_length = min(min_bridge_length, cbridge_cells);
                    }
                    /*
                    if (found_bridge)
                        break;
                    */
                }
            }
        }
        #ifdef PS_DEBUG
        sort(bridges_.begin(), bridges_.end(), [](const auto& left, const auto& right) {return left.cell_cnt <= right.cell_cnt; });
        #endif //PS_DEBUG 
        return (size_t)min_bridge_length - 1;
    }
private:
    vector<vector<int>> labels_;
    vector<vector<int>> raw_;
#ifdef PS_DEBUG
private:
    struct BridgeInfo {
        BridgeInfo(const Pos2& start_pos, const Pos2& end_pos, const size_t& cell_cnt): start_pos(start_pos), end_pos(end_pos), cell_cnt(cell_cnt) {};
        Pos2 start_pos;
        Pos2 end_pos;
        size_t cell_cnt;
    };
    vector<BridgeInfo> bridges_;
public:
    void PrintLabels() const {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                const auto& clabel = labels_[v][h];
                switch(clabel) {
                    case SEA:
                        cout << '.';
                        break;
                    default:
                        cout << clabel;
                        break;
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
    void PrintBridges() const {
        for (const auto& cbinfo: bridges_) {
            cout << "> Bridge Cell Count: " << cbinfo.cell_cnt << '\n';
            for (size_t v = 0; v < size_v(); ++v) {
                for (size_t h = 0; h < size_h(); ++h) {
                    char cdel_s = ' '; char cdel_e = ' ';
                    const auto cpos = Pos2(v, h);
                    if (cpos == cbinfo.start_pos || cpos == cbinfo.end_pos) {
                        cdel_s = '[';
                        cdel_e = ']';
                    }
                    cout << cdel_s << labels_[v][h] << cdel_e;
                }
                cout << '\n';
            }
            cout << "\n";
        }
        cout << "\n";
    }
#endif //PS_DEBUG 
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; const int& map_size = N;
    Map map(N, N);
    cout << map.GetShortestBridgeLength();

/*
    #ifdef PS_DEBUG
    cout << '\n';
    map.PrintBridges();
    #endif //PS_DEBUG 
    */
    
    return 0;
}