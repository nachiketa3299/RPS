#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> countCompleteSquareroot (pair<int, int> rng) {
    vector<int> nums;
    pair<int, int> sqrt_rng = {
        static_cast<int>(ceil(sqrt(rng.first))),
        static_cast<int>(floor(sqrt(rng.second)))
    };

    if (sqrt_rng.first > sqrt_rng.second) {
        return pair<int, int> { -1, -1 };

    } else {
        for (int n = sqrt_rng.first; n <= sqrt_rng.second; n++) {
            nums.push_back(n * n);
        }

        int sum = 0;
        for (auto &e: nums) {
            sum += e;
        }

        int min = *min_element(nums.begin(), nums.end());

        return pair<int, int> { sum, min };

    }

}

int main (void) {
    int M, N;
    cin >> M >> N;

    pair<int, int> sol = countCompleteSquareroot(pair<int, int> { M, N });

    if (sol.first == -1) {
        cout << -1 << endl;
    } else {
        cout << sol.first << endl;
        cout << sol.second << endl;
    }


    

    return 0;
}
