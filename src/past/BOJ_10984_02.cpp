#include <iostream>;
#include <vector>

class Semester {
private:
    struct Subject {
        int c; double g;
        double getProduct(void) const { return this->c * this->g; }
        Subject(void) {
            std::cin >> *this;
            return;
        }
        friend std::istream& operator>>(std::istream &is, struct Subject &sub) {
            is >> sub.c >> sub.g;
            return is;
        }
    };
    std::vector<struct Subject> subjects;
public:
    Semester(int N): subjects(N) {}
public:
    int getTotalC(void) const { 
        int total_sum = 0;
        for (const auto &s: this->subjects) total_sum += s.c;
        return total_sum;
    }
    double getGPA(void) const {
        double gpa = 0.0;
        for (const auto &s: this->subjects) gpa += s.getProduct();
        gpa /= this->getTotalC();
        return gpa;
    }
public:
    friend std::ostream& operator<<(std::ostream &os, const Semester &sem) {
        os << sem.getTotalC() << " " << sem.getGPA() << '\n';
        return os;
    }
};

int main(void) {
    int T; std::cin >> T;
    for (int i = 0; i < T; ++i) {
        int N; std::cin >> N;
        std::cout << Semester(N);
    }
}
