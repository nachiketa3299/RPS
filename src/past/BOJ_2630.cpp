#include <iostream>
#include <vector>
#define BLUE true
#define WHIT false

using namespace std;

typedef struct {
    int n_blue;
    int n_whit;
} Solution;

bool isAllSameColor (vector<vector<bool>> p) {
    bool start_color = p[0][0];
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0; j < p[i].size(); j++) {
            if (start_color != p[i][j]) {
                return false;
            }
        }
    }
    return true;
}

vector<vector<vector<bool>>> cutPaper (vector<vector<bool>> p) {
    int N = p.size();
    int n = N / 2;
    vector<vector<vector<bool>>> result(4, vector<vector<bool>>(n, vector<bool>(n)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[0][i][j] = p[i][j];
            result[1][i][j] = p[i + n][j];
            result[2][i][j] = p[i][j + n];
            result[3][i][j] = p[i + n][j + n];
        }
    }
    return result;
}

Solution recursiveCutPaper (vector<vector<bool>> &p) {
    static Solution s { 0, 0 };
    if (isAllSameColor(p) == false) {
        for (vector<vector<bool>> np: cutPaper(p)) {
            recursiveCutPaper(np);
        }
    } else if (isAllSameColor(p) == true) {
        if (p[0][0] == WHIT) {
            s.n_whit++;
        } else {
            s.n_blue++;
        }
    }
    return s;
}


int main (void) {
    int N;
    cin >> N;
    vector<vector<bool>> paper (N, vector<bool>(N));

    for (int i = 0; i < paper.size(); i++) {
        for (int j = 0; j < paper[0].size(); j++) {
            int input;
            cin >> input;
            paper[i][j] = ((input == 1) ? BLUE : WHIT);
        }
    }

    Solution s = recursiveCutPaper(paper);

    cout << s.n_whit << endl;
    cout << s.n_blue << endl;

    return 0;
}
