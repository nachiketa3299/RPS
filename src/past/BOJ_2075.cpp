#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
using llint = int;
using min_heap = greater<llint>;
using max_heap = less<llint>;
using pq = priority_queue<llint, vector<llint>, max_heap>;

int main(void) {
    int N; std::cin >> N; // N in [1, 1500] >> 225 00 00 
    vector<pq> pq_table(N);

    // (1) pq ¸¸µé±â
    for (auto& pq : pq_table) {
        for (size_t i = 0; i < N; ++i) {
            llint tdata; cin >> tdata;
            pq.push(tdata);
        }
    }

    // (2) 
    auto predicate = [](const pq& a, const pq& b) { return a.top() < b.top(); };
    for (size_t i = 0; i < N; ++i) {
        auto cmax_ptr =  max_element(pq_table.begin(), pq_table.end(), predicate);
        if (i != N - 1) cmax_ptr->pop();
        else if (i == N - 1) std::cout << cmax_ptr->top() << '\n';
    }

    return 0;
}