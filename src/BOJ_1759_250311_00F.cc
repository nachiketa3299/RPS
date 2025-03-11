#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

vector<string> generate(const vector<char>& chars, int size) {
  vector<bool> mask(chars.size(), false); 
  fill(mask.begin(), mask.begin() + size, true);
  reverse(mask.begin(), mask.end());

  vector<string> ret;

  do {
    string comb = "";

    for (int i = 0; i < mask.size(); ++i) {
      if (mask[i]) {
        comb += chars[i];
      }
    }

    ret.push_back(comb);
  } while (next_permutation(mask.begin(), mask.end()));

  return ret;
}

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

  if (cons.size() < 2 || vows.size() < 1)  return 0;

  vector<string> passwords;

  for (int vsize = 1; vsize <= L; ++vsize) {
    int csize = L - vsize;

    if (csize < 2)
      break;
    
    vector<string> c_vows = generate(vows, vsize);
    vector<string> c_cons = generate(cons, csize);

    for (const string& c_vow: c_vows) {
      for (const string& c_con: c_cons) {
        string password = c_vow + c_con;
        sort(password.begin(), password.end());
        passwords.push_back(password);
      }
    }
  }

  for (const string& password: passwords) {
    cout << password << '\n';
  }
}