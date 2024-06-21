// 2024-06-21 2:30 -- 2:59 (19)
// 그룹 단어 체커 1316 S5

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	int const N = []() { int _n; cin >> _n; return _n; }();
	vector<string> group_words;
	for (int i = 0; i < N; ++i) {
		string const in_str = []() { string _t; cin >> _t; return _t; }();
		bool existed['Z'-'A'+1] { false };
		bool is_group_word = true;

		for (int i = 0; i < in_str.size(); ++i) {

			if (!existed[in_str[i] - 'a'])
				existed[in_str[i] - 'a']  = true;
			
			else {
				if (!(is_group_word = (in_str[i - 1] == in_str[i])))
					break;
			}
		}

		if (is_group_word) group_words.push_back(in_str);
	}
	cout << group_words.size();


}