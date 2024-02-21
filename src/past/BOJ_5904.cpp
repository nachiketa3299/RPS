#include <iostream>
#include <string>
#include <vector>
#include <cassert>

class Moo {
private:
    int max_n;
    std::vector<int> length_history;
    struct Range {
        int l, m, r;
    } rng;
public:
    Moo (int N) {
        this->findMaxBoundN(N);
        this->printLengthHistory();
        return;
    }
    void printLengthHistory (void) {
        std::cout << "Printing" << std::endl;
        for (auto e: this->length_history)
            std::cout << e << std::endl;
        return;
    }

private:
    void findMaxBoundN (int idx) {
        int idx_length = idx + 1;
        assert(idx_length > 0);
        const int l_S_0 = 3;
        const int l_S_1 = 10;
        
        if (idx_length <= l_S_0) {
            this->length_history.push_back(l_S_0);
            this->max_n = 0;
        } else if (idx_length <= 10) {
            this->length_history.push_back(l_S_1);
            this->max_n = 1;
        } else {
            int cur_n = 2;
            int S_i = 10;
            while (idx_length > S_i) {
            }
        }
    }
    void findMaxBoundN (int idx, int k) {
        int idx_length = idx + 1;

        int tmp_bnd_p = 3;
        this->length_history.push_back(tmp_bnd_p);

        // if idx <= 3, S(0)
        if (idx_length <= tmp_bnd_p) {
            this->max_n = 0;
            return;
        }

        int tmp_bnd_c = 10;
        int tmp_n_c = 1;
        // else 
        while(idx_length > tmp_bnd_c) {
            tmp_bnd_c = 2 * tmp_bnd_p + tmp_n_c + 3;
            std::cout << "Pushing" << tmp_bnd_c << std::endl;
            this->length_history.push_back(tmp_bnd_c);
            tmp_bnd_p = tmp_bnd_c;
            tmp_n_c++;
        }
        this->max_n = tmp_n_c;
        return;
    }
};



int main (void) {
    int input_idx; std::cin >> input_idx;
    input_idx -= 1;
    Moo n(input_idx);
    //std::cout << Moo(input_idx).at(input_idx) << std::endl;
    return 0;
}
