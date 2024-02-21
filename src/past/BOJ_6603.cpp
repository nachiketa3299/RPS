#include <iostream>
#include <vector>
#include <algorithm>
#define PICK 6

using namespace std;


vector<vector<int>> Combination (vector<int>, int); 
void printVec(vector<vector<int>>);
bool cmp(vector <int>, vector <int>);


int main (void) {

    vector<vector<int>> Testcases;
    int k;

    do {
        cin >> k;
        vector<int> temp_vec;
        for (int i = 0; i < k; i++) {
            int temp;
            cin >> temp;
            temp_vec.push_back(temp);
        }
        if (k != 0) {
            Testcases.push_back(temp_vec);
            temp_vec.resize(0);
        }
    } while (k != 0);


    for (vector<int> &testcase: Testcases) {
        vector<vector<int>> Result = Combination(testcase, PICK);
        printVec(Result);
    }

    return 0;
}

vector<vector<int>> Combination (vector<int> testcase, int r) {
    vector<vector<int>> result;
    int n = testcase.size();

    vector<bool> mask (n - r, false);
    mask.insert(mask.end(), r, true);
    // ex if n = 8, r = 6
    // mask = {false, false, true, true, true, true}

    do {
        vector<int> temp (0);
        for (int k = 0; k < n; k++) {
            if (mask[k] == true) {
                temp.push_back(testcase[k]);
            }
        }
        sort(temp.begin(), temp.end());
        result.push_back(temp);
    } while (next_permutation(mask.begin(), mask.end()));
    sort(result.begin(), result.end(), cmp);
    return result;
}


void printVec(vector<vector<int>> vec) {
    for (auto v: vec) {
        for (auto a: v) {
            cout << a << " ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

bool cmp(vector <int> a, vector <int> b) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            continue;
        } else {
            return (a[i] > b[i]);
        }
    }
}
