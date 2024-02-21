// title: 백준 2146 다리 만들기 G3
// date:  18:34 19:05 (stop)
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define MAP_LABEL_SEA 0

using namespace std;

struct Pos2 {
    Pos2(): v(0), h(0) {}
    Pos2(const int& v, const int& h): v(v), h(h) {}
    Pos2(const Pos2& pos): v(pos.v), h(pos.h) {}
    static vector<Pos2> GetOffsets() {
        return vector<Pos2> { Pos2(-1, 0), Pos2(+1, 0), Pos2(0, -1), Pos2(0, +1) };
    }
    Pos2 operator+(const Pos2& other) const {
        return Pos2(v + other.v, h + other.h);
    }
    bool operator==(const Pos2& other) const {
        return v == other.v && h == other.h;
    }
    inline bool IsInBound(const Pos2& min_vh, const Pos2& max_vh) const {
        return IsInMinBound(min_vh) && IsInMaxBound(max_vh);
    }
    inline bool IsInMinBound(const Pos2& min_vh) const {
        return min_vh.v <= v && min_vh.h <= h;
    }
    inline bool IsInMaxBound(const Pos2& max_vh) const {
        return v < max_vh.v && h < max_vh.h;
    }
    int v, h;
};

class Map {
public:
    Map(const size_t& map_size_v, const size_t& map_size_h): 
        raw_input_(map_size_v, vector<int>(map_size_h, MAP_LABEL_SEA)), 
        labels_(map_size_v, vector<int>(map_size_h, MAP_LABEL_SEA)) 
    {
        // Input
        for (size_t v = 0; v < size_v(); ++v)
            for (size_t h = 0; h < size_h(); ++h)
                cin >> raw_input_[v][h];
        
        // Labeling Grounds
        vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        int ground_label = MAP_LABEL_SEA;
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                if (visited[v][h])
                    continue;
                if (raw_input_[v][h] == MAP_LABEL_SEA)
                    continue;
                    
                // Found Ground
                ground_label++;

                const auto cground_pos = Pos2(v, h);
                queue<Pos2> to_visit; to_visit.push(cground_pos);

                visited[to_visit.front().v][to_visit.front().h] = true; // init
                labels_[to_visit.front().v][to_visit.front().h] = ground_label; //init

                while (!to_visit.empty()) {
                    const auto cvisit = to_visit.front(); to_visit.pop();
                    for (const auto& adj_pos: GetAdjacentPoses(cvisit)) {
                        if (visited[adj_pos.v][adj_pos.h])
                            continue;
                        if (raw_input_[adj_pos.v][adj_pos.h] == MAP_LABEL_SEA)
                            continue;
                        to_visit.push(adj_pos);
                        visited[adj_pos.v][adj_pos.h] = true;
                        labels_[adj_pos.v][adj_pos.h] = labels_[cvisit.v][cvisit.h];
                    }
                }
            }
        }
    }
    vector<Pos2> GetAdjacentPoses(const Pos2& pivot) const {
        vector<Pos2> ret;
        for (const auto& offset: Pos2::GetOffsets()) {
            const auto tpos = offset + pivot;
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
    vector<Pos2> GetAdjacentPosesWithSea(const Pos2& pivot) const {
        vector<Pos2> ret;
        bool has_sea = false;
        for (const auto& offset: Pos2::GetOffsets()) {
            const auto tpos = pivot + offset;
            if (!tpos.IsInBound(Pos2(0, 0), Pos2(size_v(), size_h())))
                continue;
            ret.push_back(tpos);
            if (labels_[tpos.v][tpos.h] == MAP_LABEL_SEA)
                has_sea = true; // Just turn on once. If there's no adjacent sea at all, then this'll be false
        }
        if (has_sea)
            return ret;
        else
            return vector<Pos2> {};
    }

    size_t GetShortestBridgeLength() {
        int min_bridge_length = numeric_limits<int>::max();
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                // Not a Sea?
                if (labels_[v][h] == MAP_LABEL_SEA)
                    continue;

                // Its middle of ground?
                const auto cground_pos = Pos2(v, h);
                const auto& adj_poses = GetAdjacentPosesWithSea(cground_pos);
                if (adj_poses.empty())
                    continue;
                const auto& cground_label = labels_[cground_pos.v][cground_pos.h];
                
                // Its in beach
                queue<Pos2> to_visit; 
                vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
                vector<vector<int>> distance(size_v(), vector<int>(size_h(), numeric_limits<int>::max()));

                to_visit.push(cground_pos);
                visited[to_visit.front().v][to_visit.front().h] = true; // init
                distance[to_visit.front().v][to_visit.front().h] = 0; // init

                bool found_bridge = false;
                while (!to_visit.empty()) {
                    const auto cvisit_pos = to_visit.front(); to_visit.pop();
                    for (const auto& adj_pos: GetAdjacentPoses(cvisit_pos)) {
                        if (visited[adj_pos.v][adj_pos.h])
                            continue;
                        visited[adj_pos.v][adj_pos.h] = true;
                        to_visit.push(adj_pos);

                        distance[adj_pos.v][adj_pos.h] = distance[cvisit_pos.v][cvisit_pos.h] + 1;

                        if (labels_[adj_pos.v][adj_pos.h] == MAP_LABEL_SEA)
                            continue; // Not even ground
                        if (labels_[adj_pos.v][adj_pos.h] == cground_label)
                            continue; // Ground, but Same
                        
                        // === NOT SEA && NOT SAME GROUND ===
                        found_bridge = true;
                        min_bridge_length = min(min_bridge_length, distance[cvisit_pos.v][cvisit_pos.h]);
                    }
                    // If Found, it is shortest (cuz its BFS)
                    if (found_bridge)
                        break;
                }
            }
        }
        return min_bridge_length;
    }
private:
    vector<vector<int>> raw_input_;
    vector<vector<int>> labels_;

#ifdef PS_DEBUG
public:
    void PrintLabels() const {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                const auto& clabel = labels_[v][h];
                if (clabel == MAP_LABEL_SEA)
                    cout << '.';
                else
                    cout << clabel;
            }
            cout << '\n';
        }
        cout << '\n';
    }
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
    map.PrintLabels();
    #endif //PS_DEBUG 
    cout << map.GetShortestBridgeLength();
    return 0;
}