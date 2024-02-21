//https://www.acmicpc.net/problem/2930
// 2022-08-16T18:35, 2022-08-16T19:42
// 2022-08-17T10:12, 2022-08-17T10:39
// 2022-08-17T13:33, 2022-08-17T14:47


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<string> StringVector;

#define WIN 2
#define DRAW 1
#define LOSE 0

int verify (char sg, char oth) {
    if (sg == oth) {
        return DRAW;
    } else {
        if (sg == 'S') {
            return (oth == 'P') ? WIN : LOSE;
        } else if (sg == 'P') {
            return (oth == 'R') ? WIN : LOSE;
        } else {
            return (oth == 'S') ? WIN : LOSE;
        }
    }
}

int calScore (string sg_in, StringVector all_in) {
    int score_sum = 0;
    for (string &e_in: all_in) {
        for (int i = 0; i < sg_in.size(); i++) {
            score_sum += verify(sg_in[i], e_in[i]);
        }
    }
    return score_sum;
}

StringVector toRoundSet (StringVector input) {
    const int round_num = input.size();
    const int people_num = input[0].size();

    StringVector per_round_set;
    per_round_set.resize(people_num);
    for (int p = 0; p < people_num; p++) {
        per_round_set[p].resize(round_num);
    }

    for (int p = 0; p < people_num; p++) {
        for (int r = 0; r < round_num; r++) {
            per_round_set[p][r] = input[r][p];
        }
    }

    return per_round_set;
}

vector<int> allPossibleScore (string round_set) {
    vector<int> score_arr_per_RSP = { 0, 0, 0 };
    
    for (int p = 0; p < round_set.size(); p++) {
        // Case if SG is 'R'
        score_arr_per_RSP[0] += verify('R', round_set[p]);
        // Case if SG is 'S'
        score_arr_per_RSP[1] += verify('S', round_set[p]);
        // Case if SG is 'P'
        score_arr_per_RSP[2] += verify('P', round_set[p]);
    }
    return score_arr_per_RSP;
}

int calMaxScore (StringVector all_in) {
    int max_score_sum = 0;
    const int round_num = all_in.size();
    const int people_num = all_in[0].size();

    StringVector per_round_set = toRoundSet(all_in);

    for (int p = 0; p < people_num; p++) {
        vector<int> possible_score_arr = allPossibleScore(per_round_set[p]);
        max_score_sum += *max_element(possible_score_arr.begin(), possible_score_arr.end());
    }

    return max_score_sum;
}

int main (void) {
    int R, N;
    string sangeunInput;
    StringVector otherInputs;

    cin >> R;
    sangeunInput.resize(R);
    for (string &s: otherInputs) {
        s.resize(R);
    }
    cin >> sangeunInput;
    cin >> N;
    otherInputs.resize(N);
    for (int i = 0; i < N; i++) {
        string i_temp;
        cin >> i_temp;
        otherInputs[i] = i_temp;
    }

    int each_score = calScore(sangeunInput, otherInputs);
    int max_score = calMaxScore(otherInputs);
    cout << each_score << endl;
    cout << max_score << endl;

    return 0;
}