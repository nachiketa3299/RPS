#include <iostream>
#include <vector>

// 18분

using namespace std;

bool is_hansu(int n) {
    string sn = to_string(n);

    if (sn.size() <= 2) return true;

    int a0 = *sn.cbegin() - '0';
    int a1 = *(++sn.cbegin()) - '0';
    int d = a1 - a0;

    for (auto it = sn.cbegin() + 1; it != sn.cend(); ++it) {
      if (it + 1 == sn.cend()) 
        break;

      int a_n_0 = *it - '0';
      int a_n_1 = *(it + 1) - '0';

      if (a_n_1 - a_n_0 != d) 
        return false;
    }

    return true;
}

int main() {
  int N; cin >> N; // [1, 1'000]

  int count = 0;

  for (int n = 1; n <= N; ++n) {
    if (is_hansu(n)) 
      ++count;
  }

  cout << count;
}

// TODO: 반복자 섞어 쓰기