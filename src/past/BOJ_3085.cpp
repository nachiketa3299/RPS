#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define HOR 0
#define VER 1

using namespace std;

class Board {
private:
    int _N;
    vector<string> _board;
public:
    Board (int N)
    : _N(N) {
        this->_board.resize(this->_N);
        for (string &s: this->_board) {
            s.resize(this->_N);
            cin >> s;
        }
    }
public: 
    int getMaxRowColItem (void) {
        int result = 1;

        // Horizontal direction checking
        for (int i = 0; i < this->_N; i++) {
            int hor_temp = 1; 
            for (int j = 1; j < this->_N; j++) {
                if (this->_board[i][j - 1] == this->_board[i][j]) {
                    hor_temp++;
                } else {
                    result = max(result, hor_temp);
                    hor_temp = 1;
                }

            }
            result = max(result, hor_temp);
        }

        // Vertical direction checking
        for (int i = 0; i < this->_N; i++) {
            int ver_temp = 1;
            for (int j = 0; j < this->_N - 1; j++) {
                if (this->_board[j + 1][i] == this->_board[j][i]) {
                    ver_temp++;
                } else {
                    result = max(result, ver_temp);
                    ver_temp = 1;
                }
            }
            result = max(result, ver_temp);
        }
        return result;
    }

    void swapCandy (int mode, int i, int j) {
        if (mode == HOR) {
            swap(this->_board[i][j], this->_board[i][j + 1]);
        } else {
            swap(this->_board[j][i], this->_board[j + 1][i]);
        }
        return;
    }

public: // Getter
    int getSize (void) {
        return this->_N;
    }

public: // for debug
    void printBoard (void) {
        for (auto l: this->_board) {
            for (auto c: l) {
                cout << c << " ";
            }
            cout << endl;;
        }
        return;
    }

};

int main (void) {
    // Colors: C, P, Z, Y
    int N;
    cin >> N; // (3 <= N <= 50)  
             
    Board B(N);

    int result = 0;
    for (int i = 0; i < B.getSize(); i++) {
        for (int j = 0; j < B.getSize() - 1; j++) {
            B.swapCandy(HOR, i, j);
            result = max(result, B.getMaxRowColItem());
            B.swapCandy(HOR, i, j);

            B.swapCandy(VER, i, j);
            result = max(result, B.getMaxRowColItem());
            B.swapCandy(VER, i, j);
        }
    }

    cout << result << endl;

    return 0;
}
