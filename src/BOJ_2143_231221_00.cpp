// title: 백준 2143 백준 두 배열의 합 G3
// date: 2023-12-21 19:26
#define PS_DEBUG
#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Cache
{
public:
    Cache(const vector<int>& vec): 
        cache_(vec.size(), vector<int>(vec.size(), 0))
    {
        for (size_t i = 1; i < cache_.size(); ++i)
        {
            for (size_t j = i; j < cache_.size(); ++j)
            {
                if (i == j) 
                    cache_[i][j] = vec[j];
                else
                    cache_[i][j] = cache_[i][j - 1] + vec[j];
            }
        }
    }
    int get(size_t i, size_t j) const
    {
        return cache_[i][j];
    }
    inline size_t size_1d() const { return cache_.size(); };
#ifdef PS_DEBUG
    void Print() const
    {
        for (size_t i = 0; i < cache_.size(); ++i)
        {
            for (size_t j = 0; j < cache_.size(); ++j)
            {
                cout << cache_[i][j] << " ";
            }
            cout << '\n';
        }
        cout << '\n';
        return;
    }
#endif //PS_DEBUG
private:
    vector<vector<int>> cache_;
};

auto main() -> int
{
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr); cout.tie(nullptr);
    }

    int T; cin >> T; // [-1e9, 1e9]
    int n; cin >> n; // [1, 1e3]
    vector<int> A(n + 1, 0); for_each(++A.begin(), A.end(), [](auto& e) { cin >> e; });
    int m; cin >> m; // [1, 1e3]
    vector<int> B(m + 1, 0); for_each(++B.begin(), B.end(), [](auto& e) { cin >> e; });

    Cache cA(A);
    Cache cB(B);

#ifdef PS_DEBUG
    cout << "Cache A:\n";
    cA.Print();
    cout << "Cache B:\n";
    cB.Print();
#endif //PS_DEBUG

    const auto& min_cache = min(cA, cB, [](const auto& l, const auto& r){ return l.size_1d() <= r.size_1d(); });
    const auto& max_cache = (&min_cache == &cA ? cB : cA);

#ifdef PS_DEBUG
    cout << "MinCache A:\n";
    min_cache.Print();
    cout << "MaxCache B:\n";
    max_cache.Print();
#endif //PS_DEBUG

    int target_count = 0;

    for (size_t i = 1; i < min_cache.size_1d(); ++i)
    {
        for (size_t j = i; j < min_cache.size_1d(); ++j)
        {
            const auto val = min_cache.get(i, j);

            if (val > T) break;

            const auto offset = T - val;

            for (size_t mi = 1; mi < max_cache.size_1d(); ++mi)
            {
                for (size_t mj = mi; mj < max_cache.size_1d(); ++mj)
                {
                    const auto mval = max_cache.get(mi, mj);

                    if (mval > offset) break;
                    if (mval == offset) ++target_count;
                }
            }

        }
    }

    cout << target_count << "\n";

    return 0;
}