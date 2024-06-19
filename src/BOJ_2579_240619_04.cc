/// @date 2024-06-19 09:57 -- 10:27

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int n_sscores;
	cin >> n_sscores;

	vector<int> ss(n_sscores);
	for (auto& s: ss) cin >> s;
	
	vector<int> dp(n_sscores);

	dp[0] = ss[0];
	dp[1] = ss[0] + ss[1];
	dp[2] = max(ss[0], ss[1]) + ss[2];

	for (int k = 3; k < dp.size(); ++k)
		dp[k] = max(dp[k - 2], dp[k - 3] + ss[k - 1]) + ss[k];

	cout << dp.back();
}