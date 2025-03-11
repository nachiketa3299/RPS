#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define V_MIN 1
#define C_MIN 2

bool is_vowel(char c) {
  switch (c) {
    case 'a': case 'e': case 'u': case 'i': case 'o':
      return true;
    default:
      return false;
  }
}

void generate(const vector<char>& letters, int idx, int size, vector<char>& buff, int vcount, int ccount) {
  if (buff.size() == size) {
    if (vcount >= V_MIN && ccount >= C_MIN) {
      for (const auto& c: buff) {
        cout << c;
      }
      cout << '\n';
    }
  }

  for (int i = idx; i < letters.size(); ++i) {
    const char& c = letters[i];
    buff.push_back(c);
    bool is_v = is_vowel(c);

    if (is_v) generate(letters, i + 1, size, buff, vcount + 1, ccount);
    else      generate(letters, i + 1, size, buff, vcount, ccount + 1);

    buff.pop_back();
  }
}

int main() {
  int L, C; cin >> L >> C;

  vector<char> letters(C);
  for (auto& letter: letters) {
    cin >> letter;
  }

  sort(letters.begin(), letters.end());
  vector<char> buff; buff.reserve(L);

  generate(letters, 0, L, buff, 0, 0);
}