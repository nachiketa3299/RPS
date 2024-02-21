#include <iostream>
#include <vector>
// a is base
struct Score {
    int a, b;
    Score(void): a(100), b(100) {}
    Score(int a, int b): a(a), b(b) {}
    Score(const Score &s): a(s.a), b(s.b) {}
    Score operator+(const struct Score &ref) {
        return Score(this->a + ref.a, this->b + ref.b);
    }
    void print(void) const {
        std::cout << a << '\n' << b << '\n';
    }
};

struct Record {
    int a, b;
    Record(void): a(0), b(0) {}
    Record(int a, int b): a(a), b(b) {}
    Record(const Record &r): a(r.a), b(r.b) {}
    struct Score result(void) const {
        if (a > b) return Score(0, -a);
        else if (a == b) return Score(0, 0);
        else return Score(-b, 0);
    }
};




int main(void) {
    int R; std::cin >> R;
    std::vector<struct Record> records(R);
    for(auto &record: records) {
        int a, b; std::cin >> a >> b;
        record = Record(a, b);
    }

    Score s;

    for (auto &record: records) {
        s = s + record.result();
    }
    s.print();
    return 0;
}
