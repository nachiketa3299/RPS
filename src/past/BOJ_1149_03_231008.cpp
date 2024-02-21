// [2023-10-08T23:01, 2023-10-08T23:40] (39)

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

enum class HouseColor
{
	Red, Green, Blue
};

int main(void)
{
	// Input
	std::size_t HouseCount; 
	std::cin >> HouseCount; // [2, 1e3]

	std::map<HouseColor, std::vector<std::size_t>> CostsPerColor
	{
		{ HouseColor::Red, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Green, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Blue, std::vector<std::size_t>(HouseCount) },
	};

	for (std::size_t i = 0; i < HouseCount; ++i)
	{
		// [1, 1e3], Natural Number
		std::cin >> CostsPerColor[HouseColor::Red][i];
		std::cin >> CostsPerColor[HouseColor::Green][i];
		std::cin >> CostsPerColor[HouseColor::Blue][i];
	}

	// i 번째 집에 색칠한다고 가정 (1 < i <= HouseCount)
	// i 번째 집에 Red을 칠한다고 가정하면 i - 1 번째에는 Blue혹은 Green 둘 중 하나를 칠한 거임
	// (중요) i 번째 집에 Red를 칠하는데 그 때까지의 총 비용이 최소가 되게 하려면, i - 1 번째가 최소 였었어야 함. (무슨 색으로 칠했었는진 중요치 않음) 
	// (그 전까지가 최소비용이었다면 지금 Red/Blue/Green을 칠한 것으로 총 비용을 마지막에 비교하면 됨) - 이게 이해 안되면 이 문제 못 풂

	std::set<HouseColor> HouseColors { HouseColor::Red, HouseColor::Green, HouseColor::Blue };
	// i 번째 집에 어떤 색을 칠할 때 최소비용
	std::map<HouseColor, std::vector<std::size_t>> MinCosts
	{
		{ HouseColor::Red, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Green, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Blue, std::vector<std::size_t>(HouseCount) },
	};
	
	// 첫 번째 집은 그냥 처음 값을 넣어주면 그게 최소비용임
	for (HouseColor const& CurrentColor: HouseColors)
	{
		MinCosts[CurrentColor].front() = CostsPerColor[CurrentColor].front();
	}

	// 두 번째 집 부터는 이전 최소 비용과 비교해야함
	for (std::size_t i = 1; i < HouseCount; ++i)
	{
		for (HouseColor const& CurrentColor : HouseColors)
		{
			// 현재 색상이 아닌 두 색을 집합으로 받아옴
			std::set<HouseColor> CurrentColorSet = { CurrentColor };
			std::set<HouseColor> OtherColors; 
			std::set_difference
			(
				HouseColors.begin(), HouseColors.end(),
				CurrentColorSet.begin(), CurrentColorSet.end(),
				std::inserter(OtherColors, OtherColors.begin())
			);
			HouseColor const& OtherColor1 = *(OtherColors.begin());
			HouseColor const& OtherColor2 = *(++OtherColors.begin());

			// 핵심 로직
			std::size_t PrevMiminumCost = std::min(MinCosts[OtherColor1][i - 1], MinCosts[OtherColor2][i - 1]);
			MinCosts[CurrentColor][i] = PrevMiminumCost + CostsPerColor[CurrentColor][i];
		}
	}

	std::vector<std::size_t> CandidateMinimums
	{
		MinCosts[HouseColor::Red].back(),
		MinCosts[HouseColor::Green].back(),
		MinCosts[HouseColor::Blue].back(),
	};
	std::size_t TotalMinimum = *std::min_element(CandidateMinimums.begin(), CandidateMinimums.end());
	std::cout << TotalMinimum << std::endl;
	return 0;
}