#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool Check(const vector<vector<int>>& Arr2D, int XMin, int XMax, int YMin, int YMax, int& Start) {
	Start = Arr2D[YMin][XMin];

	for (int i = YMin; i < YMax; i++) {
		for (int j = XMin; j < XMax; j++) {
			if (Start != Arr2D[i][j]) {
				return false;
			}
		}
	}

	return true;
}

string QuadTree(const vector<vector<int>>& Arr2D, int XMin, int XMax, int YMin, int YMax) {
	string Result = "";

	int XHalf = (XMax - XMin) / 2;
	int YHalf = (YMax - YMin) / 2;

	int Num = -1;

	if (Check(Arr2D, XMin, XMax, YMin, YMax, Num)) {
		Result += to_string(Num);
	}
	else {
		Result += "(";

		Result += QuadTree(Arr2D, XMin, XHalf, YMin, YHalf);
		Result += QuadTree(Arr2D, XHalf, XMax, YMin, YHalf);
		Result += QuadTree(Arr2D, XMin, XHalf, YHalf, YMax);
		Result += QuadTree(Arr2D, XHalf, XMax, YHalf, YMax);

		Result += ")";
	}

	return Result;
}

int main() {
	//start : 20 : 16

	int N;
	cin >> N;

	vector<vector<int>> Arr2D(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		string Line;
		cin >> Line;

		for (int j = 0; j < Line.size(); j++) {
			Arr2D[i][j] = (int) (Line[j] - 48);
		}
	}

	cout << QuadTree(Arr2D, 0, N, 0, N);

	return 0;
}