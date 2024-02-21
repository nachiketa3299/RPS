#include <iostream>
#include <vector>

class Rectangle {
private:
    const struct PrintChar {
        char t = '*';
        char f = ' ';
    } print_char;

    struct Range {
        int start, end;
        friend bool operator == (const struct Range& r1, const struct Range& r2) {
            return (r1.start == r2.start && r1.end == r2.end);
        }
    };
    int edge_size;
    std::vector<std::vector<bool>> rec;

public:
    Rectangle (int N) : edge_size(N) {
        rec = std::vector<std::vector<bool>> (this->edge_size, std::vector<bool> (this->edge_size, true));
        return;
    }

public:
    void print (void) {
        for (const auto& line: this->rec) {
            for (const auto& element: line) {
                if (element) {
                    std::cout << this->print_char.t;
                }
                else {
                    std::cout << this->print_char.f;
                }
            }
            std::cout << std::endl;
        }
    }
private:
    void makeHole (const Range& r1, const Range& r2) {
        for (int i = r1.start ; i < r1.end; i++) {
            for (int j = r2.start; j < r2.end; j++) {
                this->rec[i][j] = false;
            }
        }
        return;
    }

    void recursive (int N, const Range& r1, const Range& r2) {
        int unit = N / 3;
        struct Range hole_r1 { r1.start + unit, r1.start + 2 * unit };
        struct Range hole_r2 { r2.start + unit, r2.start + 2 * unit };
        this->makeHole(hole_r1, hole_r2);

        if (N == 3) {
            return;
        } else {

            for (int i = r1.start; i < r1.end; i += unit) {
                for (int j = r2.start; j < r2.end; j += unit) {
                    struct Range new_r1 { i, i + unit };
                    struct Range new_r2 { j, j + unit };
                    if (!(new_r1 == hole_r1 && new_r2 == hole_r2)) {
                        this->recursive(unit, new_r1, new_r2);
                    }
                }
            }

        }
    }
public:
    void punchHoles (void) {
        this->recursive(this->edge_size, Range { 0, this->edge_size }, Range {0, this->edge_size});
        return;
    }
};


int main (void) {
    int N;
    std::cin >> N;
    Rectangle R(N);
    R.punchHoles();
    R.print();

    return 0;
}
