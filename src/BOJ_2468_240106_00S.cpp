// title:  백준 2468 안전 영역 S1
// date: 2024-01-06 13:41 14:40
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

using namespace std;

struct Pos2 {
    Pos2(const size_t& iv = 0, const size_t& ih = 0): v(iv), h(ih) {};
    Pos2 operator==(const Pos2& other) const {
        return v == other.v && h == other.h;
    }
    Pos2 operator+(const Pos2& other) const {
        return Pos2(v + other.v, h + other.h);
    }
    inline bool IsInBound(const size_t& max_vh) const {
        return IsInBound(Pos2(0, 0), Pos2(max_vh, max_vh));
    }
    inline bool IsInBound(const Pos2& min_vh, const Pos2& max_vh) const {
        const bool is_in_v_bound = min_vh.v <= v && v < max_vh.v;
        const bool is_in_h_bound = min_vh.h <= h && h < max_vh.h;
        return is_in_v_bound && is_in_h_bound;
    }
    static vector<Pos2> GetOffsets() {
        return vector<Pos2> { Pos2(-1, 0), Pos2(+1, 0), Pos2(0, -1), Pos2(0, +1) };
    }
public:
    int v, h;
};

template <typename T>
T& GetRefAt(vector<vector<T>>& vec, const Pos2& pos) {
    return vec[pos.v][pos.h];
}

class HeightMap {
public:
    HeightMap(const size_t& map_size_v, const size_t& map_size_h): heights_(map_size_v, vector<int>(map_size_h, 0)), max_height_(numeric_limits<int>::min()) {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                cin >> heights_[v][h];
                max_height_ = max(max_height_, heights_[v][h]);
            }
        }
    }
    vector<Pos2> GetAdjacentPoses(const Pos2& pivot) const {
        vector<Pos2> ret;
        for (const auto& offset: Pos2::GetOffsets()) {
            const auto candid_pos = offset + pivot;
            if (candid_pos.IsInBound(size_v()))
                ret.push_back(candid_pos);
        }
        return ret;
    }
    inline size_t size_v() const { 
        return heights_.size(); 
    }
    inline size_t size_h() const { 
        return heights_.front().size(); 
    }
    inline size_t max_height() const {
        return max_height_;
    }
public:
    int GetAreaCountWithRainMeter(const size_t& rain_height) {
        vector<vector<bool>> visited(size_v(), vector<bool>(size_h(), false));
        int area_count = 0;

        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                auto& cheight = heights_[v][h];
                if (!(cheight > rain_height))
                    continue;
                
                if (visited[v][h])
                    continue;

                queue<Pos2> to_visit;
                to_visit.push(Pos2(v, h)); visited[v][h] = true;
                while (!to_visit.empty()) {
                    const auto cvisit = to_visit.front(); to_visit.pop();
                    for (const auto& adj_pos: GetAdjacentPoses(cvisit)) {
                        if (visited[adj_pos.v][adj_pos.h])
                            continue;
                        if (!(heights_[adj_pos.v][adj_pos.h] > rain_height))
                            continue;
                        
                        visited[adj_pos.v][adj_pos.h] = true;
                        to_visit.push(adj_pos);
                    }
                }
                area_count++;
            }
        }
        #ifdef PS_DEBUG
        cout << "> Height: " << rain_height << '\n';
        cout << "> area count: " << area_count << '\n';
        PrintWithHeight(rain_height);
        #endif //PS_DEBUG 
        return area_count;
    }
#ifdef PS_DEBUG
public:
    void Print() const {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                cout << heights_[v][h];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    void PrintWithHeight(const size_t& height) const {
        for (size_t v = 0; v < size_v(); ++v) {
            for (size_t h = 0; h < size_h(); ++h) {
                auto& cheight = heights_[v][h];
                if (cheight > height)
                    cout << heights_[v][h];
                else
                    cout << '.';
            }
            cout << '\n';
        }
        cout << '\n';
    }
#endif //PS_DEBUG 
private:
    vector<vector<int>> heights_;
    int max_height_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int N; cin >> N; // [2, 100]
    HeightMap h_map(N, N);

    int area_count_max = numeric_limits<int>::min();
    for (size_t rain_height = 0; rain_height <= h_map.max_height(); ++rain_height) {
        area_count_max = max(area_count_max, h_map.GetAreaCountWithRainMeter(rain_height));
    }
    cout << area_count_max;

    return 0;
}