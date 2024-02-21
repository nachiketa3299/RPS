// https://www.acmicpc.net/problem/1065
// 2022-08-10

#include <iostream>

using namespace std;

class Digit {

private:
    int * d_arr;
    int size;

// TODO Dynamic Array Return Function : https://stackoverflow.com/questions/44478449/c-how-to-return-dynamically-allocated-array-from-function

public:
    Digit () {}
    Digit (const int n) {
        this->size = this->_verifySize(n);
        this->d_arr = new int [size];
        this->_digitize(n);
    }
    ~Digit () {
        delete [] this->d_arr;
    }

    bool isHansu () {
        const int difference = this->d_arr[0] - this->d_arr[1];
        for (int i = 1; i < this->size - 1; i++) {
            int c_difference = this->d_arr[i] - this->d_arr[i + 1];
            if (difference != c_difference) {
                return false;
            }
        }
        return true;
    }

    void _printInfo () {
        cout << "- Size: " << this->size << endl;
        cout << "- Array: ";
        for (int i = 0; i < this->size; i++) {
            cout << this->d_arr[i];
            cout << ", ";
        }
        cout << endl;
    }

private:
    const int _verifySize (int n) {
        int size = 0;
        while (n != 0) {
            n /= 10;
            size++;
        }
        return size;
    }
    void _digitize (int n) {
        for (int i = 0; i < this->size; i++) {
            this->d_arr[i] = n % 10;
            n /= 10;
        }
    }

};


int main (void) {

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    // Input N
    int N;
    cin >> N;

    int num_of_ans = 0;
    for (int i = 1; i <= N; i++) {
        // cout << ">> Target: " << i << endl; //
        Digit DN = Digit(i);
        // DN._printInfo(); //
        if (DN.isHansu()) {
            num_of_ans++;
        }
    }

    cout << num_of_ans << endl;

    return 0;
}