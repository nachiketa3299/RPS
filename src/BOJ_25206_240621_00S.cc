/// 2024-06-21 09:13-10:03 (50)
/// 너의 평점은 S5 25206

#include <iostream>
#include <string>
#include <map>
#include <numeric>
#include <array>

using namespace std;
using grade_t = pair<string, float>;

int main() {

	map<string const, float const> const s_dict = {
		{ "A+", 4.5f }, { "A0", 4.0f }, { "B+", 3.5f },
		{ "B0", 3.0f }, { "C+", 2.5f }, { "C0", 2.0f }, 
		{ "D+", 1.5f }, { "D0", 1.0f }, { "F" , 0.0f },
	};

	int constexpr N_COURSES = 20;
	array<grade_t, N_COURSES> s_d; // total score papaer

	for (auto& [letter, scale]: s_d) {
		string _t; cin >> _t >> scale >> letter;
	}

	// PROCESS `s_d`
	// "P" 빼고 전체를 더함
	auto cnt_exp = [](float const& a, grade_t const& d) {
		auto const& [letter, scale] = d;
		return letter == "P" ? a : a + scale;
	};

	auto const total_g = accumulate(s_d.cbegin(), s_d.cend(), 0.f, cnt_exp);

	// 평점을 계산함
	auto cal_score = [&s_dict](float const& a, grade_t const& d) {
		auto const& [letter, scale] = d;
		return letter == "P" ? a : a + scale * s_dict.at(letter);
	};

	auto const g = accumulate(s_d.cbegin(), s_d.cend(), 0.f, cal_score);

	cout << g / total_g;
}