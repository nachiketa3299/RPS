#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main (void) {
    // all IDs' characters are lowercase
    // and ID.length() <= 50
    string s_input;
    cin >> s_input;
    assert(s_input.length() <= 50);
    cout << s_input + "\?\?!" << endl;
    return 0;
}