#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Person {
    std::string name;
    int age;
    Person(void): name(""), age(0) {}
    Person(std::string name, int age): name(name), age(age) {}
    friend std::istream& operator>>(std::istream &is, Person &ref) {
        is >> ref.age >> ref.name; return is;
    }
    void print(void) const {
        std::cout << this->age << " " << this->name << '\n';
        return;
    }
};

int main(void) {
    int N; std::cin >> N;
    std::vector<Person> p_v(N);
    for (std::size_t i = 0; i < N; ++i) std::cin >> p_v[i] ;
    std::stable_sort(p_v.begin(), p_v.end(), [&](const Person &p1, const Person &p2)->bool{ return p1.age < p2.age; });
    for (const Person &p: p_v) p.print();
    return 0;
}
