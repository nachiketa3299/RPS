#include <iostream>
#include <vector>

using namespace std;

class IntGraph {
private:
    int start_number;
    int end_number;
    vector<vector<int>> llist;
    vector<vector<int>> paths;
    vector<bool> visited;
public:
    IntGraph (int N) : start_number(N) {
        this->makeGraph();
    }
    void DFS (int s_val, int g_val, int pi) {
        this->visited[s_val] = true;
        this->paths[pi].push_back(s_val);

        if (s_val == g_val) {

        }
        for (int i = this->llist.size() - 1; i >= 0; i--) {

        }

    }
private:
    void makeGraph () {
        this->llist.resize(this->start_number);
        for (int i = this->start_number - 1; i >= 1; i--) {
            this->llist[i].push_back(this->toVal(i) - 1);
            if (this->toVal(i) % 2 == 0) {
                this->llist[i].push_back(this->toVal(i) / 2);
            } else if (this->toVal(i) % 3 == 0) {
                this->llist[i].push_back(this->toVal(i) / 3);
            } else {
                ;
            }
        }
    }
    int toVal (int i) { return i + 1; }
    int toInd (int i) { return i - 1; }
};


int main (void) {
    int N;
    cin >> N;
    return 0;
}
