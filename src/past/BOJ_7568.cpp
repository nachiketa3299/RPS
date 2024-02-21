// https://www.acmicpc.net/problem/7568
// 2022-08-22
// - `[2022-08-22T11:33, 2022-08-22T11:44]`
// - `[2022-08-22T11:51, 2022-08-22T11:59]`

#include <iostream>
#include <vector> // array and vector difference?

using namespace std;

typedef struct {
    int weight;
    int height;
} WeHeight;

const bool isSmall (WeHeight current, WeHeight compare) {
    if (current.weight < compare.weight) {
        if (current.height < compare.height) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

const int findRank (const int index, vector<WeHeight> arr) {

    WeHeight current = arr[index];
    int current_rank = 1;

    for (int i = 0; i < arr.size(); i++) {
        if (isSmall(current, arr[i]) && i != index) {
            current_rank++;
        }
    }
    return current_rank;
}

int main (void) {
    int N; // (2 <= N <= 50)
    cin >> N; // (10 <= x, y <= 200)

    vector<WeHeight> parr;
    for (int i = 0; i < N; i++) {
        int input_temp_w, input_temp_h;
        cin >> input_temp_w >> input_temp_h;
        parr.push_back(WeHeight{ input_temp_w, input_temp_h });
    }

    vector<int> rankarr;

    for (int i = 0; i < parr.size(); i++) {
        rankarr.push_back(findRank(i, parr));
    }

    for (auto e: rankarr) {
        cout << e << " ";
    }

    return 0;
}