
// 서로 다른 L개의 알파벳 소문자들로 구성
// 최소 한 개의 모음과 최소 두 개의 자음
// 암호는 정렬된 순서
// C가지 종류의 문자 가능성 있는 암호 모두 구하기
// 시간 제한 2초
// [3, L, C, 15]
// C 개 문자들이 공백으로 구분되어 주어짐
// 주어지는 문자들은 소문자, 중복 X

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

vector<vector<char>> combination(const vector<char>& total, int size) {
  vector<bool> mask(total.size(), false);

  fill(mask.begin(), mask.begin() + size, true); // 여기에 상수 아닌거 쓰면?

  vector<vector<char>> ret;

  do {
    vector<char> selected;

    for (int i = 0; i < total.size(); ++i) {
      if (mask[i])
        selected.push_back(total[i]);
    }

    ret.push_back(selected);

  } while (prev_permutation(mask.begin(), mask.end())); // mutable

  return ret;
}

// C 에서 최소 한개의 모음, 최소 두 개의 자음을 사용하여
// 정렬된 문자열 만들기

int main() {
  // 3 <= L <= C <= 15
  int L, C; cin >> L >> C; // 암호의 길이: L
  vector<char> vowels;
  vector<char> consonants;

  for (int i = 0; i < C; ++i) {
    char c; cin >> c;

    switch (c) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
      vowels.push_back(c);
      break;
    default:
      consonants.push_back(c);
    }
  }

  vector<string> passwords;

  // 최소 [1개]부터 [들어온 전체 모음갯수]까지 사용
  for (int vs = 1; vs <= vowels.size(); ++vs) {
    // 최소 [2개]부터 [암호길이 - 현재 모음갯수]까지 사용

    int cs = L - vs;
    if (cs < 2) break;

    vector<vector<char>> c_vows = combination(vowels, vs);
    vector<vector<char>> c_cons = combination(consonants, cs);

    for (const vector<char>& c_vow: c_vows) {
      for (const vector<char>& c_con: c_cons) {

        string password; // reserve vs size

        password.insert(password.end(), c_vow.cbegin(), c_vow.cend());
        password.insert(password.end(), c_con.cbegin(), c_con.cend());

        sort(password.begin(), password.end());
        passwords.push_back(password);
      }
    }
  }

  sort(passwords.begin(), passwords.end());

  for (const string& password: passwords) {
    cout << password << '\n';
  }
}