#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int x;
    int y;
} Pos;

typedef struct {
    Pos pos;
    bool exist;
} Bch;

typedef struct {
    Pos pos;
    bool visited;
} Seed;

int main (void) {
    int T;
    cin >> T;
    vector<int> result_by_testcase (T, 0);

    for (int tc = 0; tc < T; tc++) {
        int M, N, K;
        cin >> M >> N >> K;

        vector<vector<Bch>> bch_grid (N, vector<Bch> (M));
        vector<Seed> bch_seed (K);
    }

    return 0;
}
