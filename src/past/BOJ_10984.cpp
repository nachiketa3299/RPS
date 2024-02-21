#include <iostream>
#include <vector>

struct Subject {
    int C; double G;
    Subject(int C=0, double G=0.0): C(C), G(G) {}
    Subject(const Subject& c): C(c.C), G(c.G) {}
    double getProduct(void) const {
        return this->C * this->G;
    }
    void print(void) const {
        std::cout << C << " " << G << '\n';
    }
};

int getTotalC (const std::vector<struct Subject> &s) {
    int t_c = 0;
    for (const auto& ss: s) t_c += ss.C;
    return t_c;
}

double getGPA (const std::vector<struct Subject> &s) {
    double gpa = 0;
    for (const auto &ss: s) gpa += ss.getProduct();
    gpa /= getTotalC(s);
    return gpa;
}

int main(void) {
    int T; std::cin >> T;
    std::vector<std::vector<struct Subject>> sem(T);

    for (int i = 0; i < sem.size(); ++i) {
        int N; std::cin >> N;
        for (int j = 0; j < N; j++) {
            int C; double G; std::cin >> C >> G;
            sem[i].push_back(Subject(C, G));
        }
    }

    // Get Result At Same Struct `Subject`
    // Subject.C is Total C & Subject.G is GPA
    std::vector<struct Subject> result(T);

    for (const auto &s: sem) 
        result[&s - &sem[0]] = Subject(getTotalC(s), getGPA(s));
    for (const auto &r: result) r.print();

    return 0;
}
