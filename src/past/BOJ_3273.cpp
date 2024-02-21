#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main (void) {
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> sequence;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        sequence.push_back(t);
    }
    int x;
    cin >> x;
    int c = 0;

    if (x == 1) {
        ;
    } else {
        sort(sequence.begin(), sequence.end());
        int max_index = n - 1;

        while (sequence[0] + sequence[max_index] > x) {
            max_index--;
        }

        for (int j = max_index; j > 0; j--) {
            for (int i = 0; i < j; i++) {
                if (sequence[i] + sequence[j] == x) {
                    c++;
                }
            }
        }

    }


    cout << c << "\n";
    
    return 0;
}
