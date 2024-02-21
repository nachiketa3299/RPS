// [2023-10-07T08:30, 2023-10-07T09:44]
//https://www.acmicpc.net/problem/1149

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

enum class HouseColor { Red, Green, Blue };


int main(void)
{
	std::size_t HouseCount; std::cin >> HouseCount; // [2, 1e3]

	std::vector<std::map<HouseColor, std::size_t>> Costs(HouseCount);
	for (std::map<HouseColor, std::size_t>& Cost : Costs)
	{
		std::size_t PriceRed, PriceGreen, PriceBlue;
		std::cin >> PriceRed >> PriceGreen >> PriceBlue;
		Cost.insert({ HouseColor::Red, PriceRed });
		Cost.insert({ HouseColor::Green, PriceGreen });
		Cost.insert({ HouseColor::Blue, PriceBlue });
	}

	std::map<HouseColor, std::size_t> TotalCostPerColor;

	for (HouseColor const& StartColor : { HouseColor::Red, HouseColor::Green, HouseColor::Blue })
	{
		std::vector<std::size_t> MinPrice(HouseCount);
		MinPrice.push_back(Costs[0][StartColor]);

		HouseColor OtherColor1, OtherColor2;
		if (StartColor == HouseColor::Red)
		{
			OtherColor1 = HouseColor::Green;
			OtherColor2 = HouseColor::Blue;
		}
		else if (StartColor == HouseColor::Green)
		{
			OtherColor1 = HouseColor::Red;
			OtherColor2 = HouseColor::Blue;
		}
		else
		{
			OtherColor1 = HouseColor::Red;
			OtherColor2 = HouseColor::Green;
		}

		for (std::size_t i = 1; i < HouseCount; ++i)
		{
			MinPrice.push_back(Costs[i][StartColor] + std::min(Costs[i - 1][OtherColor1], Costs[i - 1][OtherColor2]));
		}
		TotalCostPerColor.insert({ StartColor, MinPrice.back() });
	}

	std::size_t Solution = std::min_element(TotalCostPerColor.begin(), TotalCostPerColor.end(), [](auto const& op1, auto const& op2) {return op1.second < op2.second; })->second;
	std::cout << Solution << std::endl;

	return 0;
}
