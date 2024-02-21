// 2022-08-23
// https://www.acmicpc.net/problem/1620

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const bool isFirstAlpha (const string input) {
	return (input[0] >= 'A' && input[0] <= 'Z') ? true : false;
}

string searchAToI (vector<string> dict, string query) {
	for (int i = 0; i < dict.size(); i++) {
		if (dict[i] == query) {
			return to_string(i + 1);
		}
	}
}

string searchIToA (vector<string> dict, string query) {
	int target_index = stoi(query) - 1;
	return dict[target_index];
}

int main (void) {
	int N, M;
	// 1 <= N, M <= 100'000 , (N, M) in Natural Number
	cin >> N >> M;

	vector<string> dictionary (N);
	for (auto &e: dictionary) {
		// e is consists only of alphabets, and only first letter is uppercase.
		// 2 <= e.length() <= 20
		cin >> e;
	}
	vector<string> question_arr (M);
	for (auto &e: question_arr) {
		cin >> e;
	}

	vector<string> answer_arr (M);
	for (int i = 0; i < question_arr.size(); i++) {
		if (isFirstAlpha(question_arr[i])) {
			answer_arr.push_back(searchAToI(dictionary, question_arr[i]));
		} else {
			answer_arr.push_back(searchIToA(dictionary, question_arr[i]));
		}
	}

	for (auto e: answer_arr) {
		cout << e << endl;
	}


	return 0;
}