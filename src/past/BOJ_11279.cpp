#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main (void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N;
    cin >> N;
    vector<int> operations(N);
    for (int &o: operations) {
        cin >> o;
    }

    priority_queue<int> max_heap;
    vector<int> output;

    for (int o: operations) {
        switch (o) {
            case 0:
                if (max_heap.size() != 0) {
                    output.push_back(max_heap.top());
                    max_heap.pop();
                } else {
                    output.push_back(0);
                }
                break;
            default:
                max_heap.push(o);
                break;
        }
    }

    for (int out: output) {
        cout << out << '\n';
    }

    
    return 0;
}
