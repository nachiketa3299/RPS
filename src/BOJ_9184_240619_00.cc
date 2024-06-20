/// @date 2024-06-19T23:08

#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

struct dt {
	int a, b, c;
	dt() {
		cin >> *this;
	}

	friend istream& operator>>(istream& in, dt& d) {
		in >> d.a >> d.b >> d.c;
		return in;
	}

	bool is_valid() const {
		return !(a == -1 && b == -1 && c == -1);
	}

	// bool operator<(dt const& o) {
	// 	if (a != o.a) return a > o.a;
	// 	if (b != o.b) return b > o.b;
	// 	return c > o.c;
	// }
};

struct Op {
	inline constexpr static int kNoVal = -1;
	void consume(vector<dt> const& ds) {
		for (auto const& d: ds) {
			auto dp = vector<vector<vector<int>>>(21, vector<vector<int>>(21, vector<int>(21)));
			dp[0][0][0] = ㅏ;
			println(d, w(d, dp));
		}
	}
	static void println(dt const& d, int v) {
		cout << "w(" << d.a << ", " << d.b << ", " << d.c << ") = " << v;
		cout << '\n';
	}
	int& w(dt const& d, vector<vector<vector<int>>>& dp_) {
		auto [a, b, c] = d;

		if (a<=0 || b<=0 || c<=0)
			a = b = c = 0; // dp_[0][0][0] = 1
		else if (a>20 || b>20 || c>20)
			a = b = c = 20; 
		
		// a, b, c all in [1, 20]
		
		for (int ia = 1; ia <= a; ++ia) {
		for (int ib = 1; ib <= b; ++ib) {
		for (int ic = 1; ic <= c; ++ic) {
			if (a<b && b<c)
			{
				auto p1 = c-1<=0         ? dp_[0][0][0] : dp_[a][b][c-1];
				auto p2 = c-1<=0||b-1<=0 ? dp_[0][0][0] : dp_[a][b-1][c-1];
				auto p3 = b-1<=0         ? dp_[0][0][0] : dp_[a][b-1][c];

				dp_[a][b][c] = p1 + p2 - p3;
			}
			else 
			{
				
				auto p1 = a-1<=0         ? dp_[0][0][0] : dp_[a-1][b][c];
				auto p2 = a-1<=0||b-1<=0 ? dp_[0][0][0] : dp_[a-1][b-1][c];
				auto p3 = a-1<=0||c-1<=0 ? dp_[0][0][0] : dp_[a-1][b][c-1];
				auto p4 = b-1<=0         ? dp_[0][0][0] : dp_[a][b-1][c];

				dp_[a][b][c] = p1 + p2 + p3 - p4;
			}
		}}}

		return  dp_[a][b][c];
	}

	/*
		000
		100 =
		010
		001
		110
		101
		011
		111
	*/
};

int main() {
	vector<dt> ds;

	while(true) {
		dt d;
		if (!d.is_valid()) break;
		ds.push_back(d);
	}
	Op op;

	op.consume(ds);

}