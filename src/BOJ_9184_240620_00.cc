/// 백준 S2 신나는 함수 실행
/// 2025-06-20 10:49 -- 11:45 (50)

#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct Dt {
	int a, b, c;
	friend istream& operator>>(istream& in, Dt& r) {
		in >> r.a >> r.b >> r.c; return in;
	}
	bool is_valid() const {
		return !(a==-1&& b==-1&&c==-1);
	}
};

struct Ft {
	template <class T> using tv_t = vector<vector<vector<T>>>;
	Ft()
		: dp(21, vector<vector<int>>(21, vector<int>(21)))
		, is_dp(21, vector<vector<bool>>(21, vector<bool>(21, false))) {
		dp[0][0][0] = 1;
		is_dp[0][0][0] = true;
	}

	int w(Dt const& d) {
		auto const& [a, b, c] = d;
		if (a<=0||b<=0||c<=0) return dp[0][0][0]; // always has value
		if (a>20||b>20||c>20) return w({20, 20, 20}); // restart func with 20,20,20

		// after this, `a`, `b`, `c` all in [1, 20]

		if (is_dp[a][b][c]) return dp[a][b][c];
		
		auto const& iv = dp[0][0][0];
		
		// a, b, c -> 20 으로 바꾸면 훨씬 빠른
		for (int ia = 1; ia <= a; ++ia) {
		for (int ib = 1; ib <= b; ++ib) {
		for (int ic = 1; ic <= c; ++ic) {
			if (ia<ib && ib<ic) {
				auto const p0 =          ic-1<=0 ? iv : dp[ia][ib  ][ic-1];
				auto const p1 = ib-1<=0||ic-1<=0 ? iv : dp[ia][ib-1][ic-1];
				auto const p2 = ib-1<=0          ? iv : dp[ia][ib-1][ic  ];

				dp[ia][ib][ic] = p0 + p1 - p2;
				is_dp[ia][ib][ic] = true;
			} else {

				auto const p0 = ia-1<=0                   ? iv : dp[ia-1][ib  ][ic  ];
				auto const p1 = ia-1<=0||ib-1<=0          ? iv : dp[ia-1][ib-1][ic  ];
				auto const p2 = ia-1<=0         ||ic-1<=0 ? iv : dp[ia-1][ib  ][ic-1];
				auto const p3 = ia-1<=0||ib-1<=0||ic-1<=0 ? iv : dp[ia-1][ib-1][ic-1];

				dp[ia][ib][ic] = p0 + p1 + p2 - p3;
				is_dp[ia][ib][ic] = true;
			}
		}}}

		return dp[a][b][c];
	}
	tv_t<int> dp; // real cache
	tv_t<bool> is_dp; // is these calculated before?
};

int main() {
	vector<Dt> ds;

	while (true) {
		auto d = Dt();
		cin >> d;
		if (!d.is_valid()) break;
		ds.push_back(d);
	}

	auto f = Ft();

	for (auto const& d: ds) {
		auto const& [a, b, c] = d;
		cout << "w(" << a << ", "  << b << ", " << c << ") = ";
		cout << f.w(d) << '\n';
	}
}