//https://www.acmicpc.net/problem/1032
// BAEKJOON-STUDY
// [2022-08-14T13:55, 2022-08-14T14:23]
// [2022-08-14T15:53, 2022-08-14T16:32] 성공!
// TODO range-based for loop in dynamically allocated array (https://boycoding.tistory.com/210)

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> getInput (int i_n) {
    vector<string> str_vec(i_n);
    for (int i = 0; i < i_n; i++) {
        cin >> str_vec[i];
    }
    return str_vec;
}

string genQuery (vector<string> str_vec) {
    const int str_vec_size = str_vec.size();
    const int str_size = str_vec[0].length();
    string query;
    query.resize(str_size); // TODO difference between reserve and resize? reserve gets error

    // 스트링 들의 c_i번째 인덱스가 모두 같은지, 하나라도 다른지 판별
    for (int c_i = 0; c_i < str_size; c_i++) {
        bool is_all_same = true;
        for (int str_i = 1; str_i < str_vec_size; str_i++) {
            if (str_vec[0][c_i]  != str_vec[str_i][c_i]) {
                is_all_same = false;
                break;
            }
        }
        // 모두 같은지 하나라도 다른지 판별 결과에 따라 문자 할당
        if (is_all_same && str_vec[0][c_i] == '.') {
            query[c_i] = '.';
        } else if (is_all_same) {
            query[c_i] = str_vec[0][c_i];
        } else {
            query[c_i] = '?';
        }
    }

    return query;
}

int main (void) {
    /* Get string inputs */
    int N; // Number of file names
    cin >> N;
    vector<string> str_vec = getInput(N);
    // str_vec[*].length() is all same

    cout << genQuery(str_vec) << endl;

    return 0;
}