// https://www.acmicpc.net/problem/2217 (ทฮวม)
// [2023-10-06T11:00, 2023-10-06T11:32] (32)

#include <iostream>
#include <vector>
#include <algorithm>

int main(void)
{
	// Input
	std::size_t RopeCounts; std::cin >> RopeCounts; // [1, 1e5]
	std::vector<std::size_t> RopeWeights(RopeCounts);
	for (std::size_t& RopeWeight : RopeWeights)
	{
		std::cin >> RopeWeight; // [1, 1e4], Natural Number
	}

	std::sort(RopeWeights.begin(), RopeWeights.end(), std::greater<std::size_t>());
	std::vector<std::size_t> const& DescendingRopeWeights = RopeWeights;
	// Process

	std::vector<std::size_t> CandidateRopeTotalMaxWeight(RopeCounts);

	for (std::size_t PickedRopeCounts = 1; PickedRopeCounts <= RopeCounts; ++PickedRopeCounts)
	{
		CandidateRopeTotalMaxWeight.push_back(PickedRopeCounts * DescendingRopeWeights[PickedRopeCounts - 1]);
	}

	std::sort(CandidateRopeTotalMaxWeight.begin(), CandidateRopeTotalMaxWeight.end(), std::greater<std::size_t>());

	// Output
	std::size_t const& Solution = CandidateRopeTotalMaxWeight.front();
	std::cout << Solution << std::endl;

	return 0;
}