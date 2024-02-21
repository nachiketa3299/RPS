#include <iostream>
#include <string>

using namespace std;

string makeShort (string);

int main (void) {
    string long_form;
    cin >> long_form;

    string short_form = makeShort(long_form);
    cout << short_form << endl;

    return 0;
}

string makeShort (string long_form) {
    string short_form;
    short_form.push_back(long_form[0]);

    for (int i = 1; i < long_form.size(); i++) {
        if (long_form[i] == '-') {
            short_form.push_back(long_form[i + 1]);
        }
    }
    return short_form;
}
