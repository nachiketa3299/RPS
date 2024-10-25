#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() 
{
	auto vec = std::vector<int> { 1, 2, 3 };
	std::sort(vec.begin(), vec.end(), std::less<int>());
	// next_permutation은 오름차순 정렬이 선행되어야 함

	// do - while을 쓰는 이유는, 자기 자신을 포함하지 않기 때문
	while (std::next_permutation(vec.begin(), vec.end())) 
	{
		for (const auto& e: vec)
		{
			std::cout << e << ' ';
		}
		std::cout << '\n';
	}

	std::cout << '\n';

	// 주의! 미리 정렬이 되어 있어야 함.
	// prev_permutation은 내림차순 정렬이 선행되어야 함
	// std::greater<int>는 '큰 것이 앞에 온다' 임

	std::sort(vec.begin(), vec.end(), std::greater<int>());
	while (std::prev_permutation(vec.begin(), vec.end()))
	{
		for (const auto& e: vec) 
		{
			std::cout << e << ' ';
		}
		std::cout << '\n';
	}
}
