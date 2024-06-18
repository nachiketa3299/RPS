/// @date 2024-06-18T15:44--15:54 (10)

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	vector<string> words(5);

	for (auto& word: words) {
		getline(cin, word);
	}

	constexpr int kMAX_W_LEN = 15;

	for (int i = 0; i < kMAX_W_LEN; ++i) {

		string ret = "";

		for (auto const& word: words) {
			if (!(word.size() > i)) continue;

			ret += word[i];
		}
		cout << ret;
	}
}