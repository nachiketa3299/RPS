/// @date 2024-06-18T11:11 - 11:38 (17)
/// @date 2024-06-18T11:38 

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	array<bool, 30 + 1> submitted({false}); // 1 ~ 30

	for (int i = 0; i < 28; ++i) {
		int temp; cin >> temp;
		submitted[temp] = true;
	}

	vector<int> not_submitted;

	for (int i = 1; i < 31; ++i) {
		if (submitted[i])
			continue;
		
		not_submitted.push_back(i); // TODO rbased for to indices
	}

	for (auto const& nsub: not_submitted) {
		cout << nsub << '\n';
	}

}