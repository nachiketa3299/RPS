#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void DFS (vector<vector<int>> network, vector<bool> &corrupted, int start=0) {
    corrupted[start] = true;
    for (int next_comp: network[start]) {
        if (corrupted[next_comp] == false) {
            DFS(network, corrupted, next_comp);
        }
    }
}

void makeFullGraph(vector<vector<int>> &network) {
    for (int i = 0; i < network.size(); i++) {
        for (int e: network[i]) {
            // if network[e] doesn't have i
            if (find(network[e].begin(), network[e].end(), i) == network[e].end()) {
                network[e].push_back(i);
            }
        }
    }
}

int main (void) {
    int COMP_NUM; // (COMP_NUM <= 100)
    cin >> COMP_NUM;
    vector<bool> Corrupted (COMP_NUM, false);
    vector<vector<int>> Network (COMP_NUM);

    int COMP_PAIR_NUM;
    cin >> COMP_PAIR_NUM;

    for (int i = 0; i < COMP_PAIR_NUM; i++) {
        int comp, linked;
        cin >> comp >> linked;
        Network[comp - 1].push_back(linked -1);
    }

    makeFullGraph(Network);

    DFS(Network, Corrupted);

    int ans = 0;
    for (auto e: Corrupted) {
        if (e) {
            ans++;
        }
    }

    cout << ans - 1 << endl;

    return 0;
}