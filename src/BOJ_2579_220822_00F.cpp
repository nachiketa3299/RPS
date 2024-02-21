// https://www.acmicpc.net/problem/2579
// 2022-08-22
// - `[2022-08-22T21:03]`
// What is brute force?

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool hasTwoConsOne (vector<int> arr) {
    for (int i = 1; i < arr.size() - 1;) {
        if (arr[i] == 1) {
            if (arr[i + 1] == 1) {
                return true;
            } else if (arr[i + 1] != 1) {
                i += 1;
            }
        } else {
            i += 1;
        }
    }
    return false;
}

vector<vector<int>> possibleSum (const int size) {
    vector<vector<int>> pos_sums;
    int max_twonum = size / 2;
    for (int twonum = 0; twonum < max_twonum + 1; twonum++) {
        int onenum = size - 2 * twonum;
        int cur_size = onenum + twonum;
        vector<int> sub (onenum, 1);
        sub.resize(cur_size, 2);
        do {
            if (!hasTwoConsOne(sub)) {
                pos_sums.push_back(sub);
            }
        } while (next_permutation(sub.begin(), sub.end()));
    }
    return pos_sums;
}

vector<int> calScore (vector<vector<int>> pos_sum, vector<int> step_s) {
    vector<int> scores;
    for (int i = 0; i < pos_sum.size();i++) {
        int sum = 0;
        int index = 0;

        for (auto e: pos_sum[i]) {
            cout << e << " ";
        }
        cout << endl;

        for (int j = 0; j < pos_sum[i].size(); j++) {
            index += pos_sum[i][j];
            sum += step_s[index - 1];
            cout << "- tosumi: " << index - 1 << ", - tosum:" << step_s[index - 1] << endl;
        }
        cout << "- sum: " << sum << endl;
        scores.push_back(sum);
    }
    return scores;
}

int main (void) {
    int STEP_SIZE;
    cin >> STEP_SIZE;

    // Initialize scores of each step
    vector<int> step_scores(STEP_SIZE);
    for (auto &e: step_scores) {
        cin >> e;
    }
    // step_score 에 계단별 점수가 저장된다.

    vector<vector<int>> possible_sums = possibleSum(STEP_SIZE);
    for (auto e: possible_sums) {
        for (auto s: e) {
            cout << s << " ";
        }
        cout << endl;
    }
    vector<int> possible_scores = calScore(possible_sums, step_scores);

    cout << *max_element(possible_scores.begin(), possible_scores.end()) << endl;
    return 0;
}