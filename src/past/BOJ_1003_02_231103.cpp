///@date 2023-11-03

#include <iostream>
#include <vector>
using namespace std;

typedef int ZeroCount;
typedef int OneCount;

class FibCache
{
public:
    ///@short 기본 생성자는 fib(0), fib(1) 에 대해서만 저장
    FibCache(): o_c(2, 0), z_c(2, 0), max_cache(1) 
    {
        this->o_c[0] = 1;
        this->o_c[1] = 0;

        this->z_c[0] = 0;
        this->z_c[1] = 1;
        return;
    }
    
    ZeroCount get_zero_count(const int& N)
    {
        if (this->has_no_cache(N))
            this->flourish_cache(N);
        return this->o_c[N];
    }
    OneCount get_one_count(const int& N)
    {
        if (this->has_no_cache(N))
            this->flourish_cache(N);
        return this->z_c[N];
    }
private:
    bool has_no_cache(const int& N) const
    {
        return N > max_cache;
    }
    void flourish_cache(const int& N)
    {
        for (size_t i = this->max_cache + 1; i <= N; ++i)
        {
            this->o_c.push_back(this->o_c[i - 1] + this->o_c[i - 2]);
            this->z_c.push_back(this->z_c[i - 1] + this->z_c[i - 2]);
        }
        this->max_cache = N;
        return;
    }
private:
    vector<OneCount> o_c;
    vector<ZeroCount> z_c;
    int max_cache;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int T; cin >> T;
    FibCache fc;
    for (size_t i = 0; i < T; ++i)
    {
        int N; cin >> N;
        cout << fc.get_zero_count(N) << " " << fc.get_one_count(N) << '\n';
    }

    return 0;
}
