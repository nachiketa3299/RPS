#include <vector>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& num, int target) {
		for (auto i = 0; i < num.size() - 1; ++i) {
			for (auto j = i + 1; j < num.size(); ++j) {
				if (num[i] + num[j] == target) {
					return { i, j };
				}
			}
		}

		return {};
	}
};