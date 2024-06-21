// 2024-06-21 40 (머리 식히기)
// 백준 9461 파도반 수열 S3

#include <iostream>

using namespace std;
using dp_t = long long int;

struct Padovan {
	Padovan()
		: dp(new dp_t[MAX_SIZE])
		, cache_end(2 + 1)
	{
		dp[2] = dp[1] = dp[0] = 1;
	}

	~Padovan() { delete [] dp; }
	dp_t operator()(int N) {
		auto const& nidx = N - 1;

		if (nidx < cache_end)
			return dp[nidx];

		for (int i = cache_end; i <= nidx; ++i) {
			dp[i] = dp[i - 2] + dp[i - 3];
		}

		cache_end = nidx + 1;
		return dp[nidx];
	}

	dp_t* dp;
	int cache_end;
	static constexpr int MAX_SIZE = 100;
};

int main() {
	int T; cin >> T; 
	int* tcs = new int[T];
	int* output = new int[T];
	for (int i = 0; i < T; ++i) {
		auto& N = tcs[i]; cin >> N; // in [1, 100]
	}
	static Padovan pfunct;
	for (int i = 0; i < T; ++i) {
		cout << pfunct(tcs[i]) << '\n';
	}
}

// TestCases
/* in
5
1
2
3
4
5
*/

/* out
1
1
1
2
2
*/

