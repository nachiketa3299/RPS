#include <iostream>
#include <vector>

struct Record {
    int t, p;
    Record(void): t(0), p(0) {}
    Record(int t, int p): t(t), p(p) {}
    Record(const Record& r): t(r.t), p(r.p) {}
};

class Graph {
    Graph(std::vector<struct Record> &records) {

    }
};

int main(void) {
    int N; std::cin >> N;
    std::vector<struct Record> records(N);
    for (auto &record: records) {
        int t, p; std::cin >> t >> p;
        record = Record(t, p);
    }

    return 0;
}
