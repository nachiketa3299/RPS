/// 2024-06-21 T 12:30--35
/// 문자열 B5 

#include <iostream>

using namespace std;

int main() {
	int t; cin >> t;
	string* strs = new string[t];
	for (int i = 0; i < t; ++i) {
		cin >> strs[i];

		const auto& str = strs[i];
		cout << str.front();
		cout << str.back();
		cout << '\n';
	}
}