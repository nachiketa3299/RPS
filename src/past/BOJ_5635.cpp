#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Person {
    struct Date {
    public:
        int y;
        int m;
        int d;
    public:
        Date(int y, int m, int d) : y(y), m(m), d(d) {}
    };
public:
    std::string name;
    struct Date birth_date;
public:
    Person(std::string name, int y, int m, int d)
        : name(name), birth_date(y, m, d) {}
    void print(void) const {
        std::cout << this->name << " ";
        std::cout << this->birth_date.y << " ";
        std::cout << this->birth_date.m << " ";
        std::cout << this->birth_date.d << " ";
        std::cout << std::endl;
    }
    static bool p_sorter(const struct Person& p1, const struct Person& p2) {
        if (p1.birth_date.y != p2.birth_date.y)
            return p1.birth_date.y > p2.birth_date.y;
        if (p1.birth_date.m != p2.birth_date.m)
            return p1.birth_date.m > p2.birth_date.m;
        return p1.birth_date.d > p2.birth_date.d;
    }
};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<struct Person> pvec;
    for (int i = 0; i < n; i++) {
        std::string name;
        int y, m, d;
        std::cin >> name >> d >> m >> y;
        pvec.push_back(Person(name, y, m, d));
    }
    std::sort(pvec.begin(), pvec.end(), &Person::p_sorter);
    std::cout << pvec.front().name << std::endl;
    std::cout << pvec.back().name << std::endl;
    return 0;
}
