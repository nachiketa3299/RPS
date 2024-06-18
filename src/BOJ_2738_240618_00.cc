#include <iostream>
#include <vector>

using namespace std;

struct Matrix {

	Matrix(int N, int M): data_(N, vector<int>(M)) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cin >> data_[i][j];
			}
		}
	}
	Matrix(vector<vector<int>>&& vec): data_(vec) { }
	pair<int, int> size() const { 
		return make_pair(data_.size(), data_.front().size());
	}

	Matrix operator+(Matrix const& o) const {
		auto const& [N, M] = size();
		auto data = vector<vector<int>>(N, vector<int>(M));

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				data[i][j] = data_[i][j] + o.data_[i][j];
			}
		}
		return Matrix(move(data));
	}

	void print() const {
		auto const& [N, M] = size();
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cout << data_[i][j] << ' ';
			}
			cout << '\n';
		}
	}
private:
	vector<vector<int>> data_;
};

int main() {
	int N, M; cin >> N >> M;
	(Matrix(N, M) + Matrix(N, M)).print();
}