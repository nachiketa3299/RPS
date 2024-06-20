/// @date 2024-06-19T22:50--23:07 (17)

#include <iostream>
#include <vector>

using namespace std;

struct Fibo {
	Fibo(int n): dp(n + 1) { dp[1] = dp[2] = 1; }

	int call_no(int const& n, int* cptr) {
		if (n == 1 || n == 2) { ++(*cptr); return 1;}
		else return call_no(n - 1, cptr) + call_no(n - 2, cptr);
	}

	int call_dp(int const& n, int* cptr) {

		for (int i = 3; i <= n; ++i) {
			++(*cptr);
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}

	vector<int> dp;
};


int main() {
	int n; cin >> n; // in [5, 40]
	auto fib = Fibo(n);
	int non_dp_call = 0, dp_call = 0;

	fib.call_no(n, &non_dp_call);
	fib.call_dp(n, &dp_call);
	
	cout << non_dp_call << " " << dp_call;

}