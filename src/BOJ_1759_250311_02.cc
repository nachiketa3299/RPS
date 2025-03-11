#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

#define V_MIN 1
#define C_MIN 2

int main() {
  int L, C; cin >> L >> C;
  vector<char> vows, cons;

  for (int i = 0; i < C; ++i) {
    char c; cin >> c;
    switch (c) {
      case 'a': case 'e': case 'i': case 'o': case 'u':
        vows.push_back(c);
        break;
      default:
        cons.push_back(c);
        break;
    }
  }

  sort(vows.begin(), vows.end());
  sort(cons.begin(), cons.end());

  vector<string> pwds;

  for (int vs = V_MIN; vs <= L - C_MIN; ++vs) {
    int cs = L - vs;

    vector<bool> vmask(vows.size(), false);
    fill(vmask.rbegin(), vmask.rbegin() + vs, true);

    vector<bool> cmask(cons.size(), false);
    fill(cmask.rbegin(), cmask.rbegin() + cs, true);

    do {
      string v_str{};

      for (int i = 0; i < vows.size(); ++i) {
        if (!vmask[i]) continue;
        v_str.push_back(vows[i]);
      }

      do {
        string c_str;

        for (int i = 0; i < cons.size(); ++i) {
          if (!cmask[i]) continue;
          c_str.push_back(cons[i]);
        }

        string pwd{ v_str + c_str };
        if (pwd.empty()) continue;

        sort(pwd.begin(), pwd.end());

        pwds.push_back(pwd);
      } while (next_permutation(cmask.begin(), cmask.end()));
    } while (next_permutation(vmask.begin(), vmask.end()));
  }

  sort(pwds.begin(), pwds.end());

  for (const auto& pwd: pwds) {
    cout << pwd << '\n';
  }
}