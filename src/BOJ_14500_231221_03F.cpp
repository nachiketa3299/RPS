/// 2023-12-21 16:04

#define PS_DEBUG

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

struct Pos
{
    Pos(int x, int y): x_(x), y_(y) {};
    inline void invert_x() { x_ = -x_; return; };
    inline void invert_y() { y_ = -y_; return; };
    inline void rotate(const Pos& base = Pos{0, 0})
    {
        const auto tx = x_; const auto ty = y_;
        x_ = 0 * (tx - base.x_) - 1 * (ty - base.y_) + base.x_;
        y_ = 1 * (tx - base.x_) + 0 * (ty - base.y_) + base.y_;
        return;
    }
    bool operator==(const Pos& right)
    {
        return x_ == right.x_ && y_ == right.y_;
    }
    int x_{0}, y_{0};
};

class Tetro
{
public:
    Tetro(const Pos& root, const Pos& p1, const Pos& p2, const Pos& p3):
        coords_{root, p1, p2, p3}
    { calibrate_coords(); };
    Tetro(const array<Pos, 4>& coords):
        coords_(coords)
    { calibrate_coords(); };
private:
    void calibrate_coords()
    {
        auto mx = min_element(coords_.begin(), coords_.end(), [](const auto& l, const auto& r) { return l.x_ < r.x_; })->x_;
        auto my = min_element(coords_.begin(), coords_.end(), [](const auto& l, const auto& r) { return l.y_ < r.y_; })->y_;
        if (mx < 0) 
            for_each(coords_.begin(), coords_.end(), [&mx](auto& p) { p.x_ += -mx; });
        if (my < 0) 
            for_each(coords_.begin(), coords_.end(), [&my](auto& p) { p.y_ += -my; });
    }

public:
    Tetro get_flipped() const
    {
        auto n_coords = coords_;
        for_each(n_coords.begin(), n_coords.end(), [](auto& p){ p.invert_x(); });
        return Tetro(n_coords);
    }

    vector<Tetro> get_rotated() const
    {
        vector<Tetro> ret; ret.push_back(*this);
        auto n_coords = coords_;
        for (size_t i = 1; i < 4; ++i)
        {
            for_each(n_coords.begin(), n_coords.end(), [](auto& p){ p.rotate(); });
            ret.push_back(Tetro(n_coords));
        }
        return ret;
    }

    inline array<Pos, 4> coords() const { return coords_; };
    inline Pos root() const { return coords_[0]; };

    bool operator==(const Tetro& right)
    {
        for (size_t i = 0; i < coords_.size(); ++i)
        {
            if (!(coords_[i] == right.coords_[i]))
                return false;
        }
        return true;
    }

private:
    array<Pos, 4> coords_;
};

class Paper
{
public:
    Paper(const vector<vector<int>>& paper): 
        paper_(paper) 
    {};

    vector<int> get_tetro_scores(const Tetro& tetro)
    {
        vector<int> scores;
        for (int dx = 0; dx < x_size(); ++dx)
        {
            for (int dy = 0; dy < y_size(); ++dy)
            {
                int tscore = 0;
                bool invalid_score = false;

                for (const auto& coord: tetro.coords())
                {
                    auto fx = dx + coord.x_;
                    auto fy = dx + coord.y_;

                    bool x_out_bound = !(0 <= fx && fx < x_size());
                    bool y_out_bound = !(0 <= fy && fy < y_size());

                    if (x_out_bound || y_out_bound)
                    {
                        invalid_score = true;
                        break;
                    }

                    tscore += paper_[fy][fx];
                }

                if (!invalid_score) 
                    scores.push_back(tscore);
            }
        }
        return scores;
    }
    inline size_t x_size() { return paper_.front().size(); };
    inline size_t y_size() { return paper_.size(); };
public:
    vector<vector<int>> paper_;
};

int main()
{
    int N; cin >> N;
    int M; cin >> M;
    vector<vector<int>> tpaper(N, vector<int>(M, 0));

    for (auto& l: tpaper)
        for (auto& e: l)
            cin >> e;

    Paper paper(tpaper);

    array<Tetro, 5> tetros 
    { 
        Tetro({0, 0}, {1, 0}, {2, 0}, {3, 0}),
        Tetro({0, 0}, {1, 0}, {1, 1}, {0, 1}),
        Tetro({0, 0}, {0, 1}, {0, 2}, {1, 2}),
        Tetro({0, 0}, {0, 1}, {1, 1}, {1, 2}),
        Tetro({0, 0}, {0, 1}, {0, 2}, {1, 1})
    };

    vector<int> scores;

    for (auto& tetro: tetros)
    {
        vector<Tetro> targets;
        targets.push_back(tetro);
        targets.push_back(tetro.get_flipped());

        auto nr = tetro.get_rotated();
        auto fr = tetro.get_flipped().get_rotated();

        targets.insert(targets.end(), nr.begin(), nr.end());
        targets.insert(targets.end(), fr.begin(), fr.end());

        targets.erase(unique(targets.begin(), targets.end()), targets.end());

        for (const auto& target: targets)
        {
            auto tscores = paper.get_tetro_scores(target);
            scores.insert(scores.end(), tscores.begin(), tscores.end());
        }
    }

    sort(scores.begin(), scores.end(), greater<int>());

    cout << scores.front() << '\n';

    return 0;
}