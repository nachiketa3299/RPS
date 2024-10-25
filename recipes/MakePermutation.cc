#include <iostream>
#include <vector>
#include <algorithm>

void PrintVector(const std::vector<int>& vec) 
{
	for (auto i = 0; i < vec.size(); ++i) 
	{
		const auto delimeter = i != vec.size() - 1 ? ", " : "";
		std::cout << vec[i] << delimeter;
	}
}

/// @brief 순열을 만든다.
/// @param n 
/// @param r 
/// @param depth 
void PrintPermutation(std::vector<int>& vec, int n, int r, int depth)
{
	std::cout << n << " : " << r << " : " << depth << '\n';

	if (r == depth) 
	{
		PrintVector(vec);
		std::cout << '\n';
		return;
	}

	// 이거 그래프 한번 그려 봐야 함
	for (auto i = depth; i < n; ++i)
	{
		std::swap(vec[i], vec[depth]);

		PrintPermutation(vec, n, r, depth + 1);

		std::swap(vec[i], vec[depth]); // 원상 복귀
	}
	return;
}

int main()
{
	auto vec = std::vector<int> { 1, 2, 3 };
	PrintPermutation(vec, 3, 2, 0);
}
